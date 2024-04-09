import java.awt.*;

public class Wolf extends Animal{
    public Wolf(int x, int y, World world)
    {super(x,y,world);
        sign = 'W';
        name = "Wolf";
        color = Color.LIGHT_GRAY;
        str = 9;
        ini = 5;
        speciesId = 2;
    }
    public Wolf(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);
        sign = 'W';
        name = "Wolf";
        speciesId = 2;
        color = Color.LIGHT_GRAY;
    }
    @Override
    public Animal MakeNewA(int x, int y) {
        Animal newAnimal = new Wolf(x, y, world);
        return newAnimal;
    }
}
