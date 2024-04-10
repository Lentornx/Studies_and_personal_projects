package org.example;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.Optional;

public class MageRepositoryTest {
    private MageRepository repository = new MageRepository();
    private Mage mage = new Mage("Merlin", 10);

    @Test
    public void testSave() {
        MageRepository repository2 = new MageRepository();
        Mage mage2 = new Mage("Merlin", 10);
        repository2.save(mage2);
        assertTrue(repository2.find("Merlin").isPresent());
    }

    @Test
    public void testDelete() {
        repository.save(mage);
        repository.delete("Merlin");
        assertFalse(repository.find("Merlin").isPresent());
    }

    @Test
    public void testDelete2() {
        repository.save(mage);
        repository.delete("Merlin");
        assertThrows(IllegalArgumentException.class, () -> repository.delete("Merlin"));
    }

    @Test
    public void testFind() {
        repository.save(mage);
        Optional<Mage> optionalMage = repository.find("Merlin");
        assertTrue(optionalMage.isPresent());
        assertEquals(mage, optionalMage.get());
    }

    @Test
    public void testSaveDuplicate() {
        repository.save(mage);
        assertThrows(IllegalArgumentException.class, () -> repository.save(mage));
    }
}

