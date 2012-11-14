package edu.ucsb.cs.cs185.hw4;



import java.util.Calendar;

import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.DatePicker;
import android.widget.NumberPicker;
import android.widget.TextView;
import android.widget.TimePicker;

public class lister extends Activity
{
	int fromYear = 2012, fromMonth = 4, fromDay = 27;
	int fromHour = 23, fromMinute = 59;
	int toYear = 2012, toMonth = 4, toDay = 27;
	int toHour = 23, toMinute = 59;
	
	ActionBar actionBar; 	
	
		
	TextView textFrom;
	TextView textTo;
	
	DatePicker datePicker;
	TimePicker timePicker;
	NumberPicker hourPicker;
	NumberPicker minutePicker;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        actionBar = getActionBar();
        

    	
        
        
        //textFrom = (TextView) findViewById(R.id.textFrom);
        //textTo = (TextView) findViewById(R.id.textTo);
        
        datePicker = (DatePicker) findViewById(R.id.datePicker);
        datePicker.init(fromYear, fromMonth, fromDay, null);
		datePicker.setMinDate(1072944000000L); // 1/1/2004 00:00 in epochs
		datePicker.setMaxDate(1335553140000L); // 4/27/2012 11:59 in epochs
		
        timePicker = (TimePicker) findViewById(R.id.timePicker);
        timePicker.setCurrentHour(23);
        timePicker.setCurrentMinute(59);
        
        hourPicker = (NumberPicker) findViewById(R.id.hourPicker);
        hourPicker.setMinValue(0);
        hourPicker.setMaxValue(47);
        hourPicker.setValue(0); 

        minutePicker = (NumberPicker) findViewById(R.id.minutePicker);
        minutePicker.setMinValue(0);
        minutePicker.setMaxValue(59);
        minutePicker.setValue(0);

        //UpdateDisplay();
    }
    
    
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu, menu);
        return true;
    }

    
    String DateTimeToString(int year, int month, int day, int hour, int minute)
    {
    	return (month + "-" + day + "-" + year + ", " + hour + ":" + String.format("%02d", minute));
    }
    
    void UpdateDisplay()
    {
    	String stringTemp = (
            	DateTimeToString(fromYear, fromMonth, fromDay, fromHour, fromMinute)
            	+ " - " + DateTimeToString(toYear, toMonth, toDay, toHour, toMinute));

            Intent returnIntent = new Intent();
            returnIntent.putExtra("time", stringTemp);
            setResult(RESULT_OK, returnIntent); 

            finish();
            	

    }
    
    public void buttonSetOnClick(View view)
    {
    	fromDay = datePicker.getDayOfMonth();
    	fromMonth = datePicker.getMonth() + 1;
    	fromYear = datePicker.getYear();
    	fromHour = timePicker.getCurrentHour();
    	fromMinute = timePicker.getCurrentMinute();

    	int duration = hourPicker.getValue() * 60 + minutePicker.getValue();
    	
    	Calendar calendar = Calendar.getInstance();
    	calendar.set(fromYear, fromMonth - 1, fromDay, fromHour, fromMinute);
    	calendar.add(Calendar.MINUTE, duration);
    	
    	toDay = calendar.get(Calendar.DATE);
    	toMonth = calendar.get(Calendar.MONTH) + 1;
    	toYear = calendar.get(Calendar.YEAR);
    	toHour = calendar.get(Calendar.HOUR_OF_DAY);
    	toMinute = calendar.get(Calendar.MINUTE);
    	
    	UpdateDisplay();
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.Home:     

				            	finish();
                                break;
            case R.id.settings: 
					        	AlertDialog.Builder alertbox2 = new AlertDialog.Builder(this);            	 
					            alertbox2.setMessage("no settings here!");
					        	alertbox2.show();
                                break;
            case R.id.help: 	
					        	AlertDialog.Builder alertbox3 = new AlertDialog.Builder(this);            	 
					            alertbox3.setMessage("Taylor Daw \n    4.0.3 \n");
					        	alertbox3.show();
                                break;
        }
        return true;
	
    }
    }