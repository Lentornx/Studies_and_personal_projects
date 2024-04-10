package org.example;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        EntityManagerFactory entityManagerFactory = Persistence.createEntityManagerFactory("myPersistenceUnit");
        EntityManager entityManager = entityManagerFactory.createEntityManager();

        Tower tower1 = new Tower();
        tower1.setName("Tower1");
        tower1.setHeight(100);

        Mage mage1 = new Mage();
        mage1.setName("Mage1");
        mage1.setLevel(10);
        mage1.setTower(tower1);

        Mage mage2 = new Mage();
        mage2.setName("Mage2");
        mage2.setLevel(20);
        mage2.setTower(tower1);

        TowerHandler towerHandler = new TowerHandler(entityManager);
        MageHandler mageHandler = new MageHandler(entityManager);

        entityManager.getTransaction().begin();
        towerHandler.addTower(tower1);
        mageHandler.addMage(mage1, tower1);
        mageHandler.addMage(mage2, tower1);
        entityManager.getTransaction().commit();

        Tower tower2 = new Tower();
        tower2.setName("Tower2");
        tower2.setHeight(150);

        Mage mage3 = new Mage();
        mage3.setName("Mage3");
        mage3.setLevel(15);
        mage3.setTower(tower2);

        Mage mage4 = new Mage();
        mage4.setName("Mage4");
        mage4.setLevel(25);
        mage4.setTower(tower2);

        Mage mage5 = new Mage();
        mage5.setName("Mage5");
        mage5.setLevel(35);
        mage5.setTower(tower2);

        entityManager.getTransaction().begin();
        towerHandler.addTower(tower2);
        mageHandler.addMage(mage3, tower2);
        mageHandler.addMage(mage4, tower2);
        mageHandler.addMage(mage5, tower2);
        entityManager.getTransaction().commit();
        Scanner input = new Scanner(System.in);

        while (true) {

            System.out.println("1. add an element");
            System.out.println("2. remove an element");
            System.out.println("3. print tables");
            System.out.println("4. print all mages with level above N");
            System.out.println("5. print all mages with level above N from tower T");
            System.out.println("6. quit");

            int command = input.nextInt();
            if(command == 1) {
                System.out.println("1. add a mage");
                System.out.println("2. add a tower");
                command = input.nextInt();
                System.out.println("provide a name");
                String name = input.next();
                if(command == 1)
                {
                    System.out.println("provide the level");
                    int level = input.nextInt();
                    System.out.println("provide an existing tower's name");
                    String towerName = input.next();
                    Tower tower = towerHandler.getTowerById(towerName);
                    Mage mage = new Mage(name,level,tower);
                    entityManager.getTransaction().begin();
                    mageHandler.addMage(mage,tower);
                    entityManager.getTransaction().commit();
                }
                else if (command == 2)
                {
                    System.out.println("provide the height");
                    int height = input.nextInt();
                    Tower tower = new Tower(name,height);
                    entityManager.getTransaction().begin();
                    towerHandler.addTower(tower);
                    entityManager.getTransaction().commit();
                }
            }
            else if (command == 2) {
                System.out.println("1. remove a mage");
                System.out.println("2. remove a tower");
                command = input.nextInt();
                System.out.println("provide a name");
                String name = input.next();

                if(command == 1) {
                    entityManager.getTransaction().begin();
                    mageHandler.deleteMage(name);
                    entityManager.getTransaction().commit();
                }
                else if(command == 2) {
                    entityManager.getTransaction().begin();
                    towerHandler.deleteTower(name,mageHandler);
                    entityManager.getTransaction().commit();
                }

            }
            else if (command == 3) {
                List<Tower> towers = towerHandler.getAllTowers();
                for (Tower tower : towers) {
                    List<Mage> mages = mageHandler.getAllMagesFromTower(tower.getName());
                    System.out.println("Tower Name: " + tower.getName() + ", Height: " + tower.getHeight());
                    for (Mage mage : mages) {
                        System.out.println("    Mage Name: " + mage.getName() + ", Level: " + mage.getLevel());
                    }
                }
            }

            else if (command == 4) {

                System.out.println("provide the level");
                int level = input.nextInt();
                List<Mage> magesWithLevelGreaterThanN = entityManager.createQuery(
                        "SELECT m FROM Mage m WHERE m.level > :level", Mage.class).setParameter("level", level).getResultList();

                System.out.println("Mages with level greater than "+level+":");
                for (Mage mage : magesWithLevelGreaterThanN) {
                    System.out.println("Name: " + mage.getName() + ", Level: " + mage.getLevel());
                }
            }

            else if (command == 5) {
                System.out.println("provide the level");
                int level = input.nextInt();
                System.out.println("provide the tower's name");
                String towerName = input.next();
                List<Mage> answerList = mageHandler.getMagesWithLevelGreaterThanFromTower(level, towerName);
                System.out.println("Mages with level greater than "+level+" from "+towerName+":");
                for (Mage mage : answerList) {
                    System.out.println("Name: " + mage.getName() + ", Level: " + mage.getLevel());
                }
            }
            else if (command == 6) break;
        }

        entityManager.close();
        entityManagerFactory.close();
    }
}
