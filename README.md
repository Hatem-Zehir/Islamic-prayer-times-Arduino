# Islamic-prayer-times-Arduino
This is an Arduino code that displays on a Nokia 5510 LCD the Date and the Time and also calculates and displays Salat Time (prayer time) for a given town.

## Hardware components
| Component | Link |
|-----------|------|
| Arduino Board (e.g., Arduino UNO, Nano, etc.) | [Buy](https://s.click.aliexpress.com/e/_oFe9rDB) |
| DS1307 RTC Module | [Buy](https://s.click.aliexpress.com/e/_on4dd9J) |
| Nokia 5510 Display | [Buy](https://s.click.aliexpress.com/e/_oluFaPJ) |
| Jumper Wires & Breadboard | |

> ℹ️ **Affiliate Links:**  The links above are affiliate links.  If you purchase through these links, I may earn a small commission at no extra cost to you.

Here is the schematic of the circuit
![Circuit Schematic](https://github.com/Hatem-Zehir/Islamic-prayer-times-Arduino/blob/main/Circuit-of-the-Arduino-prayer-times-calculator.png)

## The program
This code has math routines to compute sun position and Muslims salat (prayer) time for a given town (latitude/longitude), DST, and convention. The hardware part is composed of an Arduino UNO (you can use any other arduino board), an RTC DS1307, and the Nokia 5510 display to display the time, the date, and prayer times.

## How to edit the program?
You should adapt the line 164 of the code:
```
calcPrayerTimes(year, month, dayOfMonth, 41.3, 20.6, 3, -18.5, -19, fajr, sunRise, zuhr, asr, maghrib, isha);
```
The parameters needed are:
- **Longitude/Latitude/Time Zone** of the desired place.
- **Fajr Twilight/ Esha Twilight** which differ in calculations from one country to another.

|Organization|Angle of the sun under the Horizon (Fajr)|Angle of the sun under the Horizon (Isha)|Region|
| --- | --- | --- | --- |
|University Of Islamic Sciences, Karachi|18 Degrees|18 Degrees|Pakistan, Bangladesh,India, Afghanistan, Parts of Europe|
|North America|15 Degrees|15 Degrees|Parts of the USA, Canada, Parts of the UK|
|Muslim World League|18 Degrees|17 Degrees|Europe, The Far East, Parts of the USA|
|Umm Al-Qura Committee|19 Degrees|90 minutes after the Sunset Prayer, 120 minutes (in Ramadan only)|The Arabian Peninsula|
|Egyptian General Authority of Survey|19.5 Degrees|17.5 Degrees|Africa, Syria, Iraq, Lebanon, Malaysia, Parts of the USA|

## How does the program work?
The function takes the data of Year/Month/Day/Longitude/Latitude/TimeZone/FajrTwilight/IshaTwilight plus 6 references to double variables (Fajr/SunRise/Zuhr/Asr/Maghrib/Isha). These 6 variables are the ones to return data into. there is also some functions to help in some number conversions (for example, Radians to Degrees and vise versa).

So, if we take Cairo as an example:
- Longitude: 30.2
- Latitude: 30
- Time Zone: +2 
- Fajr Twilight: -19.5
- Esha Twilight: -17.5

We should adapt the line 164 like this:
```
calcPrayerTimes(year, month, dayOfMonth, 30.2, 30, 2, -19.5, -17.5, fajr, sunRise, zuhr, asr, maghrib, isha);
```
Note that these prayer times are still "double" and should be converted to a time format. Mahmoud Adly Ezzat made the doubleToHrMin function (you can find it before the calcPrayerTimes function) which splits the number into Hours and Minutes. It takes the double and two references to int variables.

**P.S:** the Prayer time calculation algorithm is written by Mahmoud Adly Ezzat. You can read more about it in his [blog post](http://3adly.blogspot.com/2010/07/prayer-times-calculations-pure-c-code.html).
