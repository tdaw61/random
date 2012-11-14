/*This is the 2nd interface for Taylor Daw, 3402948
 * this takes a lot of code from the tutorials and then with some manipulation makes it all work out as planned.
 */


package hw3.p2;

import java.util.Calendar;
import android.widget.DatePicker;
import android.widget.TextView;
import android.widget.NumberPicker;
import android.widget.TimePicker;
import android.app.Activity;
import android.os.Bundle;
import android.widget.Button;
import android.view.View;



public class Hw3_2Activity extends Activity {

	
	private Button button1;
	private TextView from;
	private TextView to;
	
	private DatePicker date1;
	private TimePicker time1;
	private NumberPicker num1;
	private NumberPicker num2;
	 
		@Override
		public void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState);
			
			setContentView(R.layout.main);
			
			from = (TextView) findViewById(R.id.from);
			to = (TextView) findViewById(R.id.to);
			button1 = (Button) findViewById(R.id.button1);
			date1 = (DatePicker) findViewById(R.id.datePicker1);
			time1 = (TimePicker) findViewById(R.id.timePicker1);
			num1 = (NumberPicker) findViewById(R.id.numberPicker1);
			num2 = (NumberPicker) findViewById(R.id.numberPicker2);
			
			//get rid of extra calendar in 4.0.3
			date1.setCalendarViewShown(false);
			//set click listener
		    button1.setOnClickListener(new View.OnClickListener()
		    {
		       public void onClick(View v)
		       {
		    	   if (date1.getYear() < 2012 || date1.getYear() >= 2004)
		    	   {
		             		           
		    	   
			    	   if (date1.getYear() == 2012)
			    	   {
			    		   	if ((date1.getMonth()+1) < 4)
			    		   	{
			    		   		
					            update();
			    		   		
			    		   	}
			    		   	
			    		   	else if ((date1.getMonth()+1) == 4)
			    		   	{
			    		   		if ((date1.getDayOfMonth() < 28))
			    		   		{
			    		   			
						            update();
			    		   		}
			    		   	}
			    	   }
		    	   }
		       }
		    });
	        //set all of the constraints
	        date1.init(2012, 4, 27, null);
	        time1.setCurrentHour(23);
	        time1.setCurrentMinute(59);    	
	        num1.setValue(4);
	        num2.setValue(0);
	        num1.setMinValue(0);
	        num2.setMinValue(0);
	        num1.setMaxValue(47);
	        num2.setMaxValue(59);

	        
		}
		
		//append the to from string
		private void update() 
		{
			from.setText(new StringBuilder().append("From: ")
					.append(date1.getMonth() + 1).append("-")
					.append(date1.getDayOfMonth()).append("-")
					.append(date1.getYear()).append(" , ")
					.append(time1.getCurrentHour()).append(":")
					.append(pad(time1.getCurrentMinute())));
			int minute = time1.getCurrentMinute() + num2.getValue();
			int hour = time1.getCurrentHour() + num1.getValue();
			
			Calendar c = Calendar.getInstance();
			c.set(date1.getYear(), date1.getMonth() + 1, date1.getDayOfMonth());
			
			while (minute >= 60)
			{	
				minute-=60;
				hour++;
			}
			
			while (hour >= 24)
			{
				hour-=24;
				c.add(Calendar.DATE, 1);
			}
			
			to.setText(new StringBuilder()
					.append("To: ")
					.append(c.get(Calendar.MONTH)).append("-")
					.append(c.get(Calendar.DAY_OF_MONTH)).append("-")
					.append(c.get(Calendar.YEAR)).append(" , ")
					.append(hour).append(":")
					.append(pad(minute)));
		        
		        
		        }
		

		
		//helper class to prevent times returning as 1:5 instead of 1:05
		private static String pad(int c)
		{
			if (c >= 10)
				return String.valueOf(c);
		    else
		        return "0" + String.valueOf(c);
		}

		 
	}
