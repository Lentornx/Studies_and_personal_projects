import java.awt.*;

public class Dandelion extends Plant{
    public Dandelion(int x, int y, World world)
    {super(x,y,world);
        sign = 'D';
        color = Color.YELLOW;
        name = "Dandelion";
        str = 0;
        speciesId = 8;
        spreadChance = 10;
        spreadCount = 3;
    }
    public Dandelion(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);
        sign = 'D';
        name = "Dandelion";
        speciesId = 8;
        spreadChance = 30;
        spreadCount = 3;
        color = Color.YELLOW;
    }
    @Override
    public Plant MakeNewP(int x, int y) {
        Plant newPlant = new Dandelion(x, y, world);
        return newPlant;
    }
}
