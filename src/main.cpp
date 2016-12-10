#include "resources.h"


class Component{
private:
  _dev_::Vibrator *vibrator;
  _sen_::Sensor *sensor;
  int _mode;

public:
  struct mode{
    enum md{NORMAL, INVERSE};
  };

  Component(_dev_::Vibrator *v, _sen_::Sensor *s, int _mode=mode::md::NORMAL):
  _mode(_mode), vibrator(v), sensor(s){}


  void init(){
    sensor->init();
    vibrator->init();
  }

  void setMode(int mode_=mode::md::NORMAL){
      _mode = mode_;
  }

  int getDistance(){
    return this->sensor->getDistance();
  }

  void run(){
    sensor->run();
    int distance = sensor->getDistance();
    //Serial.print("SENSOR: "); Serial.println(distance);
    if(distance <  _sen_::DISTANCE::CLOSE){
      // if normal mode high vibration, if inverse low vibration
      _mode == mode::md::INVERSE ?
      vibrator->setSpeed(_dev_::PARAMETERS::LOW_VIB):
      vibrator->setSpeed(_dev_::PARAMETERS::HIGH_VIB);
    }
    else if (distance < _sen_::DISTANCE::NORMAL){
      vibrator->setSpeed(_dev_::PARAMETERS::MED_VIB);
    }
    else if (distance < _sen_::DISTANCE::FAR){
      // If normal mode low vibration, if inverse high vibraiton
      _mode == mode::md::INVERSE ?
      vibrator->setSpeed(_dev_::PARAMETERS::HIGH_VIB):
      vibrator->setSpeed(_dev_::PARAMETERS::LOW_VIB);
    }else{
      vibrator->setSpeed(_dev_::PARAMETERS::NO_VIB);
    }
    vibrator->commit();
  }
};

// has some errors !! CHANGE ITS POINTERS
Component *create(int *v_pins, int *echo_pins, int *trig_pins, int size=3){
  Component *components=0;

  for(int i=0;i < size; i++){
     _sen_::Sensor *sensor = new _sen_::Sensor(trig_pins[i], echo_pins[i]);
     _dev_::Vibrator *vib = new _dev_::Vibrator(v_pins[i]);
    //Component *c = new Component(vib, sensor);
    components[i] = Component(vib, sensor);
  }

  return components;
}

const int size = 3;

int v_pins[size] = {3, 5, 6};
int echo_pins[size] = {A5, A4, A2};
int trig_pins[size] = {8, 9, 10};

// sensors MODIFY LATER
_sen_::Sensor sensor1(A0, A1);
_sen_::Sensor sensor2(A3, A2);
_sen_::Sensor sensor3(8, 9);
// vibrators MODIFY LATER
_dev_::Vibrator vib1(3);
_dev_::Vibrator vib2(5);
_dev_::Vibrator vib3(6);
// Components MODIFY LATER
Component c1(&vib1, &sensor1);
Component c2(&vib2, &sensor2, Component::mode::md::INVERSE);
Component c3(&vib3, &sensor3);

//
Component components[size] = {c1, c2, c3};



void setup(){
    Serial.begin(9600);
  //  sensor1.init(); sensor2.init(); sensor3.init();
    for (int i=0; i<size; i++){
      components[i].init();
      Serial.print("INIT ");
    }
}

unsigned int last_pass = 0;
unsigned int time_delay = 100;

void loop(){

  unsigned int t = millis();


  if(t-last_pass > time_delay){
    // sensor1.run(); sensor2.run(); sensor3.run();
    // Serial.print("Sensor 1: "); Serial.println(sensor1.getDistance());
    // Serial.print("Sensor 2: "); Serial.println(sensor2.getDistance());
    // Serial.print("Sensor 3: "); Serial.println(sensor3.getDistance());

  //
    //Serial.println(t-last_pass);
    last_pass = t;
    for(int i=0; i<size; i++){
      components[i].run();
      //Serial.print(components[i].getDistance()); Serial.print(" ");
      delay(100);
    }
    Serial.println("RUN");
    last_pass = t;
   }

}
