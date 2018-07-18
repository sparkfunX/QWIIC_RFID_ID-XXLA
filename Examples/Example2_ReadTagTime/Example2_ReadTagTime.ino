/*
	Qwiic RFID board fot the ID-XXLA Modules
	By: Elias Santistevan
	Sparkfun Electronics
	Date: July 18th, 2018
	License: This code is public domain but if you use this and we meet someday, get me a beer! 

	Feel like supporting our work? Buy a board from Sparkfun!
	<website here>

	This example will do one thing for you: It will give the RFID tag's ID of the last tag scanned 
	and the time since the last ID scan.  
*/

#include <Wire.h> 

#define RFID_ADDR 0x7D //0x7D is the default address, 0x7C if you close the address jumper.

byte tagID[7]; //Length of the tag is 5 bytes long followed by 1 byte of checksum.

//We'll use a pin attached to the interrupt line to initiate the 
//check for the RFID tag ID. Feel free to remove it and do a manual check.
const int eventPin = 8; 
unsigned long time = 0; //Time will be the 7th and 8th byte read from the I2C bus after the ID.

void setup()
{
	Wire.begin(); 
	Serial.begin(9600); 
	Serial.println("Waiting for interrupt to fire which indicates a tag has been read!"); 
	pinMode(eventPin, INPUT_PULLUP); 
}
void loop()
{
	if( digitalRead(eventPin) == LOW ) checkTagID();
	delay(250);//slow it down
}
//20 tags can be stored by the product at a time, the first one to be scanned is the first one
//to be pulled from the tag stack. If the tag reads '000000' or the interrupt line never went low
//then there are no new tags to be read.
void checkTagID()
{	
	Serial.print("RFID Tag ID: "); 
	Wire.requestFrom((uint8_t)RFID_ADDR, (uint8_t)8); 
	for( int x = 0; x < 7; x++ ) 
		tagID[x] = Wire.read(); 
	for( int x = 0; x < 7; x++ ) 
		Serial.print(tagID[x]); 
	Serial.print(" TIME SINCE LAST: "); 
	time = Wire.read() << 8;
	time |= Wire.read(); 
	//Time is in milliseconds, divide by 1000 to get seconds. The time 
	//gives a unique scan identifier to the tag's ID.
	//Uncomment the following line to get seconds instead of milliseconds:
	//time /= 1000; 
	Serial.println(time);

}
