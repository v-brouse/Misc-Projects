package edu.bloomu.chap10.sect7;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.input.KeyCode;
import javafx.scene.input.MouseButton;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 * A grid of colored cells updated over time to reflect states of a
 * predator-prey simulation. The user can advance the simulation by 
 * one unit of time by clicking the primary mouse button. The 
 * secondary mouse button toggles auto-update mode for animating
 * the passage of time; pressing the space bar has the same effect.
 *
 * @author Drue Coles
 */
public class WorldViewer extends Application {

   // constants for drawing
   private static final Color predatorColor = Color.DARKRED;
   private static final Color preyColor = Color.DARKGREEN;
   private static final Color emptyColor = Color.ALICEBLUE;
   private static final Color cellBorderColor = Color.LIGHTGRAY;
   private static final int cellSize = 6;
   private static final int padding = 2;

   private static final int size = 75; // size of simulated world
   
   // milliseconds between auto-updates
   private static final int delay = 75; 

   private final World world = new World(size);
   private final Rectangle[][] cells = new Rectangle[size][size];
   private Timeline timeline; // for auto-updates

   @Override
   public void start(Stage stage) {

      // Size of scene is determined by the size of the simulated 
      // world and a fixed size for the colored squares depicting 
      // creatures of the simulated world. 
      final int n = 2 * padding + size * cellSize;
      Pane root = new Pane();
      Scene scene = new Scene(root, n, n);

      // Initialize 2D array of rectangles to be filled at each step 
      // of the simulation with a color signifying the creature at 
      // the corresponding grid location. 
      for (int i = 0; i < size; i++) {
         for (int j = 0; j < size; j++) {
            int x = padding + i * cellSize;
            int y = padding + j * cellSize;
            cells[i][j] = new Rectangle(x, y, cellSize, cellSize);
            cells[i][j].setStroke(cellBorderColor);
            root.getChildren().add(cells[i][j]);
         }
      }
      showWorld(); // Draw the simulated world in its starting state.

      // Create animation for updates to the simulation.
      KeyFrame keyframe = new KeyFrame(Duration.millis(delay), e -> {
         world.tick();
         showWorld();
      });
      timeline = new Timeline(keyframe);
      timeline.setCycleCount(Timeline.INDEFINITE);
      timeline.pause();

      // Mouse click handler for updating the simulation.
      root.setOnMouseClicked(e -> {
         if (e.getButton() == MouseButton.PRIMARY) {
            timeline.pause();
            world.tick();
            showWorld();
         } else {
            toggleRunState();
         }
      });

      // Space bar to update the simulation.
      scene.setOnKeyPressed(e -> {
         if (e.getCode() == KeyCode.SPACE) {
            toggleRunState();
         }
      });

      stage.setTitle("Predator-Prey Simulation");
      stage.setScene(scene);
      stage.show();
      showInfo();
      stage.setAlwaysOnTop(true);
   }

   /**
    * Toggles animation timeline between running and paused states.
    */
   private void toggleRunState() {
      if (timeline.getStatus() == Timeline.Status.RUNNING) {
         timeline.pause();
      } else if (!world.isDead()) {
         timeline.play();
      }
   }

   /**
    * Fills each rectangle in the 2D array with a color depending on 
    * the creature at the corresponding position in the simulation.
    */
   private void showWorld() {
      for (int i = 0; i < size; i++) {
         for (int j = 0; j < size; j++) {
            Creature creature = world.get(i, j);
            if (creature == null) {
               cells[i][j].setFill(emptyColor);
            } else if (creature instanceof Predator) {
               cells[i][j].setFill(predatorColor);
            } else if (creature instanceof Prey) {
               cells[i][j].setFill(preyColor);
            }
         }
      }
   }

   /**
    * Produces an alert box with basic info about the simulation.
    */
   private static void showInfo() {
      String info
              = "Primary mouse button: advance one unit of time.\n"
              + "Right mouse button: toggle auto-update mode.";

      Alert alert = new Alert(AlertType.INFORMATION);
      alert.setTitle("Predator-Prey Simulation");
      alert.setHeaderText("RED = PREDATOR\nGREEN = PREY");
      alert.setContentText(info);
      alert.showAndWait();
   }

   public static void main(String[] args) {
      launch(args);
   }
}