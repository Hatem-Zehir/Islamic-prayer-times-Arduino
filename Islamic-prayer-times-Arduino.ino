// Prayer time on Nokia 5510/3310 display Hatem ZEHIR
// Prayer time calculation is from http://3adly.blogspot.com/2010/07/prayer-times-calculations-pure-c-code.html

#include "Wire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

int xegg, yegg;

#define DS1307_I2C_ADDRESS 0x68  // This is the I2C address
long previousMillis = 0;        // will store last time time was updated
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
long interval = 200;
int displayx, displayy, displayradius, x2, y2, x3, y3;
int zero = 0;
char  *Day[] = {"", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
double fajr, sunRise, zuhr, asr, maghrib, isha;

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}

// Gets the date and time from the ds1307 and prints result
void getDateDs1307()
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  //Wire.write(0x00);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

  second     = bcdToDec(Wire.read() & 0x7f);
  minute     = bcdToDec(Wire.read());
  hour       = bcdToDec(Wire.read() & 0x3f);
  dayOfWeek  = bcdToDec(Wire.read());
  dayOfMonth = bcdToDec(Wire.read());
  month      = bcdToDec(Wire.read());
  year       = bcdToDec(Wire.read());

}

void setDateDs1307()
{
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(zero);
  Wire.write(decToBcd(second));    // 0 to bit 7 starts the clock
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));      // for 12 hour am/pm, need to set bit 6 (also need to change readDateDs1307)
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}


void printTime()
{
  int hours, minutes;
  char s[12];
  display.clearDisplay();
  display.setCursor(0, 16);
  display.print(Day[dayOfWeek]);
  display.print(":");
  display.print(char(dayOfMonth / 10 + 0x30));
  display.print(char(dayOfMonth % 10 + 0x30));
  display.print("/");
  display.print(char(month / 10 + 0x30));
  display.print(char(month % 10 + 0x30));
  display.print("/");
  display.print("20");
  display.print(char(year / 10 + 0x30));
  display.print(char(year % 10 + 0x30));

  display.setCursor(18, 26);
  display.print( char( hour / 10 + 0x30) );
  display.print( char( hour % 10 + 0x30) );
  display.print(":");
  display.print( char(minute / 10 + 0x30));
  display.print( char(minute % 10 + 0x30));
  display.print(":");
  display.print(char (second / 10 + 0x30));
  display.print(char (second % 10 + 0x30));
  display.display();
  delay(1000);

  doubleToHrMin(fajr, hours, minutes);
  display.clearDisplay();
  display.setCursor(1, 1);
  display.print("Fajr ");
  display.print(hours);
  display.print(":");
  display.print(minutes);
  display.display();

  doubleToHrMin(zuhr, hours, minutes);
  display.setCursor(1, 10);
  display.print("Zuhr ");
  display.print(hours);
  display.print(":");
  display.print(minutes);
  display.display();

  doubleToHrMin(asr, hours, minutes);
  display.setCursor(1, 20);
  display.print("Asr ");
  display.print(hours);
  display.print(":");
  display.print(minutes);
  display.display();

  doubleToHrMin(maghrib, hours, minutes);
  display.setCursor(1, 30);
  display.print("Maghrib ");
  display.print(hours);
  display.print(":");
  display.print(minutes);
  display.display();

  doubleToHrMin(isha, hours, minutes);
  display.setCursor(1, 40);
  display.print("Isha ");
  display.print(hours);
  display.print(":");
  display.print(minutes);
  display.display();
  delay(5000);
}


void setup()  {
  Wire.begin();
  display.begin();
  display.clearDisplay();
  display.setContrast(25);
  xegg = (display.width()) / 2;
  yegg = (display.height()) / 2;
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(22, 18);
  display.print("RAMADHAN");
  display.display();
  delay(500);
  display.setCursor(24, 28);
  display.print("MUBARAK");
  display.display();
  delay(500);
  getDateDs1307() ;
}


void loop() {
  getDateDs1307() ;
  calcPrayerTimes(year, month, dayOfMonth, 39.8, 21.4, 3, -18.5, -19, fajr, sunRise, zuhr, asr, maghrib, isha); // year , month, day, Longitude, Latitude, Time Zone, Fajr Twilight, Esha Twilight

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    //getDateDs1307() ;
    printTime();
  }

}

/*-------------------------------------------------------------------------------------*/
// PRAYER TIME (by Mahmoud Adly Ezzat, Cairo)

//convert Degree to Radian
double degToRad(double degree)
{
  return ((3.1415926 / 180) * degree);
}

//convert Radian to Degree
double radToDeg(double radian)
{
  return (radian * (180 / 3.1415926));
}

//make sure a value is between 0 and 360
double moreLess360(double value)
{
  while (value > 360 || value < 0)
  {
    if (value > 360)
      value -= 360;

    else if (value < 0)
      value += 360;
  }

  return value;
}

//make sure a value is between 0 and 24
double moreLess24(double value)
{
  while (value > 24 || value < 0)
  {
    if (value > 24)
      value -= 24;

    else if (value < 0)
      value += 24;
  }

  return value;
}

//convert the double number to Hours and Minutes
void doubleToHrMin(double number, int &hours, int &minutes)
{
  hours = floor(moreLess24(number));
  minutes = floor(moreLess24(number - hours) * 60);
}

void calcPrayerTimes(int year, int month, int day,
                     double longitude, double latitude, int timeZone,
                     double fajrTwilight, double ishaTwilight,
                     double &fajrTime, double &sunRiseTime, double &zuhrTime,
                     double &asrTime, double &maghribTime, double &ishaTime)
{
  double D = (367 * year) - ((year + (int)((month + 9) / 12)) * 7 / 4) + (((int)(275 * month / 9)) + day - 730531.5);

  double L = 280.461 + 0.9856474 * D;
  L = moreLess360(L);

  double M = 357.528 + (0.9856003) * D;
  M = moreLess360(M);

  double Lambda = L + 1.915 * sin(degToRad(M)) + 0.02 * sin(degToRad(2 * M));
  Lambda = moreLess360(Lambda);

  double Obliquity = 23.439 - 0.0000004 * D;
  double Alpha = radToDeg(atan((cos(degToRad(Obliquity)) * tan(degToRad(Lambda)))));
  Alpha = moreLess360(Alpha);

  Alpha = Alpha - (360 * (int)(Alpha / 360));
  Alpha = Alpha + 90 * (floor(Lambda / 90) - floor(Alpha / 90));

  double ST = 100.46 + 0.985647352 * D;
  double Dec = radToDeg(asin(sin(degToRad(Obliquity)) * sin(degToRad(Lambda))));
  double Durinal_Arc = radToDeg(acos((sin(degToRad(-0.8333)) - sin(degToRad(Dec)) * sin(degToRad(latitude))) / (cos(degToRad(Dec)) * cos(degToRad(latitude)))));

  double Noon = Alpha - ST;
  Noon = moreLess360(Noon);


  double UT_Noon = Noon - longitude;


  ////////////////////////////////////////////
  // Calculating Prayer Times Arcs & Times //
  //////////////////////////////////////////

  // 2) Zuhr Time [Local noon]
  zuhrTime = UT_Noon / 15 + timeZone;

  // Asr Hanafi
  //double Asr_Alt =radToDeg(atan(2+tan(degToRad(latitude - Dec))));
  double Asr_Alt = radToDeg(atan(1.7 + tan(degToRad(latitude - Dec))));
  // Asr Shafii
  //double Asr_Alt = radToDeg(atan(1 + tan(degToRad(latitude - Dec))));
  double Asr_Arc = radToDeg(acos((sin(degToRad(90 - Asr_Alt)) - sin(degToRad(Dec)) * sin(degToRad(latitude))) / (cos(degToRad(Dec)) * cos(degToRad(latitude)))));
  Asr_Arc = Asr_Arc / 15;
  // 3) Asr Time
  asrTime = zuhrTime + Asr_Arc;

  // 1) Shorouq Time
  sunRiseTime = zuhrTime - (Durinal_Arc / 15);

  // 4) Maghrib Time
  maghribTime = zuhrTime + (Durinal_Arc / 15);

  double Esha_Arc = radToDeg(acos((sin(degToRad(ishaTwilight)) - sin(degToRad(Dec)) * sin(degToRad(latitude))) / (cos(degToRad(Dec)) * cos(degToRad(latitude)))));
  // 5) Isha Time
  ishaTime = zuhrTime + (Esha_Arc / 15);

  // 0) Fajr Time
  double Fajr_Arc = radToDeg(acos((sin(degToRad(fajrTwilight)) - sin(degToRad(Dec)) * sin(degToRad(latitude))) / (cos(degToRad(Dec)) * cos(degToRad(latitude)))));
  fajrTime = zuhrTime - (Fajr_Arc / 15);

  return;
}
