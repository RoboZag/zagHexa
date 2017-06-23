Android Sensors Applicatoin!
=================== 

Android App act like server that transmit its sensors' values : 

```sequence
Android Server-> Control station : Hello Bob, how are you
```
```sequence


Control station->Android Server: how about Gyro_sensor?
Android Server-->Control station: Ok! gyroValues!

```