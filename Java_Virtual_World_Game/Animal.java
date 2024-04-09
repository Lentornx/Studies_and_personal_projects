import java.util.Random;

abstract public class Animal extends Organism {
    public Animal(int x, int y, World world)
    {super(x,y,world);}
    public Animal(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);}

    abstract public Animal MakeNewA(int x, int y);
    @Override
    public void Win(Organism otherCreature)
    {
        System.out.print(" and " + name + " won! " + otherCreature.GetName() + " was eaten" + '\n');
        log = log + " and " + name + " won! " + otherCreature.GetName() + " was eaten" + '\n';
        world.RmOrganism(otherCreature.GetOId());
        world.AddLog(otherCreature.GetLog());
        otherCreature.ResetLog();
        otherCreature.SetAge(DEAD);
    }
    @Override
    public boolean Defended(Organism attackingCreature) {
        if (str > attackingCreature.GetS())
            return true;
        return false;
    }

    public void Procreate() {
        int rNum;
        boolean triedLeft = false, triedRight = false, triedUp = false, triedDown = false;
        while (true)
        {
            Random rand = new Random();
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
                Organism potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
                if (potentialCollision == null)
                {
                    Animal newAnimal = MakeNewA(xPos + changeX, yPos + changeY);
                    world.AddOrganism(newAnimal);
                    int tmpx = xPos + changeX;
                    int tmpy = yPos + changeY;
                    System.out.print(" and spawned offspring on tile (" + tmpx + ", " + tmpy + ")" + '\n');
                    break;
                }
            }
            if (triedDown && triedUp && triedLeft && triedRight)
            {
                System.out.print(", but had no adjacent tiles to spawn offspring to" + '\n');
                break;
            }
        }
    }
    @Override
    public void TakeAction() {
        if (age != DEAD && !moved)
        {
            int changeX = 0, changeY = 0, rNum;
            Random rand = new Random();
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
                    System.out.print(name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n');
                    log = log + name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n';
                    xPos += changeX;
                    yPos += changeY;
                }
            }
            moved = true;
        }
        world.AddLog(log);
        log = " ";
        if (age>0) age++;
    }

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
                System.out.print(defendingCreatureCast.GetName() + " on tile(" + defendingCreature.GetX() + ", " + defendingCreature.GetY() + ") tried too");
                log = log + defendingCreatureCast.GetName() + " on tile(" + defendingCreature.GetX() + ", " + defendingCreature.GetY() + ") tried too";
                defendingCreatureCast.Procreate();
                defendingCreature.SetHasMoved(true);
            }
        }
        else
        {
            System.out.print(name + " from tile (" + xPos + ", " + yPos + ") encountered a " + defendingCreature.GetName() + " on tile (" + defendingCreature.GetX() + ", " + defendingCreature.GetY() + ")");
            log = log + name + " from tile (" + xPos + ", " + yPos + ") encountered a " + defendingCreature.GetName() + " on tile (" + defendingCreature.GetX() + ", " + defendingCreature.GetY() + ")";
            if (defendingCreature.Defended(this))
                defendingCreature.Win(this);
            else
                Win(defendingCreature);
        }
    }
    @Override
    public void Print() {
        world.SetMap(xPos, yPos, sign, color);
    }
}
