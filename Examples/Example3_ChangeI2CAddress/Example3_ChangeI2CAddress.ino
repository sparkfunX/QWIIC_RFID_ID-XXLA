
/*
  An I2C based KeyPad
  By: Nathan Seidle
  SparkFun Electronics
  Date: January 21st, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14641

  This example demonstrates how to change the I2C address via software.

  Note: To change the address you can also open the on-board jumper. This will force the address to 74 (0x4A).

  Note: If you change the address to something unknown you can either open the jumper (goes to address 0x4A) or
  use the I2C scanner sketch (Example 4).
*/

#include <Wire.h>

byte rfidAddress = 0x7D; //0x7D is the default address, 0x7C if the address jumper is closed.
byte newAddress = 0x67; //Must be 0x08 <= newAddress <= 0x77

void setup(void)
{
  Wire.begin();
  
  Serial.begin(9600);
  Serial.println("Qwiic RFID Change Address Example");

  //The new address must be 0x08 <= address <= 0x77
  if(changeRFIDAddress(rfidAddress, newAddress) == true) //Old address, new address
  {
    rfidAddress = newAddress;
    Serial.println("Address successfully changed to 0x" + String(rfidAddress, HEX));
  }
}

void loop(void)
{
}


//Change the I2C address from one address to another
boolean changeRFIDAddress(byte oldAddress, byte newAddress)
{
  Wire.beginTransmission(oldAddress); //Communicate using the old address
  Wire.write(0xC7); //0xC7 is the register location on the KeyPad to change its I2C address
  Wire.write(newAddress); //Go to the new address
  if (Wire.endTransmission() != 0)
  {
    //Sensor did not ACK
    Serial.println("Error: Sensor did not ack");
    return(false);
  }
  return(true);
}

