package es.uca.menudos;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

public class UndoActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_undo);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.undo, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		switch (item.getItemId()) {
		case R.id.MnuOpc1:
			return true;
		case R.id.MnuOpc2:
			Intent intentRedo = new Intent(UndoActivity.this,MainActivity.class);
			startActivity(intentRedo);
			return true;
		case android.R.id.home:
			Intent intentHome = new Intent(UndoActivity.this,MainActivity.class);
			startActivity(intentHome);
			return true;
		default:
			return super.onOptionsItemSelected(item);}
	}
}
