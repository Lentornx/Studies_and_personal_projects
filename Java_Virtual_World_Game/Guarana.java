import java.awt.*;

public class Guarana extends Plant{
    public Guarana(int x, int y, World world)
    {super(x,y,world);
        sign = 'U';
        name = "Guarana";
        color = Color.GRAY;
        str = 0;
        speciesId = 7;
        spreadChance = 40;
        spreadCount = 1;
    }
    public Guarana(int str, int ini, int xPos, int yPos, int age, int oId, boolean moved, World world)
    {super(str, ini, xPos, yPos, age, oId, moved, world);
        sign = 'U';
        name = "Guarana";
        speciesId = 7;
        spreadChance = 10;
        spreadCount = 1;
        color = Color.GRAY;
    }
    @Override
    public Plant MakeNewP(int x, int y) {
        Plant newPlant = new Guarana(x, y, world);
        return newPlant;
    }
    @Override
    public boolean Defended(Organism attackingCreature) {
        int newStr = attackingCreature.GetS() + 3;
        attackingCreature.SetS(newStr);
        System.out.print(", which is granting strength upon being eaten,");
        if (str > attackingCreature.GetS())
            return true;
        return false;
    }
}
