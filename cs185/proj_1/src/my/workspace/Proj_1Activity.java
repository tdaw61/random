//@author Taylor Daw


package my.workspace;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;


	public class Proj_1Activity extends Activity {
		int counter = 0;
		TextView text;
		String texter;
	   /** Called when the activity is first created. */
	   @Override
	   public void onCreate(Bundle savedInstanceState) {
	       super.onCreate(savedInstanceState);
			setContentView(R.layout.main);
		
		    text = (TextView) findViewById(R.id.textView1);
	   }
	   public void clicker(View view) {
    	   counter++;
    	   text.setText("you have clicked " + String.valueOf(counter) + " times");
       }
	}