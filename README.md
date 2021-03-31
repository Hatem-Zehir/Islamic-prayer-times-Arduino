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
