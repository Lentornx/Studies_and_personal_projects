import java.awt.*;
import java.util.Random;

public class Antelope extends Animal{
    public Antelope(int x, int y, World world)
    {super(x,y,world);
        sign = 'A';
        color = Color.RED;
        name = "Antelope";
        str = 5;
        ini = 5;
        speciesId = 5;
    }
    public Antelope(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);
        sign = 'A';
        name = "Antelope";
        speciesId = 5;
        color = Color.RED;
    }
    @Override
    public Animal MakeNewA(int x, int y) {
        Animal newAnimal = new Antelope(x, y, world);
        return newAnimal;
    }
    @Override
    public boolean Defended(Organism attackingCreature) {
        if (str > attackingCreature.GetS()) {
            return true;
        }
        else
        {
            Random rand = new Random();
            int rNum2 = rand.nextInt(2);
            if (rNum2 == 0){
                avoided = true;
                int changeX = 0, changeY = 0, rNum;
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
                    {
                        Organism potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
                        if (potentialCollision == null || (xPos + changeX == attackingCreature.GetX() && yPos + changeY == attackingCreature.GetY()) )
                        {
                            xPos += changeX;
                            yPos += changeY;
                            return true;
                        }
                    }
                    else {
                        changeX = 0;
                        changeY = 0;
                    }
                }
            }
        }
        return false;
    }
    @Override
    public void Win(Organism otherCreature)
    {
        if (avoided) {
            System.out.print(" and " + name + " ran away! It went to tile (" + xPos + ", " + yPos + ")" + '\n');
            log = log + " and " + name + " ran away! It went to tile (" + xPos + ", " + yPos + ")" + '\n';
            avoided = false;
        }
        else {
            System.out.print(" and " + name + " won! " + otherCreature.GetName() + " was eaten" + '\n');
            log = log + " and " + name + " won! " + otherCreature.GetName() + " was eaten" + '\n';
            world.RmOrganism(otherCreature.GetOId());
            world.AddLog(otherCreature.GetLog());
            otherCreature.ResetLog();
            otherCreature.SetAge(DEAD);
        }
    }
    @Override
    public void TakeAction() {
        if (age != DEAD && !moved)
        {
            int changeX = 0, changeY = 0, rNum, rNum2;
            while (true)
            {
                Random rand = new Random();
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
                rNum2 = rand.nextInt(4);
                if (rNum2 == 0) {
                    changeX += -1;
                }
                else if (rNum2 == 1) {
                    changeX += 1;
                }
                else if (rNum2 == 2) {
                    changeY += -1;
                }
                else {
                    changeY += 1;
                }
                if (xPos + changeX < world.GetW() && yPos + changeY < world.GetH() &&  xPos + changeX >= 0 && yPos + changeY >= 0 && (changeX != 0 || changeY != 0))
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
            if (age != DEAD && avoided == false)
            {
                potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY); // recheck if collision changed the state of disputed tile
                if (potentialCollision == null)
                {
                    int tmpx = xPos + changeX;
                    int tmpy = yPos + changeY;
                    System.out.print(name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n');
                    log = log + name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n';
                    xPos += changeX;
                    yPos += changeY;
                }
            }
            moved = true;
            avoided = false;
        }
        world.AddLog(log);
        log = " ";
        if (age > 0) age++;
    }
    @Override
    public void Collision(Organism defendingCreature) {
        if (defendingCreature.GetSId() == speciesId)
        {
            System.out.print(name + " from tile (" + xPos + ", " + yPos + ") encountered a mate on tile (" + defendingCreature.GetX() + ", " + defendingCreature.GetY() + ")");
            log = log + name + " from tile (" + xPos + ", " + yPos + ") encountered a mate on tile (" + defendingCreature.GetX() + ", " + defendingCreature.GetY() + ")";
            if (defendingCreature.HasMoved()) {
                System.out.print(", but the mate has already moved this turn" + '\n');
                log = log + ", but the mate has already moved this turn" + '\n';
            }
            else {
                Procreate();

                Animal defendingCreatureCast = (Animal)defendingCreature;
                System.out.print(defendingCreatureCast.GetName() + " on tile(" + defendingCreature.GetX() + ", " + defendingCreature.GetY() + ") tries spawning their offspring too");
                log = log + defendingCreatureCast.GetName() + " on tile(" + defendingCreature.GetX() + ", " + defendingCreature.GetY() + ") tries spawning their offspring too";
                defendingCreatureCast.Procreate();
                defendingCreature.SetHasMoved(true);
            }
        }
        else
        {
            System.out.print(name + " from tile (" + xPos + ", " + yPos + ") encountered a " + defendingCreature.GetName() + " on tile (" + defendingCreature.GetX() + ", " + defendingCreature.GetY() + ") ");
            log = log + name + " from tile (" + xPos + ", " + yPos + ") encountered a " + defendingCreature.GetName() + " on tile (" + defendingCreature.GetX() + ", " + defendingCreature.GetY() + ") ";
            if (!defendingCreature.Defended(this))
                Win(defendingCreature);
            else
            {
                Random rand = new Random();
                int rNum3 = rand.nextInt(2);
                if (rNum3 == 0)
                    defendingCreature.Win(this);
                else
                {
                    System.out.print(name + " tries to run away, ");
                    log = log + name + " tries to run away, ";
                    int rNum2 = rand.nextInt(2);
                    if (rNum2 == 0)
                    {
                        int rNum;
                        boolean triedLeft = false, triedRight = false, triedUp = false, triedDown = false;
                        while (true)
                        {
                            int changeX = 0, changeY = 0;
                            rNum = rand.nextInt(4);
                            if (rNum == 0) {
                                if (triedLeft)
                                    continue;
                                else
                                    triedLeft = true;
                                changeX = -1;
                            }
                            else if (rNum == 1) {
                                if (triedRight)
                                    continue;
                                else
                                    triedRight = true;
                                changeX = 1;
                            }
                            else if (rNum == 2) {
                                if (triedUp)
                                    continue;
                                else
                                    triedUp = true;
                                changeY = -1;
                            }
                            else {
                                if (triedDown)
                                    continue;
                                else
                                    triedDown = true;
                                changeY = 1;
                            }
                            if (xPos + changeX < world.GetW() && yPos + changeY < world.GetH() &&  xPos + changeX >= 0 && yPos + changeY >= 0)
                            {
                                Organism potentialCollision = world.LookForCollision(defendingCreature.GetX() + changeX, defendingCreature.GetY() + changeY);
                                if (potentialCollision == null)
                                {
                                    avoided = true;
                                    break;
                                }
                            }
                            else {
                                changeX = 0;
                                changeY = 0;
                            }
                            if (triedDown && triedUp && triedLeft && triedRight)
                            {
                                System.out.print("but has nowhere to run to " + '\n');
                                log = log + "but has nowhere to run to " + '\n';
                                break;
                            }
                        }
                    }
                    if (avoided) {
                        System.out.print("and succeeds!");
                        log = log + "and succeeds!";
                        Win(defendingCreature);
                    }
                    else {
                        System.out.print("and fails!");
                        log = log + "and fails!";
                        defendingCreature.Win(this);

                    }
                }
            }
        }
    }
    private boolean avoided;
}
