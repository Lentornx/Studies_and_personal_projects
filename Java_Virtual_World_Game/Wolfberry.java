import java.awt.*;

public class Wolfberry extends Plant{
    public Wolfberry(int x, int y, World world)
    {super(x,y,world);
        sign = 'B';
        name = "Wolfberry";
        color = Color.CYAN;
        str = 10;
        speciesId = 9;
        spreadChance = 20;
        spreadCount = 1;
    }
    public Wolfberry(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);
        sign = 'B';
        name = "Wolfberry";
        speciesId = 9;
        spreadChance = 5;
        spreadCount = 1;
        color = Color.CYAN;
    }
    @Override
    public Plant MakeNewP(int x, int y) {
        Plant newPlant = new Wolfberry(x, y, world);
        return newPlant;
    }
}
