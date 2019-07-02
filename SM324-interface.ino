/****************************************************************
Reads temperature and magnetic field from an SM324 with Arduino.
Contributed by Sami Lakka, LAKKA Technologies, www.lakkatech.com
*****************************************************************/
void setup() {
  Serial.begin(9600); //Initialize serial communication at 9.6 kbps
  Wire.begin(); //Join I2C bus as master
}

void loop() {
  // Read request from SM324 for temp and mag values
  Wire.beginTransmission(16);    
  Wire.write(0xAA);                     // sends value byte  
  Wire.endTransmission();               // stop transmitting

  // Read the values
  byte numOfBytesRead = Wire.requestFrom(0x10,7);   
  byte statusByte = Wire.read();
  
  unsigned long highestMag = Wire.read();
  unsigned long medMag = Wire.read();
  unsigned long lowMag = Wire.read();

  unsigned long highestTemp = Wire.read();
  unsigned long medTemp = Wire.read();
  unsigned long lowTemp = Wire.read();

  unsigned long magValue  = (highestMag<<16) | (medMag<< 8 ) | (lowMag);        
  unsigned long tempValue = (highestTemp<<16) | (medTemp<< 8 ) | (lowTemp);
   
  Serial.println("--- READ REQUEST ---");
  Serial.print("Status: "); Serial.println(statusByte);
  Serial.print("Magnetometer value: "); Serial.println(magValue);  
  
  delay(50); 
}
