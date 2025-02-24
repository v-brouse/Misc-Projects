package edu.bloomu.chap10.sect7;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

/**
 * Moves to evade predators and reproduces at each tick of discrete 
 * time with a fixed probability. All prey start life with a single 
 * unit of energy. Food is abundant, so energy is never lost. Prey 
 * dies only when eaten by a predator.
 *
 * @author Drue Coles
 */
public class Prey extends Creature {

   private static final double breedingProb = 0.75;

   /**
    * Creates new prey with a single unit of energy.
    */
   public Prey() {
      super(1);
   }

   /**
    * Returns a new child with fixed probability.
    */
   @Override
   public Prey reproduce() {
      ThreadLocalRandom rand = ThreadLocalRandom.current();
      return !isDead() && rand.nextDouble() < breedingProb 
              ? new Prey() : null;
   }

   /**
    * Returns a randomly selected direction to an unoccupied 
    * adjacent cell if one exists (or null if all adjacent cells 
    * are occupied).
    */
   @Override
   public Direction move(Creature[] neighbors) {

      if (isDead()) {
         return null;
      }

      List<Direction> directionsToUnoccupied = new ArrayList<>();

      // For each direction, check if the adjacent cell in that 
      // direction is empty. 
      for (Direction dir : Direction.values()) {
         if (neighbors[dir.ordinal()] == null) {
            directionsToUnoccupied.add(dir);
         }
      }

      // If the list of directions to unoccupied cells is not empty, 
      // choose a direction at random from this list. 
      if (!directionsToUnoccupied.isEmpty()) {
         int i = ThreadLocalRandom.current().nextInt(
                 directionsToUnoccupied.size());
         return directionsToUnoccupied.get(i);
      }

      // Neighboring cells are occupied, so movement is impossible.
      return null; 
   }
}