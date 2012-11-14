package hw3.pack;

import java.util.Calendar;

import android.app.Activity;
import android.app.DatePickerDialog;
import android.app.Dialog;
import android.app.TimePickerDialog;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.TextView;
import android.widget.TimePicker;

public class Hw3Activity extends Activity {
    private TextView mDateDisplay;
    private Button mPickDate;
    private int mYear;
    private int mMonth;
    private int mDay;
    //private boolean change = false;
	int old_month;
	int old_day;
	int old_Year;
	int old_Hour;
	int old_minute;
    //TimePickerDialog.OnTimeSetListener mTimeSetListener;
    
    private TextView mTimeDisplay;
    //private Button mPickTime;

    private int mHour;
    private int mMinute;

    static final int TIME_DIALOG_ID = 1;

    static final int DATE_DIALOG_ID = 0;
    /** Called when the activity is first created. */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        // capture our View elements
        mDateDisplay = (TextView) findViewById(R.id.dateDisplay);
        mPickDate = (Button) findViewById(R.id.pickDate);
        // capture our View elements
        mTimeDisplay = (TextView) findViewById(R.id.timeDisplay);
        //mPickTime = (Button) findViewById(R.id.pickTime);

        // add a click listener to the button
        /*mPickTime.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                showDialog(TIME_DIALOG_ID);
            }
        });*/

        // get the current time
        final Calendar c = Calendar.getInstance();
        mHour = c.get(Calendar.HOUR_OF_DAY);
        mMinute = c.get(Calendar.MINUTE);

        // add a click listener to the button
        mPickDate.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                showDialog(DATE_DIALOG_ID);
            }
        });

        // get the current date
        //final Calendar c = Calendar.getInstance();
        mYear = c.get(Calendar.YEAR);
        mMonth = c.get(Calendar.MONTH);
        mDay = c.get(Calendar.DAY_OF_MONTH);
        mMonth = 3;
        mDay = 27;
        mYear = 2012;
        mHour = 12;
        mMinute = 0;
        
        
        mDateDisplay.setText(
        		
                new StringBuilder()
                        // Month is 0 based so add 1
                		.append("From: ")
                        .append("4").append("-")
                        .append(mDay).append("-")
                        .append(mYear).append(" ")
                        .append(pad(mHour)).append(":")
                        .append(pad(mMinute)));
            mTimeDisplay.setText(
                    new StringBuilder()
            			.append("To: ")
            			.append("4").append("-")
            			.append(mDay).append("-")
            			.append(mYear).append(" ")
            			.append("12").append(":")
            			.append("00"));

        // display the current date (this method is below)
        //updateDisplay();
    }
    
    // updates the date in the TextView
    private void updateDisplay() {

        mDateDisplay.setText(
            new StringBuilder()
                    // Month is 0 based so add 1
            		.append("From: ")
                    .append(old_month + 1).append("-")
                    .append(old_day).append("-")
                    .append(old_Year).append(" ")
                    .append(old_Hour).append(":")
                    .append(old_minute));
        mTimeDisplay.setText(
                new StringBuilder()
        			.append("To: ")
        			.append(mMonth + 1).append("-")
        			.append(mDay).append("-")
        			.append(mYear).append(" ")
        			.append(pad(mHour)).append(":")
        			.append(pad(mMinute)));

    }
    
    private static String pad(int c) {
        if (c >= 10)
            return String.valueOf(c);
        else
            return "0" + String.valueOf(c);
    }
    
    // the callback received when the user "sets" the date in the dialog
    private DatePickerDialog.OnDateSetListener mDateSetListener =
            new DatePickerDialog.OnDateSetListener() {

                public void onDateSet(DatePicker view, int year, 
                                      int monthOfYear, int dayOfMonth) {
                	old_Year = mYear;
                	old_month = mMonth;
                	old_day = mDay;

                    mYear = year;
                    mMonth = monthOfYear;
                    mDay = dayOfMonth;
                    showDialog(TIME_DIALOG_ID);

                     updateDisplay();
                }
            };
         // the callback received when the user "sets" the time in the dialog
            private TimePickerDialog.OnTimeSetListener mTimeSetListener =
                new TimePickerDialog.OnTimeSetListener() {
                    public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
                    	old_Hour = mHour;
                    	old_minute = mMinute;
                        mHour = hourOfDay;
                        mMinute = minute;
                        updateDisplay();
                        //change = true;
                    }
                };
            
            @Override
            protected Dialog onCreateDialog(int id) {
                switch (id) {
                case DATE_DIALOG_ID:
                    return new DatePickerDialog(this,
                                mDateSetListener,
                                mYear, mMonth, mDay);
                    
                case TIME_DIALOG_ID:
                     return new TimePickerDialog(this,
                              mTimeSetListener, mHour, mMinute, false);
                       }
                
                return null;
            }
            
}