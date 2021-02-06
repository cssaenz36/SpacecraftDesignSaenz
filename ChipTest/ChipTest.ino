#include <xCore.h>
#include <xSL01.h>
#include <xSI01.h>
#include <xSN01.h>
#include <xSW01.h>

xSW01 SW01;
xSN01 SN01;
xSL01 SL01;
xSI01 SI01;

void setup() {
  // put your setup code here, to run once:

  // Start the Serial Monitor
  delay(1000);
  Serial.begin(115200);

  // Set the I2C Pins for CW01
  #ifdef ESP8266
    Wire.pins(2, 14);
    Wire.setClockStretchLimit(15000);
  #endif

  // Start the I2C Comunication
  Wire.begin();
  Serial.println("I2C Initialized");
  Serial.println();

  ChipCheck(true);

  Serial.println(">>> xChip Testing Program Completed <<<");
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void ChipCheck(bool initialFlag) {
// SL01 - call lux poll function
  if(initialFlag){
    SL01.begin();
    Serial.println("SL01 interface begun");}
    delay(1000);
    Serial.println("Polling SL01...");
    pollUVMeas();
    Serial.println();


// SN01 - call GPS poll function
  if(initialFlag){
    SN01.begin();
    Serial.println("SN01 interface begun");}
    delay(1000);
    Serial.println("Polling SN01...");
    pollGPSMeas();
    Serial.println();


// SW01 - call temp poll function
  if(initialFlag){
    SW01.begin();
    Serial.println("SW01 interface begun");}
    delay(1000);
    Serial.println("Polling SW01...");
    pollTempMeas();
    Serial.println();


// SI01 - call IMU poll function
  if(initialFlag){
    SI01.begin();
    Serial.println("SI01 interface begun");}
    delay(1000);
    Serial.println("Polling SI01...");
    pollIMUMeas();
}

void pollUVMeas() {

  SL01.poll();
  Serial.println(">>> Starting SL01 Polling Cycle <<<");
  Serial.println();

  // Request SL01 to return calculated UVB intensity
  float uva = SL01.getUVA();
  // Display Data on the Serial monitor
  Serial.print("UVA Intersity: ");
  Serial.print(uva);
  Serial.println(" uW/m^2");

  // Request SL01 to return calculated UVB intensity
  float uvb = SL01.getUVB();
  // Display Data on the Serial monitor
  Serial.print("UVB Intensity: ");
  Serial.print(uvb);
  Serial.println(" uW/m^2");

  // Request SL01 to return calculated UVB intensity
  float uvindex = SL01.getUVIndex();
  // Display Data on the Serial monitor
  Serial.print("UVB Index: ");
  Serial.println(uvindex);

  Serial.println();
  Serial.println(">>> Ending SL01 Polling Cycle <<<");
}

void pollTempMeas() {

  SW01.poll();
  Serial.println(">>> Starting SL01 Polling Cycle <<<");
  Serial.println();

    // Create a variable to store the data read from SW01
  float tempC;
  float tempF;
  tempC = tempF = 0;

  // Read and calculate data from SW01 sensor
  SW01.poll();

  // Request SW01 to get the temperature measurement and store in
  // the temperature variable
  tempC = SW01.getTempC(); // Temperature in Celcuis
  tempF = SW01.getTempF(); // Temperature in Farenheit

  // Display the recoreded data over the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" C");
  Serial.print("Temperature: ");
  Serial.print(tempF);
  Serial.println(" F");

  Serial.println();
  Serial.println(">>> Ending SL01 Polling Cycle <<<");
}

void pollGPSMeas() {

  SN01.poll();
  Serial.println(">>> Starting SL01 Polling Cycle <<<");
  Serial.println();

  // Create a variable to store the data read from SN01
  String time;
  long latitude = 0;
  long longitude = 0;
  String date;

  // Get the date from GPS
  date = SN01.getDate();

  // Get the time from the GPS
  time = SN01.getTime();

  // Get the latitude from GPS
  latitude = SN01.getLatitude();

  // Get the longitude from GPS
  longitude = SN01.getLongitude();

  // Display the recorded data over the serial monitor
  Serial.print("GPS Time: ");
  Serial.println(time);
  Serial.print("GPS Date: ");
  Serial.println(date);
  Serial.print("GPS Latitude: ");
  Serial.println(latitude);
  Serial.print("GPS longitude: ");
  Serial.println(longitude);

  Serial.println();
  Serial.println(">>> Ending SL01 Polling Cycle <<<");
}

void pollIMUMeas() {
  SI01.poll();
  Serial.println(">>> Starting SL01 Polling Cycle <<<");
  Serial.println();

// Groscope
  Serial.print("G: ");
  Serial.print(SI01.getGX(), 2);
  Serial.print(", ");
  Serial.print(SI01.getGY(), 2);
  Serial.print(", ");
  Serial.println(SI01.getGZ(), 2);

// Acelerometer
  Serial.print("A: ");
  Serial.print(SI01.getAX(), 2);
  Serial.print(", ");
  Serial.print(SI01.getAY(), 2);
  Serial.print(", ");
  Serial.println(SI01.getAZ(), 2);

// Magnitude
  Serial.print("M: ");
  Serial.print(SI01.getMX(), 2);
  Serial.print(", ");
  Serial.print(SI01.getMY(), 2);
  Serial.print(", ");
  Serial.println(SI01.getMZ(), 2);

// Attitude
  Serial.print("Roll: ");
  Serial.println(SI01.getRoll(), 2);
  Serial.print("Pitch :");
  Serial.println(SI01.getPitch(), 2);
  Serial.print("GForce :");
  Serial.println(SI01.getGForce(), 2);

  Serial.println();
  Serial.println(">>> Ending SL01 Polling Cycle <<<");
}
