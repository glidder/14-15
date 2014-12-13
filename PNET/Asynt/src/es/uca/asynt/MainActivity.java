package es.uca.asynt;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.protocol.BasicHttpContext;
import org.apache.http.protocol.HttpContext;
import org.apache.http.util.EntityUtils;

import android.app.Activity;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.drawable.BitmapDrawable;
import android.media.RingtoneManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.NotificationCompat;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
	
	private ProgressBar pbarProgreso;
	private Button btnIniciar;
	private Button btnCancelar;
	private Button btnToastc;
	private Button btnToastl;
	private Button btnToastp;
	private Button btnNotificar;
	private MiTareaAsincrona tarea1;
	private TextView muestraResultado;
	private Button btnInvocar;
	private static final int NOTIF_ALERTA_ID = 1;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		btnIniciar = (Button)findViewById(R.id.BtnIniciar);
		btnCancelar = (Button)findViewById(R.id.BtnCancelar);
		btnToastc = (Button)findViewById(R.id.BtnToastc);
		btnToastl = (Button)findViewById(R.id.BtnToastl);
		btnToastp = (Button)findViewById(R.id.BtnToastp);
		btnNotificar = (Button)findViewById(R.id.BtnNotifica);
		pbarProgreso=(ProgressBar)findViewById(R.id.pbarProgreso);
		btnIniciar.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
			tarea1 = new MiTareaAsincrona();
			tarea1.execute();
			}
			});
		btnCancelar.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
			tarea1.cancel(true);}
			});
		btnInvocar=(Button)findViewById(R.id.BtnInvocar);
		btnInvocar.setOnClickListener(new View.OnClickListener()
		{
		@Override
		public void onClick(View view) {
		new LongRunningGetIO().execute(); }
		});
		btnToastc.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				Toast toast1 =
				Toast.makeText(getApplicationContext(),
				"Toast por defecto", Toast.LENGTH_SHORT);
				toast1.show();
			}
		});
		btnToastl.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				Toast toast1 =
				Toast.makeText(getApplicationContext(),
				"Toast largo con gravity", Toast.LENGTH_LONG);
				toast1.setGravity(Gravity.CENTER|Gravity.LEFT,0,0);
				toast1.show();
			}
		});
		btnToastp.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				Toast toast3 = new Toast(getApplicationContext());
				LayoutInflater inflater = getLayoutInflater();
				View layout = inflater.inflate(R.layout.toast_layout,
				(ViewGroup) findViewById(R.id.toastLayout));
				TextView txtMsg = (TextView)layout.findViewById(R.id.txtMensaje);
				txtMsg.setText("Toast Personalizado");
				toast3.setDuration(Toast.LENGTH_SHORT);
				toast3.setView(layout);
				toast3.show();
			}
		});
		btnNotificar.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				NotificationCompat.Builder notificacion =
						new NotificationCompat.Builder(MainActivity.this)
						.setSmallIcon(android.R.drawable.stat_sys_warning)
						.setLargeIcon((((BitmapDrawable)getResources()
						.getDrawable(R.drawable.ic_launcher)).getBitmap()))
						.setContentTitle("Mensaje de Alerta")
						.setContentText("Ejemplo de notificación.")
						.setContentInfo("4")
						.setTicker("Alerta!");
				notificacion.setSound(RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION));
				notificacion.setAutoCancel (true);
				Intent notIntent = new Intent(MainActivity.this, MainActivity.class);
				PendingIntent contIntent = PendingIntent.getActivity(MainActivity.this,0, notIntent,0);
				notificacion.setContentIntent(contIntent);
				NotificationManager mNotificationManager = (NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
				mNotificationManager.notify(NOTIF_ALERTA_ID, notificacion.build());
			}
		});
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
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	private void tareaLarga()
	{
		try {Thread.sleep(1000);} catch(InterruptedException e) {}
	}
	
	private class LongRunningGetIO extends AsyncTask <Void,
	Void, String> {
		@Override
		protected String doInBackground (Void... params){
			HttpClient httpClient = new DefaultHttpClient();
			HttpContext localContext = new BasicHttpContext();
			HttpGet httpGet = new HttpGet("http://10.182.152.50:8080/HelloWorld/demo/hello/");
			String text = null;
			try { HttpResponse response = httpClient.execute(httpGet, localContext);
			HttpEntity entity = response.getEntity();
			text=EntityUtils.toString(entity);
			} catch (Exception e) { return e.toString(); }
			return text;
		}
		protected void onPostExecute(String results) { 
			if (results!=null) {
				muestraResultado=(TextView)findViewById(R.id.result);
				muestraResultado.setText(results);}
		}
	}
	private class MiTareaAsincrona extends AsyncTask <Void,
	Integer, Boolean> {
		@Override
		protected Boolean doInBackground(Void... params) {
		for(int i=1; i<=10; i++) {
		tareaLarga();
		publishProgress(i*10);
		if(isCancelled())
		break;
		}
		return true; }
		@Override
		protected void onProgressUpdate(Integer... values) {
		int progreso = values[0].intValue();
		pbarProgreso.setProgress(progreso);
		}
		@Override
		protected void onPreExecute()
		{
		pbarProgreso.setMax(100);
		pbarProgreso.setProgress(0); }
		@Override
		protected void onPostExecute(Boolean result)
		{
		if(result) Toast.makeText(MainActivity.this,
		"Tarea finalizada",Toast.LENGTH_SHORT).show();}
		@Override
		protected void onCancelled() {
		Toast.makeText(MainActivity.this, "Tarea cancelada!",
		Toast.LENGTH_SHORT).show();
		}
	}
}
