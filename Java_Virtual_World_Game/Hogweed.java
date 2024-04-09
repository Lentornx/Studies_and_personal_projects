import java.awt.*;
import java.util.Random;

public class Hogweed extends Plant{
    public Hogweed(int x, int y, World world)
    {super(x,y,world);
        sign = 'H';
        name = "Hogweed";
        color = Color.DARK_GRAY;
        str = 99;
        speciesId = 10;
        spreadChance = 1;
        spreadCount = 1;
    }
    public Hogweed(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);
        sign = 'H';
        name = "Hogweed";
        speciesId = 10;
        spreadChance = 10;
        spreadCount = 1;
        color = Color.DARK_GRAY;
    }
    @Override
    public Plant MakeNewP(int x, int y) {
        Plant newPlant = new Hogweed(x, y, world);
        return newPlant;
    }
    @Override
    public void TakeAction() {
        if (!moved && age > 0)
        {
            int rNum, spreadsAttempted = 0;
            while (spreadsAttempted != spreadCount)
            {
                Random rand = new Random();
                rNum = rand.nextInt(100);
                System.out.print(name + " from tile (" + xPos + ", " + yPos + ") tried spreading");
                log = log + name + " from tile (" + xPos + ", " + yPos + ") tried spreading";
                if (rNum >= 99 - spreadChance)
                    Spread();
                else
                {
                    System.out.print(", but failed" + '\n');
                    log = log + ", but failed" + '\n';
                }
                spreadsAttempted++;
            }
            System.out.print(name + " from tile (" + xPos + ", " + yPos + ")is killing animals around it!" + '\n');
            log = log + name + " from tile (" + xPos + ", " + yPos + ")is killing animals around it!" + '\n';
            for(int changeX = -1; changeX <= 1;changeX ++)
                for (int changeY = -1; changeY <= 1; changeY ++)
                    if((changeX == 0 && changeY != 0) || (changeY == 0 && changeX != 0))
                        if (xPos + changeX < world.GetW() && yPos + changeY < world.GetH() &&  xPos + changeX >= 0 && yPos + changeY >= 0)
                        {
                            int tmpx = xPos + changeX;
                            int tmpy = yPos + changeY;
                            Organism potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
                            if (potentialCollision != null)
                                if (potentialCollision.GetI() != 0) // only animals have ini != 0
                                {
                                    System.out.print(potentialCollision.GetName()+ " from tile (" + tmpx + ", " +tmpy + ") perished" + '\n');
                                    log = log + potentialCollision.GetName()+ " from tile (" + tmpx + ", " +tmpy + ") perished" + '\n';
                                    world.RmOrganism(potentialCollision.GetOId());
                                }
                        }
            age++;
            world.AddLog(log);
            log = " ";
        }
    }
}
