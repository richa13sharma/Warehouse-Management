
// Include Libraries
#include "Arduino.h"
#include "Buzzer.h"
#include "DHT.h"
#include "HX711.h"
#include "PIR.h"


// Pin Definitions
#define BUZZER_PIN_SIG	7
#define DHT_PIN_DATA	2
#define SCALE_PIN_DAT	4
#define SCALE_PIN_CLK	3
#define PIR_PIN_SIG	5



// Global variables and defines

// object initialization
Buzzer buzzer(BUZZER_PIN_SIG);
DHT dht(DHT_PIN_DATA);
HX711 scale(SCALE_PIN_DAT, SCALE_PIN_CLK);
#define calibration_factor 2280 //This value is obtained using the SparkFun_HX711_Calibration sketch https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide?_ga=2.77038550.2126325781.1526891300-303225217.1493631967
PIR pir(PIR_PIN_SIG);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    buzzer.off();
    dht.begin();
    scale.set_scale(calibration_factor); 
    scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
//    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
//    if(menuOption == '1') {
//    // Buzzer - Test Code
//    // The buzzer will turn on and off for 500ms (0.5 sec)
//    buzzer.on();       // 1. turns on
//    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
//    buzzer.off();      // 3. turns off.
//    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
//    }
//    else if(menuOption == '2') {
//    // DHT22/11 Humidity and Temperature Sensor - Test Code
//    // Reading humidity in %
//    float dhtHumidity = dht.readHumidity();
//    // Read temperature in Celsius, for Fahrenheit use .readTempF()
//    float dhtTempC = dht.readTempC();
//    Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
//    Serial.print(F("Temp: ")); Serial.print(dhtTempC); Serial.println(F(" [C]"));
//
//    }
//    else if(menuOption == '3') {
//    // SparkFun HX711 - Load Cell Amplifier - Test Code
    float scaleUnits = scale.get_units(); //scale.get_units() returns a float
//    Serial.print(scaleUnits); //You can change this to lbs but you'll need to refactor the calibration_factor
//    Serial.println(" Kg"); //You can change this to lbs but you'll need to refactor the calibration_factor
//    }
//    else if(menuOption == '4') {
//    // Infrared PIR Motion Sensor Module - Test Code
    bool pirVal = pir.read();
//    Serial.print(F("Val: ")); Serial.println(pirVal);
//
//    }
//    
//    if (millis() - time0 > timeout)
//    {
//        menuOption = menu();
//    }


      //Main logic starts here
      //Reading humidity in %
      float dhtHumidity = dht.readHumidity();
      // Read temperature in Celsius, for Fahrenheit use .readTempF()
      float dhtTempC = dht.readTempC();
      if(dhtHumidity >= 10 || dhtTempC > 20)
       {
        Serial.println("DHT11 trigger");
    // Buzzer - Test Code
    // The buzzer will turn on and off for 500ms (0.5 sec)
    buzzer.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    buzzer.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    if(pirVal == 1)
     {
      Serial.println("PIR trigger");
    // Buzzer - Test Code
    // The buzzer will turn on and off for 500ms (0.5 sec)
    buzzer.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    buzzer.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }

    float lastScaleUnits = scaleUnits;
    scaleUnits = scale.get_units();
    float diff = scaleUnits - lastScaleUnits;
    if(diff > 1 || diff <1)
     {
      Serial.println("Load trigger");
    // Buzzer - Test Code
    // The buzzer will turn on and off for 500ms (0.5 sec)
    buzzer.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    buzzer.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }

      
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
//char menu()
//{
//
//    Serial.println(F("\nWhich component would you like to test?"));
//    Serial.println(F("(1) Buzzer"));
//    Serial.println(F("(2) DHT22/11 Humidity and Temperature Sensor"));
//    Serial.println(F("(3) SparkFun HX711 - Load Cell Amplifier"));
//    Serial.println(F("(4) Infrared PIR Motion Sensor Module"));
//    Serial.println(F("(menu) send anything else or press on board reset button\n"));
//    while (!Serial.available());
//
//    // Read data from serial monitor if received
//    while (Serial.available()) 
//    {
//        char c = Serial.read();
//        if (isAlphaNumeric(c)) 
//        {   
//            
//            if(c == '1') 
//    			Serial.println(F("Now Testing Buzzer"));
//    		else if(c == '2') 
//    			Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
//    		else if(c == '3') 
//    			Serial.println(F("Now Testing SparkFun HX711 - Load Cell Amplifier"));
//    		else if(c == '4') 
//    			Serial.println(F("Now Testing Infrared PIR Motion Sensor Module"));
//            else
//            {
//                Serial.println(F("illegal input!"));
//                return 0;
//            }
//            time0 = millis();
//            return c;
//        }
//    }
//}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/
