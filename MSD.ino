////////////////////
//MSD MASTER CODE//
///////////////////

#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *motor = AFMS.getStepper(200, 1);
#define switch1 35
#define switch2 37
#define switch3 39
#define greenLight 29
#define yellowLight 27
#define redLight 25
#define agitatorMotorDown 33
#define agitatorMotorUp 31
#define lightSensor1 A14
#define lightSensor2 A13
#define lightSensor3 A12
#define lightSensor4 A11
#define levelSensor A10
float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux
 
void setup() {

  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  pinMode(lightSensor1, INPUT);
  pinMode(lightSensor2, INPUT);
  pinMode(lightSensor3, INPUT);
  pinMode(lightSensor4, INPUT);
  pinMode(levelSensor, INPUT);
  
  pinMode(greenLight, OUTPUT);
  pinMode(yellowLight, OUTPUT);
  pinMode(redLight, OUTPUT);
  pinMode(agitatorMotorDown, OUTPUT);
  pinMode(agitatorMotorUp, OUTPUT);
  
  AFMS.begin(); //Create with the default frequency 1.6KHz
  motor->setSpeed(100); //RPM
  Serial.begin(9600);
}
 
void loop() {
  //Read light
  int ltValue = analogRead(lightSensor1);     
  Serial.print("Raw = ");
  Serial.print(ltValue);
  Serial.print(" - Lux = ");
  Serial.println(RawToLux(ltValue));
  ltValue = analogRead(lightSensor2);     
  Serial.print("Raw = ");
  Serial.print(ltValue);
  Serial.print(" - Lux = ");
  Serial.println(RawToLux(ltValue)); 
  ltValue = analogRead(lightSensor3);     
  Serial.print("Raw = ");
  Serial.print(ltValue);
  Serial.print(" - Lux = ");
  Serial.println(RawToLux(ltValue)); 
  ltValue = analogRead(lightSensor4);     
  Serial.print("Raw = ");
  Serial.print(ltValue);
  Serial.print(" - Lux = ");
  Serial.println(RawToLux(ltValue)); 

  //Read level sensor
  int lvValue = analogRead(levelSensor); 
  Serial.print("Level = ");
  Serial.println(lvValue); 

  //Read switches
  int swValue = digitalRead(switch1); 
  Serial.print("Switch one = ");
  Serial.println(swValue); 
  swValue = digitalRead(switch2); 
  Serial.print("Switch two = ");
  Serial.println(swValue);
  swValue = digitalRead(switch3); 
  Serial.print("Switch three = ");
  Serial.println(swValue);

  //Cycle lights
  digitalWrite(redLight, HIGH);
  delay(1000);
  digitalWrite(yellowLight, HIGH);
  delay(1000);
  digitalWrite(greenLight, HIGH);
  delay(1000);
  digitalWrite(redLight, LOW);
  digitalWrite(yellowLight, LOW);
  digitalWrite(greenLight, LOW);
  delay(1000);

  //Test agitator
  digitalWrite(agitatorMotorDown, HIGH);
  delay(1000);
  digitalWrite(agitatorMotorDown, LOW);
  digitalWrite(agitatorMotorUp, HIGH);
  delay(1000);
  digitalWrite(agitatorMotorUp, LOW);
  digitalWrite(agitatorMotorDown, HIGH);
  delay(1000);
  digitalWrite(agitatorMotorDown, LOW);
  delay(1000);

  //Spin stepper
  motor->step(200, BACKWARD, DOUBLE); 
}
 
float RawToLux(int raw){
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}
