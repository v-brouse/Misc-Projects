package edu.bloomu.chap10.sect7;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

/**
 * A population of predator and prey creatures on a toroidal grid.
 *
 * @author Drue Coles
 */
public class World {

   // default values for randomizing initial population
   private static final double defaultPredatorProb = 0.05;
   private static final double defaultPreyProb = 0.20;

   // world represented by an (size x size) array of creatures 
   private final int size;
   private final Creature[][] world;

   /**
    * Creates a grid of a given size with predators and prey 
    * distributed at random using default probabilities, but 
    * client code can invoke the randomize method to populate 
    * the grid using specified probabilities.
    *
    * @param size the number cells in a row or column
    */
   public World(int size) {
      this.size = size;
      world = new Creature[size][size];
      randomize(defaultPredatorProb, defaultPreyProb);
   }

   /**
    * Randomizes the population.
    *
    * @param p1 probability of predator in a cell
    * @param p2 probability of prey in a cell
    */
   public final void randomize(double p1, double p2) {

      // If the probabilities are invalid, use default value of 1/2.
      if (p1 < 0 || p2 < 0 || p1 + p2 > 1) {
         p1 = 0.50;
         p2 = 0.50;
      }

      // Populate each cell using the given probabilities.
      for (int row = 0; row < size; row++) {
         for (int col = 0; col < size; col++) {
            double p = ThreadLocalRandom.current().nextDouble();
            if (p < p1) {
               world[row][col] = new Predator();
            } else if (p < p1 + p2) {
               world[row][col] = new Prey();
            } else {
               world[row][col] = null; // unoccupied
            }
         }
      }
   }

   /**
    * Returns a reference to occupant of a given position in grid.
    */
   public Creature get(int row, int col) {
      // A row or column might be negative since the grid is a 
      // torus, so we map each index into the range [0, size - 1].
      int x = (row + size) % size;
      int y = (col + size) % size;
      return world[x][y];
   }

   /**
    * Copies a creature (or null) to specified position within grid.
    */
   public void set(Creature creature, int row, int col) {
       // A row or column might be negative since the grid is a 
      // torus, so we map each index into the range [0, size-1].
      row = (row + size) % size;
      col = (col + size) % size;
      world[row][col] = creature;
   }

   /**
    * Returns a list of references to the neighbors of a specified 
    * cell in the enumeration order for Direction. A null value 
    * signifies an empty cell.
    */
   private Creature[] getNeighbors(int row, int col) {
      return new Creature[]{
         get(row - 1, col), // north
         get(row, col + 1), // east
         get(row + 1, col), // south
         get(row, col - 1) // west
      };
   }

   /**
    * Updates the simulated world to the next generation.
    */
   public void tick() {

      // locations of predators and prey currently in the grid
      List<int[]> preyLocations = new ArrayList<>();
      List<int[]> predatorLocations = new ArrayList<>();

      for (int row = 0; row < size; row++) {
         for (int col = 0; col < size; col++) {

            Creature creature = world[row][col];
            if (creature == null || creature.isDead()) {
               world[row][col] = null;
               continue;
            }

            // Add living creature to the correct list.
            if (creature instanceof Prey) {
               preyLocations.add(new int[]{row, col});
            }
            if (creature instanceof Predator) {
               predatorLocations.add(new int[]{row, col});
            }
         }
      }

      // Let prey move first, then predators move.
      move(preyLocations);
      move(predatorLocations);
   }

   /**
    * Given a list of locations of creatures, selects one at random 
    * and removes it from list. The creature at that location moves
    * if possible. This process is repeated until list is empty.
    */
   private void move(List<int[]> locations) {
      ThreadLocalRandom rand = ThreadLocalRandom.current();
      while (locations.size() > 0) {
         int k = rand.nextInt(locations.size());
         int[] location = locations.get(k);
         locations.remove(location);
         moveCreatureAt(location[0], location[1]);
      }
   }

   /**
    * The creature at a specified location moves if possible and 
    * leaves behind offspring if able to reproduce.
    */
   private void moveCreatureAt(int row, int col) {

      Creature creature = world[row][col];
      Creature.Direction dir = creature.move(getNeighbors(row, col));

      if (dir != null) { // able to move
         switch (dir) {
            case NORTH:
               set(creature, row - 1, col);
               break;
            case EAST:
               set(creature, row, col + 1);
               break;
            case SOUTH:
               set(creature, row + 1, col);
               break;
            case WEST:
               set(creature, row, col - 1);
               break;
         }

         // Leave offspring behind (null if unable to reproduce).
         set(creature.reproduce(), row, col);
      }
   }

   /**
    * Returns true if there are no living creatures in the world.
    */
   public boolean isDead() {
      for (int i = 0; i < size; i++) {
         for (int j = 0; j < size; j++) {
            if (world[i][j] != null) {
               return false;
            }
         }
      }
      return true;
   }
}