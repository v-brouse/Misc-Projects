package edu.bloomu.chap10.sect5;

import edu.bloomu.chap10.sect3.Dog;
import edu.bloomu.chap10.sect3.Pet;

/**
 * Illustrates the concept of upcasting.
 *
 * @author
 */
public class PetDemo1 {
    public static void main(String[] args) {

        // Dog is a subclass of Pet, so it is a subtype of Pet.
        // So, wherever a Pet is needed, a dog can be used.
        Pet myPet = new Dog("Isaak", 12785);

        // The following would not compile.
        //     myPet.fetchStick();
        //
        // Why not?
    }
}
