package edu.bloomu.chap10.sect7;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

/**
 * Hunts for prey and reproduces until death by starvation.
 *
 * @author Drue Coles
 */
public class Predator extends Creature {

   private static final int initEnergy = 4;
   private static final int energyToReproduce = 12;

   /**
    * Creates a new predator.
    */
   public Predator() {
      super(initEnergy);
   }

   /**
    * Returns a new predator if this one is able to reproduce.
    */
   @Override
   public Predator reproduce() {
      return energy < energyToReproduce ? null : new Predator();
   }

   /**
    * Returns preferred direction of movement according to the 
    * following rule:
    *
    * 1. If there is prey in at least one neighboring cell, choose 
    * at random among directions leading to prey.
    *
    * 2. If there is no prey in neighboring cells, choose at random 
    * an empty cell if one is available.
    *
    * 3. If there are no empty cells, then all neighbors are 
    * predators. In this case, return null to signify no movement.
    */
   @Override
   public Direction move(Creature[] neighbors) {

      if (isDead()) {
         return null;
      }

      // directions to unoccupied cells and to cells with prey
      List<Direction> directionsToUnoccupied = new ArrayList<>();
      List<Direction> directionsToPrey = new ArrayList<>();

      // For each direction, check if the adjacent cell in that 
      // direction is empty or contains prey, and update lists 
      // accordingly. 
      for (Direction dir : Direction.values()) {
         if (neighbors[dir.ordinal()] == null) {
            directionsToUnoccupied.add(dir);
         }
         if (neighbors[dir.ordinal()] instanceof Prey) {
            directionsToPrey.add(dir);
         }
      }

      // If the list of directions to cells with prey is not empty, 
      // choose a direction at random from this list. In this case, 
      // this predator eats and gains a unit of energy.
      ThreadLocalRandom rand = ThreadLocalRandom.current();
      if (!directionsToPrey.isEmpty()) {
         energy++;
         return directionsToPrey.get(
                 rand.nextInt(directionsToPrey.size()));
      }

      // This predator does not eat, so it loses a unit of energy. 
      energy--;

      // If the list of directions to unoccupied cells is not empty, 
      // choose a direction  at random from this list. 
      if (!directionsToUnoccupied.isEmpty()) {
         return directionsToUnoccupied.get(
                 rand.nextInt(directionsToUnoccupied.size()));
      }

      // If all 4 neighboring cells are occupied by predators, no
      // movement is possible.
      return null;
   }
}