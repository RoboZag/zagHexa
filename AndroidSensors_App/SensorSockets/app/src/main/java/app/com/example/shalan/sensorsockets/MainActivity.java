package app.com.example.shalan.sensorsockets;

import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectOutputStream;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;

public class MainActivity extends AppCompatActivity implements SensorEventListener {
    TextView ip,port,msg,x,y,z ;
    String message = "" ;
    ServerSocket serverSocket;
    Sensor acc_sensor ;
    SensorObject acc_sen ;
    SensorManager sensorManager ;
    float _x ,_y,_z ;
    Socket socket ;
    BufferedReader buffer ;
    String whichSensor = "G";

    @Override
    protected void onResume() {
        super.onResume();
        sensorManager.registerListener(this,acc_sensor,sensorManager.SENSOR_DELAY_NORMAL) ;

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ip = (TextView) findViewById(R.id.ip);
        port = (TextView) findViewById(R.id.port);
        msg = (TextView) findViewById(R.id.msg);
        x = (TextView) findViewById(R.id.x);
        y = (TextView) findViewById(R.id.y);
        z = (TextView) findViewById(R.id.z);

        acc_sen = new SensorObject() ;
        ip.setText(Utility.getIpAddress());

        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        acc_sensor = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

        Thread ServerThread = new Thread(new serverSocket());
        ServerThread.start();

    }

    @Override
    public void onSensorChanged(SensorEvent sensorEvent) {
        float[] values = sensorEvent.values ;
        _x = values[0];
        _y = values[1];
        _z = values[2];

        x.setText(Float.toString(_x) );
        y.setText(Float.toString(_y)  );
        z.setText(Float.toString(_z) );
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {

    }

    private class serverSocket extends Thread{
        final static int ServerPort = 2017 ;

        @Override
        public void run() {
            super.run();
            try {
                serverSocket = new ServerSocket(ServerPort) ;
                port.setText("Port :" + serverSocket.getLocalPort());
                System.out.println(serverSocket.getLocalPort()) ;

                while(true){
                     socket = serverSocket.accept() ;

                    message += "Request from " + socket.getInetAddress()
                            + ":" + socket.getPort() + "\n";

                    //socket.getOutputStream().write(Float.toString(acc_sen.getX()).getBytes());



                    //JSONObject object = writeJSON(sensorObject);
                    //ObjectOutputStream objectOutputStream = new ObjectOutputStream(socket.getOutputStream()) ;
                    //objectOutputStream.writeObject(object.toString());
                    //System.out.println(sensorObject.getY());
                    if (socket.isConnected()) {
                        // Read from soeckt ;
                        Log.v("socket: ","is Connected") ;
                         buffer = new BufferedReader(new InputStreamReader(socket.getInputStream())) ;



                        System.out.println(buffer.read()) ;

                    }
                    // Write to Socket ;
                    switch (whichSensor){
                        case "G" :
                            Log.v("in switching","sending ....") ;
                            MainActivity.this.runOnUiThread(new Runnable() {
                                @Override
                                public void run() {

                                    SensorObject sensorObject = new SensorObject(_x,_y,_z) ;
                                    PrintStream printStream = null;
                                    try {
                                        Float[] values = {sensorObject.getX(),sensorObject.getY(),sensorObject.getZ()} ;
                                        ObjectOutputStream dataOutputStream = new ObjectOutputStream(socket.getOutputStream()) ;
                                        dataOutputStream.writeObject(values);
                                        dataOutputStream.flush();

                                    } catch (IOException e) {
                                        e.printStackTrace();

                                    }

                                    try {
                                        socket.close();
                                    } catch (IOException e) {
                                        e.printStackTrace();
                                    }

                                    Log.v("send to client :", "you just clicked connect..." );
                                    msg.setText(message);
                                }
                            });
                            break;
                        default:
                            Log.v("Socket","Nothing Look Like!") ;
                    }



                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        if (serverSocket != null) {
            try {
                serverSocket.close();
                Log.i("Destory","Server is Closed");
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();

            }
        }
    }

    public void sendData(float x,Socket socket) throws IOException {
        DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream()) ;
        dataOutputStream.writeFloat(x);
        dataOutputStream.flush();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main_menu,menu);

          return true ;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch(item.getItemId()) {
            case R.id.show_sensor :
                Intent intent = new Intent(this,AvailabalSensor.class) ;
                startActivity(intent);
                break;
        }

        return super.onOptionsItemSelected(item);

    }

    public JSONObject writeJSON(SensorObject sensorObject) throws JSONException  {
        JSONObject sensor = new JSONObject() ;
        sensor.put("x",sensorObject.getX()) ;
        sensor.put("y",sensorObject.getY()) ;
        sensor.put("z",sensorObject.getZ()) ;

        return sensor ;
    }


}
