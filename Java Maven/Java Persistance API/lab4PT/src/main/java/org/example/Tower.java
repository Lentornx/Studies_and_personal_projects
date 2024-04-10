package org.example;
import javax.persistence.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
@Entity
@Table(name = "TOWERS")
public class Tower {
    @Id
    private String name;
    private int height;
    @OneToMany(mappedBy = "tower", fetch = FetchType.EAGER)
    private List<Mage> mages = new LinkedList<Mage>();

    Tower(){}
    Tower(String n, int h) {
        name = n;
        height = h;
    }

    public void setHeight(int height) {
        this.height = height;
    }
    public void setName(String towerName) {
        name = towerName;
    }
    public List<Mage> getMages() {
        return mages;
    }
    public String getName() {
        return name;
    }

    public int getHeight() {
        return height;
    }
}
