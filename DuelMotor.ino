#include <AccelStepper.h>

#define FULLSTEP 4
#define STEP_PER_REVOLUTION 2048 

#define VRX_PIN A1
#define VRY_PIN A0
int xVal = 0;
int yVal = 0;

AccelStepper stepper1(FULLSTEP, 2, 4, 3, 5);
AccelStepper stepper2(FULLSTEP, 9, 11, 10, 12);

void setup() {
  Serial.begin(115200);
  stepper1.setMaxSpeed(1024);   
  stepper1.setAcceleration(100.0);       
  stepper1.setCurrentPosition(0);
  stepper1.moveTo(STEP_PER_REVOLUTION); 
  
  stepper2.setMaxSpeed(1024);   
  stepper2.setAcceleration(100.0);         
  stepper2.setCurrentPosition(0);
  stepper2.moveTo(STEP_PER_REVOLUTION); 
}

void loop() {

xVal = (analogRead(VRX_PIN) - 490) * 2;
yVal = (analogRead(VRY_PIN) - 509) * 2;

  if (xVal > 1000){
  xVal = 1000;
  }
  if (yVal > 1000){
  yVal = 1000;
  }
  if (xVal < -1000){
  xVal = -1000;
  }
  if (yVal < -1000){
  yVal = -1000;
  }

  if (stepper1.distanceToGo() == 0)
    stepper1.moveTo(-stepper1.currentPosition());

  stepper1.run();

  if (stepper2.distanceToGo() == 0)
    stepper2.moveTo(-stepper2.currentPosition());

  stepper2.run();

  stepper2.setSpeed(xVal);
  stepper1.setSpeed(yVal);

  Serial.print("x = ");
  Serial.print(xVal);
  Serial.print(", y = ");
  Serial.println(yVal);
 
}