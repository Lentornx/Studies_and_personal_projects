package org.example;
import java.util.*;

public class Main {

    public static void main(String[] args) {

        Comparator<Mage> comparator = new Comparator<Mage>() {
            public int compare(Mage first, Mage second) {
                if(first.getLevel() < second.getLevel()) return -1;
                else if (first.getLevel() > second.getLevel()) return 1;

                int nameComp = first.getName().compareTo(second.getName());
                if (nameComp < 0) return -1;
                else if (nameComp > 0) return 1;

                if(first.getPower() > second.getPower()) return 1;
                return -1;
            }
        };

        Set<Mage> mainSet, subSetLen, subSetKing, subSetM3;
        Map<Mage, Integer> map;

        if (args.length > 0) {
            if (args[0].equals("sorted") ) {
                mainSet = new TreeSet<Mage>();
                subSetLen = new TreeSet<Mage>();
                subSetKing = new TreeSet<Mage>();
                subSetM3 = new TreeSet<Mage>();
                map = new TreeMap<Mage, Integer>();
            }
            else if (args[0].equals("sortedAlt")){
                mainSet = new TreeSet<Mage>(comparator);
                subSetLen = new TreeSet<Mage>(comparator);
                subSetKing = new TreeSet<Mage>(comparator);
                subSetM3 = new TreeSet<Mage>(comparator);
                map = new TreeMap<Mage, Integer>(comparator);
            }
            else {
                mainSet = new HashSet<Mage>();
                subSetLen = new HashSet<Mage>();
                subSetKing = new HashSet<Mage>();
                subSetM3 = new HashSet<Mage>();
                map = new HashMap<Mage, Integer>();
            }
        }
        else
        {
            mainSet = new HashSet<Mage>();
            subSetLen = new HashSet<Mage>();
            subSetKing = new HashSet<Mage>();
            subSetM3 = new HashSet<Mage>();
            map = new HashMap<Mage, Integer>();
        }

        Mage Len = new Mage("Lentornx", 20, 114.5);
        Mage King = new Mage("Kingodysey", 15, 87.25);
        mainSet.add(Len);
        mainSet.add(King);

        Mage m1 = new Mage("M1", 12, 76);
        Mage m2 = new Mage("M2", 13, 65);
        Mage m3 = new Mage("M3", 10, 42);
        Mage m4 = new Mage("M4", 14, 74);
        subSetLen.add(m1);
        subSetLen.add(m2);
        subSetLen.add(m3);
        subSetLen.add(m4);
        Len.setSet(subSetLen);

        Mage k1 = new Mage("K1", 4, 15);
        Mage k2 = new Mage("K2", 10, 45);
        Mage k3 = new Mage("K3", 7, 20);
        subSetKing.add(k1);
        subSetKing.add(k2);
        subSetKing.add(k3);
        King.setSet(subSetKing);

        Mage mm1 = new Mage("MM1", 3, 10);
        Mage mm2 = new Mage("MM2", 2, 14);
        subSetM3.add(mm1);
        subSetM3.add(mm2);
        m3.setSet(subSetM3);


        Integer j=0;
        for (Mage m: mainSet) {
            j++;
            m.Print(1,j.toString());
        }
        for (Mage m: mainSet
        ) {
            m.insertToMap(map);
        }
        for(Map.Entry<Mage,Integer> entry : map.entrySet())
        {
            System.out.println(entry.getKey() + " = " + entry.getValue());
        }
    }

}