package org.example;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class MageRepository {
    private final Map<String, Mage> collection = new HashMap<>();

    public Optional<Mage> find(String name) {

        if(collection.containsKey(name))
            return Optional.ofNullable(collection.get(name));
        else return Optional.empty();
    }

    public void delete(String name) {
        if(!collection.containsKey(name))
            throw new IllegalArgumentException("such Mage doesn't exist");
        else collection.remove(name);

    }

    public void save(Mage mage) {
        if (collection.containsKey(mage.getName())) {
            throw new IllegalArgumentException("Mage with name " + mage.getName() + " already exists");
        }
        else
        collection.put(mage.getName(), mage);
    }
}