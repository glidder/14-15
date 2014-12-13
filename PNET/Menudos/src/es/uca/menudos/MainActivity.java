package es.uca.menudos;

import java.lang.reflect.Method;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.widget.TextView;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		getActionBar().setDisplayHomeAsUpEnabled(true);
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
		final TextView textView = (TextView)findViewById(R.id.MyTextView);
		//int id = item.getItemId();
		switch (item.getItemId()) {
		case R.id.MnuOpc1:
			Intent intentUndo = new Intent(MainActivity.this,UndoActivity.class);
			startActivity(intentUndo);
			return true;
		case R.id.MnuOpc2:
			Intent intentRedo = new Intent(MainActivity.this,RedoActivity.class);
			startActivity(intentRedo);
			return true;
		case android.R.id.home:
			return true;
		default:
			return super.onOptionsItemSelected(item);}
	}
}
