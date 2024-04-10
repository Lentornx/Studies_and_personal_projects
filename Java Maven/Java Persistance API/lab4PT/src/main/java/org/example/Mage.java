package org.example;
import javax.persistence.*;
@Entity
@Table(name = "MAGES")
public class Mage {
    @Id
    private String name;
    private int level;
    @ManyToOne
    @JoinColumn(name = "tower_name")
    private Tower tower;

    Mage(){}
    Mage(String name, int level, Tower tower_name) {
        this.name = name;
        this.level = level;
        this.tower = tower_name;
    }

    public void setName(String mageName) {
        name = mageName;
    }
    public void setLevel(int level) {
        this.level = level;
    }
    public void setTower(Tower tower) {
        this.tower = tower;
    }

    public String getName() {
        return name;
    }

    public int getLevel() {
        return level;
    }

    public Tower getTower() {
        return tower;
    }
}