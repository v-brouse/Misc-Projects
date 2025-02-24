package edu.bloomu.chap10.sect7;

/**
 * A creature that can move and reproduce on a two-dimensional grid.
 *
 * @author Drue Coles
 */
public abstract class Creature {

   public enum Direction {
      NORTH, EAST, SOUTH, WEST;
   }

   protected int energy;

   /**
    * Constructs a new creature with a given energy level.
    */
   public Creature(int energy) {
      this.energy = energy;
   }

   /**
    * Returns this creature's preferred direction of movement given 
    * a list of creatures in the four neighboring cells.
    */
   abstract Direction move(Creature[] neighbors);

   /**
    * Returns a new creature of the same type or null if this 
    * creature is not able to reproduce.
    */
   abstract Creature reproduce();

   /**
    * Returns true if this creature is dead (no energy).
    */
   public boolean isDead() {
      return energy < 1;
   }
}