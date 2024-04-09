import java.awt.*;
import java.util.Random;

public class Human extends Animal{
    public Human(int x, int y, World world)
    {super(x,y,world);
        sign = 'Y';
        name = "Human";
        color = Color.BLACK;
        str = 5;
        ini = 4;
        speciesId = 11;
    }
    public Human(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);
        sign = 'Y';
        name = "Human";
        speciesId = 11;
        color = Color.BLACK;
    }
    @Override
    public Animal MakeNewA(int x, int y) {
        return null;
    }

    public  int GetCd() {
        return cooldown;
    }
    public void SetCd(int cd) {
        cooldown = cd;
    }
    public  int GetP() {
        return powerLeft;
    }
    public void SetP(int p) {
        powerLeft = p;
    }

    public void SetAction(char ac) {
        action = ac;
    }

    public void TakeAction() {
        if (powerLeft > 0) {
            Random rand = new Random();
            int rNum = rand.nextInt(2);
            if (powerLeft >= 3 || rNum != 0) {
                specialActivated = true;
            }
            else {
                specialActivated = false;
            }
        }
        if (action == 'w')
            changeY--;
        else if (action == 's')
            changeY++;
        else if (action == 'a')
            changeX--;
        else if (action == 'd')
            changeX++;
        if(specialActivated) {
            changeX *= 2;
            changeY *= 2;
            if (action == 'q') {
                changeX--;
                changeY--;
            }
            if (action == 'e') {
                changeX++;
                changeY--;
            }
            if (action == 'z') {
                changeX--;
                changeY++;
            }
            if (action == 'c') {
                changeX++;
                changeY++;
            }
        }

        if (xPos + changeX < world.GetW() && yPos + changeY < world.GetH() &&  xPos + changeX >= 0 && yPos + changeY >= 0) {
            Organism potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
            if (potentialCollision != null) {
                Collision(potentialCollision);
            }
            if (age != DEAD) {
                potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
                if (potentialCollision == null) {
                    int tmpx = xPos + changeX;
                    int tmpy = yPos + changeY;
                    System.out.print(name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n');
                    log = log + name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n';
                    xPos += changeX;
                    yPos += changeY;
                }
            }
        }
            world.AddLog(log);
            log = " ";
            moved = true;
            if (age > 0) age++;
            if (cooldown > 0)
                cooldown--;
            if (powerLeft > 0)
                powerLeft--;
            changeX = 0;
            changeY = 0;
            specialActivated = false;
    }

    private int cooldown = 0, powerLeft = 0;
    private char action;
    private int changeX = 0, changeY = 0;
    private boolean specialActivated = false;
}
