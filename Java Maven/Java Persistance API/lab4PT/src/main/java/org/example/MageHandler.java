package org.example;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.TypedQuery;
import javax.transaction.Transactional;
import java.util.List;

public class MageHandler {

    MageHandler(EntityManager entityManager) {
        this.entityManager = entityManager;
    }
    @PersistenceContext
    private EntityManager entityManager;

    @Transactional
    public void addMage(Mage mage, Tower tower) {
        mage.setTower(tower);
        tower.getMages().add(mage);
        entityManager.persist(mage);
    }

    @Transactional
    public void deleteMage(String name) {

        entityManager.remove(entityManager.find(Mage.class, name));
    }

    @Transactional
    public List<Mage> getMagesWithLevelGreaterThanFromTower(int level, String towerName) {
        TypedQuery<Mage> query = entityManager.createQuery(
                "SELECT m FROM Mage m WHERE m.tower.name = :towerName AND m.level > :level", Mage.class);
        query.setParameter("towerName", towerName);
        query.setParameter("level", level);
        return query.getResultList();
    }

    public List<Mage> getAllMagesFromTower(String towerName) {
        TypedQuery<Mage> query = entityManager.createQuery(
                "SELECT m FROM Mage m WHERE m.tower.name = :towerName", Mage.class);
        query.setParameter("towerName", towerName);
        return query.getResultList();
    }

    @Transactional
    public Mage getMageById(String id) {
        return entityManager.find(Mage.class, id);
    }
}

