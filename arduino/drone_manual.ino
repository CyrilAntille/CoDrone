#include <CoDrone.h>

void setup() {
  CoDrone.begin(115200);
  CoDrone.AutoConnect(NearbyDrone);
  CoDrone.DroneModeChange(Flight);  //Set the drone to flight mode
  
}

// THROTTLE (controls vertical speed, positive increases height, negative decreases height), 
// PITCH (controls tilt front to back, positive tilts forward, negative tilts backward), 
// ROLL (controls tilt left to right, positive tilts right, negative tilts left), 
// YAW (rotation, positive is clockwise, negative is counter-clockwise).
// Each of these can be given a value between -100 and 100.
void loop() {
  // put your main code here, to run repeatedly:
  byte bt1 = digitalRead(11);
  byte bt4 = digitalRead(14);
  byte bt8 = digitalRead(18);
  if (bt1 && !bt4 && !bt8)
  {
    CoDrone.FlightEvent(Stop);
  }
  
  bool isEmpty = CoDrone.LowBatteryCheck(10);
  if (isEmpty == false)
  {
    CoDrone.FlightEvent(Landing);
    delay(2000);
    CoDrone.FlightEvent(Stop);
  }
  
  if (PAIRING == true)
  {
    YAW = -1 * CoDrone.AnalogScaleChange(analogRead(A3));
    THROTTLE  = CoDrone.AnalogScaleChange(analogRead(A4));
    ROLL = -1 * CoDrone.AnalogScaleChange(analogRead(A5));
    PITCH = CoDrone.AnalogScaleChange(analogRead(A6));
 
    CoDrone.Control(SEND_INTERVAL);
  }
}
