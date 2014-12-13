package com.uca.menus;



import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

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
	final TextView textView = (TextView)findViewById(R.id.MyTextView);
	switch (item.getItemId()) {
	case R.id.MnuOpc1:
	textView.setText("Undo!");
	return true;
	case R.id.MnuOpc2:
	textView.setText("Redo!");;
	return true;
	default:
	return super.onOptionsItemSelected(item);}
	}
}
