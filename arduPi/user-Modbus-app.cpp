/*  
 *  ModBus Module
 *  
 *  Copyright (C) Libelium Comunicaciones Distribuidas S.L. 
 *  http://www.libelium.com 
 *  
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 3 of the License, or 
 *  (at your option) any later version. 
 *  a
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see http://www.gnu.org/licenses/. 
 *  
 *  Version:           1.0
 *  Design:            David Gascón 
 *  Implementation:    Ahmad Saad
 */


// Include these libraries for using the RS-485 and Modbus functions

#include "ModbusMaster485.h"
#include "arduPi.h"


// Instantiate ModbusMaster object as slave ID 1
ModbusMaster485 node(17);

// Define one addres for reading
#define address 6
 
// Define the number of bytes to read
#define bytesQty 2

void setup()
{
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  
  // Power on the USB for viewing data in the serial monitor
  //Serial.begin(115200);
  delay(100);
  // Initialize Modbus communication baud rate
  node.begin(9600);

  // Print hello message
  printf("Modbus communication over RS-485\n");
  delay(100);
}


void loop()
{
  // This variable will store the result of the communication
  // result = 0 : no errors
  // result = 1 : error occurred
// for (int i;i<2;i++)
 //{  
	int result =  node.readHoldingRegisters(address, bytesQty);
 	
  	if (result != 0) {
    	// If no response from the slave, print an error message
    	printf("Communication error\n");
    	delay(1000);
	
  	}
  	else {

    	// If all OK
    	printf("Read value: \n");

    	// Print the read data from the slave
    	printf("%d\n", node.getResponseBuffer(0));
    	delay(1000);
  	}
  
  printf("\n");
  delay(2000);

  // Clear the response buffer
  node.clearResponseBuffer();
 
}

int main (){
  setup();
  while(1){
    loop();
  }
  return (0);
}
