#include <CoDrone.h>

void setup() {
  CoDrone.begin(115200);
  CoDrone.AutoConnect(NearbyDrone);
  CoDrone.DroneModeChange(Flight);  //Set the drone to flight mode
  
  CoDrone.FlightEvent(TakeOff);     // Perform a TakeOff maneuver 
  delay(2000);                    //Wait 2 seconds for the maneuver to complete
  
}

// THROTTLE (controls vertical speed, positive increases height, negative decreases height), 
// PITCH (controls tilt front to back, positive tilts forward, negative tilts backward), 
// ROLL (controls tilt left to right, positive tilts right, negative tilts left), 
// YAW (rotation, positive is clockwise, negative is counter-clockwise).
// Each of these can be given a value between -100 and 100.
void loop() {
  byte bt1 = digitalRead(11);
  byte bt4 = digitalRead(14);
  byte bt8 = digitalRead(18);
  if (bt1 && !bt4 && !bt8)
  {
    CoDrone.FlightEvent(Landing);
    delay(2000);
    CoDrone.FlightEvent(Stop);
  }
  if (!bt1 && bt4 && !bt8)
  {
    YAW = 100;
    CoDrone.Control(SEND_INTERVAL);
    delay(2000);
  }
  
  THROTTLE = -20;
  CoDrone.Control(SEND_INTERVAL);
  delay(2000);
  bool isEmpty = CoDrone.LowBatteryCheck(10);
  if (isEmpty == false)
  {
    CoDrone.FlightEvent(Landing);
    delay(2000);
    CoDrone.FlightEvent(Stop);
  }
  bool batteryWarning = CoDrone.LowBatteryCheck(30);
  if (batteryWarning == false)
  {
    CoDrone.LED_Blink(25, 5);
    CoDrone.LED_Connect();
  }

  bool allowControl = false;
  if (PAIRING == true && allowControl == true)
  {
    YAW = -1 * CoDrone.AnalogScaleChange(analogRead(A3));
    THROTTLE  = CoDrone.AnalogScaleChange(analogRead(A4));
    ROLL = -1 * CoDrone.AnalogScaleChange(analogRead(A5));
    PITCH = CoDrone.AnalogScaleChange(analogRead(A6));
 
    CoDrone.Control(SEND_INTERVAL);
  }
}
