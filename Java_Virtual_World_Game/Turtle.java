import java.awt.*;
import java.util.Random;
import java.util.RandomAccess;

public class Turtle extends Animal{

    public Turtle(int x, int y, World world)
    {super(x,y,world);
        sign = 'T';
        name = "Turtle";
        color = Color.BLUE;
        str = 2;
        ini = 1;
        speciesId = 4;
    }
    public Turtle(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);
        sign = 'T';
        name = "Turtle";
        speciesId = 4;
        color = Color.BLUE;
    }
    @Override
    public Animal MakeNewA(int x, int y) {
        Animal newAnimal = new Turtle(x, y, world);
        return newAnimal;
    }
    @Override
    public void TakeAction() {
        if (age != DEAD && !moved)
        {
            int changeX = 0, changeY = 0, rNum;
            Random rand = new Random();
            rNum = rand.nextInt(100);
            if (rNum < 25)
            {
                while (true)
                {
                    rNum = rand.nextInt(4);
                    if (rNum == 0) {
                        changeX = -1;
                    }
                    else if (rNum == 1) {
                        changeX = 1;
                    }
                    else if (rNum == 2) {
                        changeY = -1;
                    }
                    else {
                        changeY = 1;
                    }
                    if (xPos + changeX < world.GetW() && yPos + changeY < world.GetH() &&  xPos + changeX >= 0 && yPos + changeY >= 0)
                        break;
                    else {
                        changeX = 0;
                        changeY = 0;
                    }
                }

                Organism potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
                if (potentialCollision != null) {
                    Collision(potentialCollision);
                }
                if (age != DEAD)
                {
                    potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY); // recheck if collision changed the state of disputed tile
                    if (potentialCollision == null)
                    {
                        int tmpx = xPos + changeX;
                        int tmpy = yPos + changeY;
                        System.out.print( name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n');
                        log = log + name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n';
                        xPos += changeX;
                        yPos += changeY;
                    }
                }
            }
            else {
                System.out.print(name + " from tile (" + xPos + ", " + yPos + ") stayed in place" + '\n');
                log = log + name + " from tile (" + xPos + ", " + yPos + ") stayed in place" + '\n';
            }
            moved = true;
        }
        world.AddLog(log);
        log = " ";
        if (age > 0) age++;
    }
    @Override
    public void Win(Organism otherCreature)
    {
        if (deflected) {
            System.out.print( " and " + name + " won! " + otherCreature.GetName() + " was pushed back" + '\n');
            log = log + " and " + name + " won! " + otherCreature.GetName() + " was pushed back" + '\n';
            deflected = false;
        }
        else {
            System.out.print( " and " + name + " won! " + otherCreature.GetName() + " was eaten" + '\n');
            log = log + " and " + name + " won! " + otherCreature.GetName() + " was pushed back" + '\n';
            world.RmOrganism(otherCreature.GetOId());
            world.AddLog(otherCreature.GetLog());
            otherCreature.ResetLog();
            otherCreature.SetAge(DEAD);
        }
    }
    @Override
    public boolean Defended(Organism attackingCreature) {
        if (attackingCreature.GetS() < 5) {
            deflected = true;
            return true;
        }
        return false;
    }
    private boolean deflected;
}
