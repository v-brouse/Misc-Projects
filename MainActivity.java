package edu.bloomu.hw2;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private final int rows = 5;
    private final int cols = 5;
    private static int moves = 0;


    private FrogsAndToads game;
    private final Button[][] buttons = new Button[rows][cols];

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        game =new FrogsAndToads(rows, cols);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //Set layout parameters for table rows
        TableLayout tableLayout = findViewById(R.id.table_layout);
        TableRow.LayoutParams tableRowParams = new TableRow.LayoutParams(
                TableRow.LayoutParams.WRAP_CONTENT, TableRow.LayoutParams.WRAP_CONTENT);

        //Calculate size of each square so that the board occupies 80% of the screen.
        int displayWidth = getResources().getDisplayMetrics().widthPixels;
        int displayHeight = getResources().getDisplayMetrics().heightPixels;
        int n = Math.min(displayWidth, displayHeight);
        int k = Math.max(rows, cols);
        int buttonSize = (8 * n / 10) / k;

        //Create table rows and add them to the table.
        for (int i = 0; i < rows; i++) {
            TableRow tableRow = new TableRow(this);
            tableRow.setLayoutParams(tableRowParams);

            //Add a button in each cell of this row.
            for (int j = 0; j < cols; j++) {
                buttons[i][j] = new Button(this);
                buttons[i][j].setTag(new int[]{i, j});
                buttons[i][j].setWidth(buttonSize);
                buttons[i][j].setHeight(buttonSize);
                buttons[i][j].setPadding(0, 0, 0, 40); //hack
                buttons[i][j].setTextSize(getResources().getDimension(R.dimen.text_size));
                buttons[i][j].setOnClickListener(this::move);
                tableRow.addView(buttons[i][j]);
            }
            tableLayout.addView(tableRow);
        }
        drawBoard();
    }

    private void drawBoard() {
        // for loop goes through the grid to place the empty space in the middle with
        // the frogs on top and toads on the bottom
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (game.toadSpot(i, j)) {
                    buttons[i][j].setText(R.string.toads);
                    buttons[i][j].setTextColor(Color.YELLOW);
                } else if (game.frogSpot(i, j)){
                    buttons[i][j].setText(R.string.frogs);
                    buttons[i][j].setTextColor(Color.RED);
                } else if (game.emptySpot(i, j)) {
                    buttons[i][j].setText(R.string.empty_space);
                    buttons[i][j].setTextColor(Color.BLACK);
                }
            }
        }
    }

    private void move(View view) {
        int[] tag = (int[]) view.getTag();
        if(game.checkMove(tag[0], tag[1])) {
            game.move(tag[0], tag[1]);
            drawBoard();
            moves++;

        } else {
            Toast.makeText(getApplicationContext(), R.string.invalid,
                    Toast.LENGTH_LONG).show();
        }
        if(game.over()) {
            AlertDialog.Builder build = new AlertDialog.Builder(this);
            build.setTitle(R.string.win).setMessage((R.string.you_won));
            build.setPositiveButton(R.string.okay, null);
            build.create().show();
        } else if (!game.canMove()) {
            AlertDialog.Builder build = new AlertDialog.Builder(this);
            build.setTitle(R.string.loss).setMessage(R.string.you_loss);
            build.setPositiveButton(R.string.okay, null);
            build.create().show();
        }
    }
    public void undo(View view) {
        game.undo();
        drawBoard();
    }

    public void beginning(View view) {
        while(moves != 0) {
            game.undo();
            moves--;
        }
        drawBoard();
    }
}
