import java.awt.*;
abstract public class Organism
{
    public Organism(int x, int y, World w)
    {
        xPos = x;
        yPos = y;
        world = w;
    }

    public Organism(int s, int i, int x, int y, int a, int oid, boolean m, World w)
    {
        str = s;
        ini = i;
        xPos = x;
        yPos = y;
        age = a;
        oId = oid;
        moved = m;
        world = w;
    }

    public abstract void Win(Organism otherCreature);
    public abstract boolean Defended(Organism attackingCreature);
    public abstract void TakeAction();
    public abstract void Print();

    public int GetS() {
    return str;
}
    public void SetS(int strength) {
        str = strength;
    }
    public int GetI() {
    return ini;
}
    public int GetX() {
    return xPos;
}
    public int GetY() {
    return yPos;
}
    public int GetSId() {
        return speciesId;
    }
    public int GetOId() {
        return oId;
    }
    public void SetOId(int oid) {
        oId = oid;
    }
    public int GetAge() {
        return age;
    }
    public void SetAge(int a) {
        age = a;
    }
    public boolean HasMoved() {
        return moved;
    }
    public void SetHasMoved(boolean m) {
        moved = m;
    }
    public String GetLog() {
        return log;
    }
    public void ResetLog() {
        log = " ";
    }
    public String GetName() {
        return name;
    }
    protected int str, ini, xPos, yPos, age = 0, speciesId, oId;
    protected World world;
    protected char sign;
    protected Color color;
    protected String name;
    protected boolean moved = true;
    public final int DEAD = -1;
    protected String log = " ";
};
