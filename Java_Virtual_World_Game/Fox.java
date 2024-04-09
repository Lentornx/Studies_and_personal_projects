import java.awt.*;
import java.util.Random;

public class Fox extends Animal{
    public Fox(int x, int y, World world)
    {super(x,y,world);
        sign = 'F';
        color = Color.ORANGE;
        name = "Fox";
        str = 3;
        ini = 7;
        speciesId = 3;
    }
    public Fox(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);
        sign = 'F';
        name = "Fox";
        speciesId = 3;
        color = Color.ORANGE;
    }
    @Override
    public Animal MakeNewA(int x, int y) {
        Animal newAnimal = new Fox(x, y, world);
        return newAnimal;
    }
    public void TakeAction() {
        if (age != DEAD && !moved)
        {
            int changeX = 0, changeY = 0, rNum;
            boolean triedLeft = false, triedRight = false, triedUp = false, triedDown = false;
            while (true)
            {
                changeX = 0; changeY = 0;
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
                    int tmpx = xPos + changeX;
                    int tmpy = yPos + changeY;
                    Organism potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY);
                    if (potentialCollision != null)
                    {
                        if (potentialCollision.GetS() <= str)
                        {
                            Collision(potentialCollision);
                            potentialCollision = world.LookForCollision(xPos + changeX, yPos + changeY); // recheck if collision changed the state of disputed tile
                            if (potentialCollision == null)
                            {
                                System.out.print(name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n');
                                log = log + name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n';
                                xPos += changeX;
                                yPos += changeY;
                                break;
                            }
                        }
                    }
                    else
                    {
                        System.out.print(name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n');
                        log = log + name + " moved from tile (" + xPos + ", " + yPos + ") to tile (" + tmpx + ", " + tmpy + ")" + '\n';
                        xPos += changeX;
                        yPos += changeY;
                        break;
                    }
                }
                else {
                    changeX = 0;
                    changeY = 0;
                }
                if (triedDown && triedUp && triedLeft && triedRight)
                {
                    System.out.print(name + " from tile(" + xPos + ", " + yPos + "), but has nowhere safe to go!" + '\n');
                    log = log + name + " from tile(" + xPos + ", " + yPos + "), but has nowhere safe to go!" + '\n';
                    break;
                }
            }
            moved = true;
        }
        world.AddLog(log);
        log = " ";
        if (age > 0) age++;
    }}
