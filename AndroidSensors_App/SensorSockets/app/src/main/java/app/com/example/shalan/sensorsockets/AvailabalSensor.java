package app.com.example.shalan.sensorsockets;

import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;

public class AvailabalSensor extends AppCompatActivity {
    SensorManager sensorManager ;
    List<Sensor> sensors_list ;
    ArrayList<String> sensorName ;
    ArrayList<String> sensorType ;
    ListView listView ;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_availabal_sensor);
        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        listView = (ListView) findViewById(R.id.listview);
        sensors_list = sensorManager.getSensorList(Sensor.TYPE_ALL) ;

        for (Sensor i : sensors_list ){
            if (i.getName() != null)
                Log.v("sensorname:",i.getName());

            Log.v("sensor type:", String.valueOf(i.getType()));

        }
        listView.setAdapter(new ArrayAdapter<>(this,
                                                    android.R.layout.simple_list_item_1,
                                                    sensorName));


    }
}
