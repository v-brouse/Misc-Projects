package edu.bloomu.chap10.sect5;

import edu.bloomu.chap10.sect3.Cat;
import edu.bloomu.chap10.sect3.Dog;
import edu.bloomu.chap10.sect3.GuardDog;
import edu.bloomu.chap10.sect3.Pet;

import java.security.Guard;
import java.util.concurrent.ThreadLocalRandom;

/**
 * Another example of a class cast exception.
 *
 * @author
 */
public class PetDemo5 {
    public static void main(String[] args) {

        // Dog is a subclass of Pet, so it is a subtype of Pet.
        // So, wherever a Pet is needed, a dog can be used.
        Pet myPet = new Dog("Isaak", 12785);

        GuardDog duke = new GuardDog("Duke", 24643, true);
        duke.attackIntruder();

        // The downcast is necessary for compilation.
        // But what happens at runtime?
        GuardDog duchess = (GuardDog) myPet;
        duchess.attackIntruder();
    }
}
