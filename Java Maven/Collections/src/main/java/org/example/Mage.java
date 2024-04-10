package org.example;
import java.util.*;
public class Mage implements Comparable<Mage>{
    public Mage (String name, int level, double power) {
        this.name = name;
        this.level = level;
        this.power = power;
    }
    @Override
    public int compareTo(Mage o) {
        int nameComp = this.name.compareTo(o.name);
        if (nameComp < 0) return -1;
        else if (nameComp > 0) return 1;

        if(this.level < o.level) return -1;
        else if (this.level > o.level) return 1;

        if(this.power > o.power) return 1;
        return -1;
    }
    @Override
    public String toString() {
        return "Mage{name='"+name+"', level="+level+", power="+power+"}";
    }
    public void Print(int depth,String j) {


        for (int i = 0; i < depth; i++) {
            System.out.print(" ");
        }
        System.out.print(j + ". ");

        System.out.println(this.toString());

        Integer jA=0;
        if(apprentices != null)
            for (Mage apprentice : apprentices) {
                jA++;
                apprentice.Print(depth+1, j+"."+jA.toString());
            }
    }
    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Mage)
        {
            Mage other = (Mage)obj;
            if(this.hashCode() == other.hashCode()) return true;
        }
        return false;
    }
    @Override
    public int hashCode() {
        int hash = 59 * Double.hashCode(level) + 13 * Double.hashCode(power) + 11 * name.hashCode() + 7;
        if(apprentices != null)
            for (Mage apprentice: apprentices) {
                hash = hash + apprentice.hashCode();
            }
        return hash;
    }

    public void insertToMap( Map<Mage, Integer> map) {
        map.put(this, this.getDescendants());
        if(apprentices != null)
            for (Mage apprentice: apprentices) {
                apprentice.insertToMap(map);
            }
    }
    public Integer getDescendants() {
        Integer desc = 0;
        if(apprentices != null) {
            desc = apprentices.size();
            for (Mage apprentice : apprentices) {
                desc = desc + apprentice.getDescendants();
            }
        }
        return desc;
    }
    public String getName() { return name; }
    public int getLevel() { return level; }
    public double getPower() { return power; }
    public Set<Mage> getSet() { return apprentices; }
    public void setSet(Set<Mage> set) {
        apprentices = set;
    }
    private String name;
    private int level;
    private double power;
    private Set<Mage> apprentices;
}
