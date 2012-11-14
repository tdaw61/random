/* This is part 3 for Taylor Daw, 3402948
 * There is a lot of use of code from the library and custom widget, along with bits and pieces taken from the other two parts
 * 
 * 
 */

package me.pack;

import java.util.Calendar;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import kankan.wheel.R;
import kankan.wheel.widget.adapters.NumericWheelAdapter;
import kankan.wheel.widget.OnWheelChangedListener;
import kankan.wheel.widget.WheelView;
import kankan.wheel.widget.adapters.ArrayWheelAdapter;


public class Hw3_3rdActivity extends Activity {
    /** Called when the activity is first created. */
	
	private Button button;
	private TextView from;
	private TextView to;
	private WheelView month;
	private WheelView year;
	private WheelView hours_2;
	private WheelView mins_2;
	private WheelView day;
	private WheelView ampm;
	private WheelView hours_1;
	private WheelView mins_1;
	private WheelView hours;
	private boolean change = false;
	
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        
        hours_2 = (WheelView) findViewById(R.id.hour2);
        mins_2 = (WheelView) findViewById(R.id.mins2);
        day = (WheelView) findViewById(R.id.day);
        hours_1 = (WheelView) findViewById(R.id.hour1);
        mins_1 = (WheelView) findViewById(R.id.mins1);
        from = (TextView) findViewById(R.id.from);
		to = (TextView) findViewById(R.id.to);
        year = (WheelView) findViewById(R.id.year);
        ampm = (WheelView) findViewById(R.id.ampm);
        button = (Button) findViewById(R.id.button1);    
        month = (WheelView) findViewById(R.id.month);
         
        
        ArrayWheelAdapter<String> am_pm =
            new ArrayWheelAdapter<String>(this, new String[] {"AM", "PM"});
        ampm.setViewAdapter(am_pm);
        
        NumericWheelAdapter hour_1 = new NumericWheelAdapter(this, 1, 12, "%02d");
        hours_1.setViewAdapter(hour_1);
        hours_1.setCurrentItem(10);
    
        NumericWheelAdapter min_1 = new NumericWheelAdapter(this, 0, 59, "%02d");
        mins_1.setViewAdapter(min_1);
        mins_1.setCyclic(true);
        mins_1.setCurrentItem(59);
        
        NumericWheelAdapter hour_2 = new NumericWheelAdapter(this, 0, 47, "%02d");
        hours_2.setViewAdapter(hour_2);
        hours_2.setCurrentItem(3);
    
        NumericWheelAdapter min_2 = new NumericWheelAdapter(this, 0, 59, "%02d");
        mins_2.setViewAdapter(min_2);
        mins_2.setCurrentItem(0);
        mins_2.setCyclic(true);
        
        OnWheelChangedListener listener = new OnWheelChangedListener() {
            public void onChanged(WheelView wheel, int oldValue, int newValue) {
                updateDays(year, month, day);
            }
        };

        NumericWheelAdapter monthAdapter = new NumericWheelAdapter(this, 1, 12, "%02d");
        month.setViewAdapter(monthAdapter);
        month.setCurrentItem(3);
        month.addChangingListener(listener);
        month.setCyclic(true);
        
        NumericWheelAdapter yearAdapter = new NumericWheelAdapter(this, 2004, 2012, "%04d");
        year.setViewAdapter(yearAdapter);
        year.setCurrentItem(2018);
        year.addChangingListener(listener);
        
        
        button.setOnClickListener(new View.OnClickListener()
	    {
	       public void onClick(View v)
	       {
	             update();
	       }
	    });
        
        updateDays(year, month, day);
        day.setCurrentItem(25);
    }
    
    void updateDays(WheelView year, WheelView month, WheelView day) {
    	
        Calendar calendar = Calendar.getInstance();
        calendar.set(Calendar.YEAR, calendar.get(Calendar.YEAR) + year.getCurrentItem());
        calendar.set(Calendar.MONTH, month.getCurrentItem());
        int maxDays = calendar.getActualMaximum(Calendar.DAY_OF_MONTH);
        
        NumericWheelAdapter dayAdapter = new NumericWheelAdapter(this, 1, maxDays);
        day.setViewAdapter(dayAdapter);

        day.setCurrentItem(0);
    }
    
    private void update() 
	{
		Calendar c = Calendar.getInstance();
		
		from.setText(new StringBuilder().append("From: ")
				.append(month.getCurrentItem()+1).append("-")
				.append(day.getCurrentItem()+1).append("-")
				.append(c.get(Calendar.YEAR) + year.getCurrentItem() - 8).append(" , ")
				.append(hours_1.getCurrentItem()+1).append(":")
				.append(pad(mins_1.getCurrentItem())));
		
		int minute = mins_1.getCurrentItem() + mins_2.getCurrentItem();
		int hour = hours_1.getCurrentItem() + hours_2.getCurrentItem() + 1;
		
		c = Calendar.getInstance();
		c.set(c.get(Calendar.YEAR) + year.getCurrentItem() - 8, month.getCurrentItem()+1, day.getCurrentItem()+1);
		
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