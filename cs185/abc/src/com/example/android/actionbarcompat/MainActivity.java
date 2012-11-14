/*
 * Copyright 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/* Created by Taylor Daw
 * This is made up of many snippets of code borrowed from the forums and other code pointed to in the HW instructions.
 */
package com.example.android.actionbarcompat;

import android.app.AlertDialog;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageView;
import android.widget.ImageView.ScaleType;
import android.widget.Toast;

public class MainActivity extends ActionBarActivity {
	private boolean mAlternateTitle = false;
	// YOU CAN EDIT THIS TO WHATEVER YOU WANT
	private static final int SELECT_PICTURE = 1;

	private String selectedImagePath;
	// ADDED
	private String filemanagerstring;
	private static Bitmap bitmap;
	private touch myTV;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		 findViewById(R.id.toggle_title).setOnClickListener(new
		 View.OnClickListener() {
		 public void onClick(View view) {
		 if (mAlternateTitle) {
		 Toast.makeText(getApplicationContext(), "useless button", 15);
		 
		 } else {
		 setTitle("still useless");
		 }
		 mAlternateTitle = !mAlternateTitle;
		 }
		 });
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater menuInflater = getMenuInflater();
		menuInflater.inflate(R.menu.main, menu);

		// Calling super after populating the menu is necessary here to ensure
		// that the
		// action bar helpers have a chance to handle this event.
		return super.onCreateOptionsMenu(menu);
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case R.id.menu_pictures:
			Intent intent = new Intent();
			intent.setType("image/*");
			intent.setAction(Intent.ACTION_GET_CONTENT);
			startActivityForResult(Intent.createChooser(intent, "Select Picture"),SELECT_PICTURE);
			break;

		case R.id.menu_settings:
			AlertDialog.Builder alertbox2 = new AlertDialog.Builder(this);
			alertbox2.setMessage("No settings over here!");
			alertbox2.show();
			break;

		case R.id.menu_help:

			AlertDialog.Builder alertbox3 = new AlertDialog.Builder(this);
			alertbox3.setMessage("Taylor Daw \n    4.0.3 \n help menu... Not that helpful");
			alertbox3.show();
			break;

		}
		return super.onOptionsItemSelected(item);
	}

	
	
    public boolean onTouch(View v, MotionEvent event) {
		return false;
    	
    }
    		
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (resultCode == RESULT_OK) {
            if (requestCode == SELECT_PICTURE) {
                Uri selectedImageUri = data.getData();
                selectedImagePath = getPath(selectedImageUri);
                if(bitmap != null)
                bitmap.recycle();
              	bitmap = BitmapFactory.decodeFile(selectedImagePath);
                myTV = new touch(this,bitmap);
                setContentView(myTV);
                
            }
        }
    }

    public String getPath(Uri uri) {
        String[] projection = { MediaStore.Images.Media.DATA };
		@SuppressWarnings("deprecation")
		Cursor cursor = managedQuery(uri, projection, null, null, null);
        //Cursor cursor = CursorLoader(, uri, projection, null, null);
		//Loader<Cursor> = 
		
        int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
        cursor.moveToFirst();
        return cursor.getString(column_index);
    }

}
