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
public class PetDemo3 {
    public static void main(String[] args) {

        // Dog is a subclass of Pet, so it is a subtype of Pet.
        // So, wherever a Pet is needed, a dog can be used.
        Pet myPet = new Dog("Isaak", 12785);

        if (ThreadLocalRandom.current().nextBoolean()) {
            myPet = new Cat("Muffin");
        }
        // If we know that myPet will refer to a Dog, we can perform a downcast in
        // order to invoke fetchStick.
        Dog dog = (Dog) myPet;
        dog.fetchStick();

        myPet.speak(); // late binding enables runtime polymorphism
    }
}
