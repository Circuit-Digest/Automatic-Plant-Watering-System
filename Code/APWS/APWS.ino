/***************************************************
 Code for Automatic Plant Watering System (APWS)
 ****************************************************/
const int AirValue = 540;   //replace the value from calibration in air
const int WaterValue = 250;  //replace the value from calibration in water
int soilMoistureValue = 0;
int soilmoisturepercent=0;
void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT); // MAX22201 IN1
  pinMode(6, OUTPUT); // MAX22201 IN2
  pinMode(13, OUTPUT); // LED output
  /*
  Put the mototr driver into sleep mode during startup.
  When both IN1 and IN2 inputs are low for longer than tSLEEP (2.2ms max), the MAX22201 enters low-power sleep mode.
  In this mode, outputs are three-stated and the device current consumption is ISLEEP (6.5μA max).  
  */
  digitalWrite(5, LOW);  
  digitalWrite(6, LOW);  
  digitalWrite(13, LOW);  
}
void loop() {
soilMoistureValue = analogRead(A0);  //Read Value from sensor
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
Serial.println(soilmoisturepercent);
if(soilmoisturepercent < 50)  // Soil is dry, Turn on motor
{
  /*
  for the MAX22201 to exit Sleep mode and power on the device, drive IN1 and IN2 high for at least 400μs. 
  */
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);  
  delay(1);
  /*
  Once the MAX22201 is active turn on the motor. You can change the rotation direction by invering the states of IN1 and IN2. 
  */                      
  digitalWrite(5, LOW);            
  digitalWrite(6, HIGH);    
  digitalWrite(13, HIGH);  
}
else if(soilmoisturepercent >85) // Soil is moist, Turn off motor
{
  /*
 Turn off the mototr and put MAX22201 to sleep Mode. 
  */
  digitalWrite(5, LOW);  
  digitalWrite(6, LOW);   
  digitalWrite(13, LOW);    
}
 
   delay(400); //Wait for few milliseconds and then continue the loop.
}

