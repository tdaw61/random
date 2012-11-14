//@author Taylor Daw
package my.pack;


import android.app.Activity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.FrameLayout;
import android.view.View;
import android.widget.TextView;

public class Proj_2Activity extends Activity {
    /** Called when the activity is first created. */
	int counter = 0;
	TextView text;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        LinearLayout layout = new LinearLayout(this);

        final Button button = new Button(this);
        button.setText("Click Me!");
        text = new TextView(this);
        text.setText("you clicked " + counter + " times. \n");
        layout.addView(text);
        layout.addView(button);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                // Perform action on click
            	counter++;
            	text.setText("you clicked " + counter + " times.");
            }
        });
	    setContentView(layout);

    }

}