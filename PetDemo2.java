package edu.bloomu.chap10.sect5;

import edu.bloomu.chap10.sect3.Cat;
import edu.bloomu.chap10.sect3.Dog;
import edu.bloomu.chap10.sect3.Pet;

import java.util.concurrent.ThreadLocalRandom;

/**
 * Illustrates the concept of upcasting.
 *
 * @author
 */
public class PetDemo2 {
    public static void main(String[] args) {

        // Dog is a subclass of Pet, so it is a subtype of Pet.
        // So, wherever a Pet is needed, a dog can be used.
        Pet myPet = new Dog("Isaak", 12785);

        if (ThreadLocalRandom.current().nextBoolean()) {
            myPet = new Cat("Muffin");
        }
        // The following would not compile.
        //     myPet.fetchStick();
        //
        // Why not?

        myPet.speak();
    }
}
