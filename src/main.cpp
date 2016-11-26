#include "resources.h"

Vibrator motor(5);
Sensor sensor(2, 3);


void on_distance_read(int distance){
      Serial.println(distance);

      if(distance < DIST::TOO_CLOSE){
        motor.setSpeed(SPEED::SP3);
      }
      else if (distance < DIST::CLOSE){
        motor.setSpeed(SPEED::SP2);
      }
      else if (distance < DIST::NORMAL){
        motor.setSpeed(SPEED::SP1);
      }else{
        motor.setSpeed(SPEED::STOP);
      }
}

void setup(){
    motor.init();
    sensor.init();
    sensor.setCallback(on_distance_read);

    Serial.begin(9600);
}


void loop(){

  sensor.run();
  motor.commit();
  Serial.println(motor.getSpeed());
  delay(200);
}
