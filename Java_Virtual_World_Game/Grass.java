import java.awt.*;

public class Grass extends Plant{
    public Grass(int x, int y, World world)
    {super(x,y,world);
        sign = 'G';
        color = Color.GREEN;
        name = "Grass";
        str = 0;
        speciesId = 6;
        spreadChance = 50;
        spreadCount = 1;
    }
    public Grass(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);
        sign = 'G';
        name = "Grass";
        speciesId = 6;
        spreadChance = 20;
        spreadCount = 1;
        color = Color.GREEN;
    }
    @Override
    public Plant MakeNewP(int x, int y) {
        Plant newPlant = new Grass(x, y, world);
        return newPlant;
    }
}
