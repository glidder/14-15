package es.uca.congreso;

//http://stackoverflow.com/questions/1851633/how-to-add-button-dynamically-in-android

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		switch (item.getItemId()) {
			case R.id.MnuCom:
				Intent intentComite = new Intent(MainActivity.this,ComiteActivity.class);
				startActivity(intentComite);
				return true;
			case R.id.MnuPro:
				Intent intentProgram = new Intent(MainActivity.this,ProgramActivity.class);
				startActivity(intentProgram);
				return true;
			case R.id.MnuDat:
				Intent intentDates = new Intent(MainActivity.this,DatesActivity.class);
				startActivity(intentDates);
				return true;
			case R.id.MnuLoc:
				Intent intentLocation = new Intent(MainActivity.this,LocationActivity.class);
				startActivity(intentLocation);
				return true;
			case android.R.id.home:
				return true;
			default:
				return super.onOptionsItemSelected(item);
		}
	}
}
