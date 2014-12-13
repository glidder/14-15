package es.uca.congreso;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

public class ComiteActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_comite);
		getActionBar().setDisplayHomeAsUpEnabled(true);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.comite, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		switch (item.getItemId()) {
		case R.id.MnuPro:
			Intent intentProgram = new Intent(ComiteActivity.this,ProgramActivity.class);
			startActivity(intentProgram);
			return true;
		case R.id.MnuDat:
			Intent intentDates = new Intent(ComiteActivity.this,DatesActivity.class);
			startActivity(intentDates);
			return true;
		case R.id.MnuLoc:
			Intent intentLocation = new Intent(ComiteActivity.this,LocationActivity.class);
			startActivity(intentLocation);
			return true;
		case android.R.id.home:
			return true;
		default:
			return super.onOptionsItemSelected(item);
		}
	}
}
