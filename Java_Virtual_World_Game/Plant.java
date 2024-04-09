import java.util.Random;

abstract public class Plant extends Organism {
    public Plant(int x, int y, World world)
    {super(x,y,world);
        ini = 0;}
    public Plant(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);}

    abstract public Plant MakeNewP(int x, int y);
    @Override
    public void TakeAction() {
        if (!moved && age > 0)
        {
            int rNum, spreadsAttempted = 0;
            while (spreadsAttempted != spreadCount)
            {
                Random rand = new Random();
                rNum = rand.nextInt(100);
                System.out.print( name + " from tile (" + xPos + ", " + yPos + ") tried spreading");
                log = log + name + " from tile (" + xPos + ", " + yPos + ") tried spreading";
                if (rNum >= 99 - spreadChance)
                    Spread();
                else {
                    System.out.print(", but failed" + '\n');
                    log = log + ", but failed" + '\n';
                }
                spreadsAttempted++;
            }
            age++;
        }
    }
    @Override
    public void Win(Organism otherCreature) {
        System.out.print( " and " + otherCreature.GetName() + " died while eating it! Both perished" + '\n');
        log = log + " and " + otherCreature.GetName() + " died while eating it! Both perished" + '\n';
        world.RmOrganism(otherCreature.GetOId());
        world.RmOrganism(oId);
        otherCreature.SetAge(DEAD);
        world.AddLog(log);
        world.AddLog(otherCreature.log);
        otherCreature.ResetLog();
        log = " ";
        age = DEAD;
    }
    @Override
    public boolean Defended(Organism attackingCreature) {
        if (str > attackingCreature.GetS())
            return true;
        return false;
    }

    public void Spread() {
        boolean triedLeft = false, triedRight = false, triedUp = false, triedDown = false;
        while (true)
        {
            int changeX = 0, changeY = 0, rNum;
            Random rand = new Random();
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
                Organism potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
                if (potentialCollision == null)
                {
                    Plant newPlant = MakeNewP(xPos + changeX, yPos + changeY);
                    world.AddOrganism(newPlant);
                    int tmpx = xPos + changeX;
                    int tmpy = yPos + changeY;
                    System.out.print( " and spread to tile (" + tmpx + ", " + tmpy + ")" + '\n');
                    log = log + " and spread to tile (" + tmpx + ", " + tmpy + ")" + '\n';
                    break;
                }
            }
            else {
                changeX = 0;
                changeY = 0;
            }
            if (triedDown && triedUp && triedLeft && triedRight)
            {
                System.out.print( ", but had no adjacent tiles to spread to" + '\n');
                log = log + ", but had no adjacent tiles to spread to" + '\n';
                break;
            }
        }
        world.AddLog(log);
        log = " ";
    }
    @Override
    public void Print() {
        world.SetMap(xPos, yPos, sign, color);
    }
    protected int spreadCount, spreadChance;
}
