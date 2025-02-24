import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;

import java.util.concurrent.ThreadLocalRandom;

/**
 * (9.9.3g)
 *
 * @author Vanessa Brouse
 */
public class RainDrops extends Application {

    private Circle circle = new Circle();

    @Override
    public void start(Stage stage) {
        StackPane root = new StackPane();
        final int width = 500;
        final int height = 300;
        Scene scene = new Scene(root, width, height, Color.BLACK);

        scene.addEventHandler(MouseEvent.MOUSE_CLICKED, (MouseEvent me) -> {
            int randRadius = ThreadLocalRandom.current().nextInt(20, 101);
            if(me.getButton().equals(MouseButton.PRIMARY)) {
                Circle circle = new Circle(me.getX(), me.getY(), randRadius, Color.GREEN);
                root.getChildren().addAll(circle);
            }
        });

//        class MouseHandler implements EventHandler<MouseEvent> {
//            @Override
//            public void handle(MouseEvent mouseEvent) {
//                int randRadius = ThreadLocalRandom.current().nextInt(20, 101);
//                double x = mouseEvent.getX();
//                double y = mouseEvent.getY();
//                Circle circle = new Circle(x, y, randRadius, Color.GREEN);
//                root.getChildren().addAll(circle);
//            }
//        }


        stage.setTitle("Raindrops");
        stage.setAlwaysOnTop(true);
        stage.setScene(scene);
        stage.show();
    }
    public static void main(String[] args) {
        launch(args);
    }
}
