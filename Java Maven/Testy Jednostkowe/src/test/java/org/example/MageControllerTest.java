package org.example;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.Optional;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

public class MageControllerTest {
    private MageRepository mockRepository;
    private MageController controller;

    @BeforeEach
    public void setUp() {
        mockRepository = mock(MageRepository.class);
        controller = new MageController(mockRepository);
    }

    @Test
    public void testSave() {
        assertEquals("done", controller.save("Merlin", 10));
    }

    @Test
    public void testSaveDuplicate() {
        doThrow(IllegalArgumentException.class).when(mockRepository).save(any(Mage.class));
        assertEquals("bad request", controller.save("Merlin", 10));
    }

    @Test
    public void testDelete() {
        assertEquals("done", controller.delete("Merlin"));
    }

    @Test
    public void testDelete2() {
        doThrow(IllegalArgumentException.class).when(mockRepository).delete(any(String.class));
        assertEquals("not found", controller.delete("Merlin"));
    }

    @Test
    public void testFind() {
        when(mockRepository.find("Merlin")).thenReturn(Optional.of(new Mage("Merlin", 10)));
        assertEquals("Merlin - Level 10", controller.find("Merlin"));
    }

    @Test
    public void testFindNotFound() {
        when(mockRepository.find("Gandalf")).thenReturn(Optional.empty());
        assertEquals("not found", controller.find("Gandalf"));
    }
}
