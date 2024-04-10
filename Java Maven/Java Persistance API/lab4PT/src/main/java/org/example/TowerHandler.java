package org.example;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.transaction.Transactional;
import java.util.List;

public class TowerHandler {

    TowerHandler(EntityManager entityManager) {
        this.entityManager = entityManager;
    }

    @PersistenceContext
    private EntityManager entityManager;

    @Transactional
    public void addTower(Tower tower) {
        entityManager.persist(tower);
    }

    @Transactional
    public void deleteTower(String towerName, MageHandler mageHandler) {
        Tower tower = entityManager.find(Tower.class, towerName);
        if (tower != null) {
            List<Mage> mages = mageHandler.getAllMagesFromTower(tower.getName());
            for (Mage mage : tower.getMages()) {
                entityManager.remove(mage);
            }
            entityManager.remove(tower);
        }
    }

    @Transactional
    public Tower getTowerById(String id) {
        return entityManager.find(Tower.class, id);
    }

    @Transactional
    public List<Tower> getAllTowers() {
        return entityManager.createQuery("SELECT DISTINCT t FROM Tower t", Tower.class).getResultList();
    }
}

