#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;  

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 3, 4, 5, 6);   
// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Hello!");
  

  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
 
  ads.setGain(GAIN_SIXTEEN);
  ads.begin();

  lcd.begin(16, 2);
  // Clears the LCD screen
  lcd.clear();
}

void loop(void)
{
  int16_t results;
  
  
  //float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */
  float multiplier = 0.0078125F; /* ADS1115  @ +/- 0.256V gain (16-bit results) */

  
  double sum_data=0.0000000;
  double count=0.0;
  for (unsigned long time_now = millis(); (millis()-time_now < 1.1628*1000);) {
    results = ads.readADC_Differential_0_1()+7.5;
    sum_data+=results * multiplier;
    count+=1;
  }
  
  Serial.println("Differential: "); Serial.print(results); Serial.print("("); Serial.print(sum_data/count,7); Serial.println("mV)");
  Serial.println("current");
  Serial.println(((sum_data/count)*1000)/(0.1),2); Serial.print("micro A"); 
  
  lcd.clear();
  lcd.setCursor(3, 0);
  // set the cursor to column 3, line 0
  lcd.print(((sum_data/count)*1000)/(0.1),4);  
  
  lcd.setCursor(2, 1);
  lcd.print("Micro Amperes");    //resolution = Micro ampere 78.125
  
  delay(200); 
}
