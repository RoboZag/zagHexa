package app.com.example.shalan.sensorsockets;

import java.io.Serializable;

/**
 * Created by noura on 19/06/2017.
 */

public class SensorObject implements Serializable {

    private static final long serialVersionUID = 12358903454875L;

    float x = 0 ;
    float y = 0;
    float z = 0;

    public  SensorObject(){

         }

    public  SensorObject(float x,float y, float z){
        this.x = x ;
        this.y = y ;
        this.z = z ;
    }
    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public float getZ() {
        return z;
    }

    public void setZ(float z) {
        this.z = z;
    }
}
