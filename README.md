# Islamic-prayer-times-Arduino
This is an Arduino code that displays on a Nokia 5510 display the Date and the Time and also calculates and displays Salat Time (prayer time) for a given town.

## Hardware components
- One Arduino compatible board (I use Arduino UNO, but any other will be just fine)
- DS1307 RTC module
- Nokia 5510 display
- Jumper wires
- Breadboard

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
