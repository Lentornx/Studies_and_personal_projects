import java.awt.*;

public class Sheep extends Animal{
    public Sheep(int x, int y, World world)
    {super(x,y,world);
        sign = 'S';
        name = "Sheep";
        color = Color.WHITE;
        str = 4;
        ini = 4;
        speciesId = 1;
    }
    public Sheep(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);
        sign = 'S';
        name = "Sheep";
        speciesId = 1;
        color = Color.WHITE;
    }
    @Override
    public Animal MakeNewA(int x, int y) {
        Animal newAnimal = new Sheep(x, y, world);
        return newAnimal;
    }
}
