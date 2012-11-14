package edu.ucsb.cs.cs185.hw4;

import java.util.ArrayList;

import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.ArrayAdapter;
import android.widget.ListView;



public class HW4Skeleton extends Activity{
	

	ActionBar actionBar; 	
	
	ArrayList<String> strings = new ArrayList<String>();
	String temp;
	static final int TIME_SELECT = 0;
	
	static ListView lv;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.list);
        actionBar = getActionBar();
        lv = (ListView) findViewById(R.id.mylist);
        

    }
    
    /*
    @Override
    public void onConfigurationChanged(Configuration newConfig) {
      super.onConfigurationChanged(newConfig);
      setContentView(R.layout.list);
      lv = (ListView) findViewById(R.id.mylist);
    }*/

    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.othermenu, menu);
        return true;
    }
    
    protected void onActivityResult(int requestCode, int resultCode, Intent data){

        switch (requestCode) {
            case TIME_SELECT:
                if (resultCode == RESULT_OK){
                	String name = data.getStringExtra("time");                	
                	strings.add(name);
                	String [] list = strings.toArray(new String[strings.size()]);                	
                	ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                    		android.R.layout.simple_list_item_1, android.R.id.text1, list);

                    lv.setAdapter(adapter);
                	break;
                } 
            default:
                break;
        }
    }
    
    @Override
    protected void onSaveInstanceState(Bundle outState) {
   
    	//outState.putAll(outState)
    	outState.putStringArrayList("lister", strings);


    super.onSaveInstanceState(outState);
    }
    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
    super.onRestoreInstanceState(savedInstanceState);
    if (savedInstanceState != null) {
    	strings = savedInstanceState.getStringArrayList("lister");

    }

    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.newentry:     
				            	Intent myIntent = new Intent(HW4Skeleton.this, lister.class);
				            	startActivityForResult(myIntent, TIME_SELECT);
                                break;
            case R.id.settings: 
					        	AlertDialog.Builder alertbox2 = new AlertDialog.Builder(this);            	 
					            alertbox2.setMessage("No settings over here!");
					        	alertbox2.show();
                                break;
            case R.id.help: 	
            	
					        	AlertDialog.Builder alertbox3 = new AlertDialog.Builder(this);            	 
					            alertbox3.setMessage("Taylor Daw \n    4.0.3 ");
					        	alertbox3.show();
                                break;
        }
        return true;
	
    }

	
}


