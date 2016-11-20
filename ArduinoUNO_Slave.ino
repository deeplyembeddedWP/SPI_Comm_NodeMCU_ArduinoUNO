#include <SPI.h>

volatile boolean process_it;                    //Flag for checking if the data is recieved from Master i.e. ESP8266
byte a;                                         //Byte to store the processed data

void setup (void)
{
	Serial.begin (115200);                        //Set UART baug rate to 115200
	SPCR |= bit (SPE);                            //Configure ATMEGA328P/Arduino in slave mode
	pinMode(MISO, OUTPUT);                        //Configure MISO as output, SlaveOut
	process_it = false;                           //Initialize flag to FALSE
	SPI.attachInterrupt();                        //Enable interrupts for SPI--> You can do that like this too /*SPCR |= bit (SPIE)*/

}  


// SPI interrupt routine
ISR (SPI_STC_vect)
{
	byte c = SPDR;                                //Grab the data byte from the SPI Data Register (SPDR)
	a = c;                                        //Put the byte into a temporary variable for processing
	SPDR = c*2;                                   //process the data byte and put it back into the SPDR for the Master to read it
	process_it = true;                            //Set the Flag  as TRUE

}  


void loop (void)
{
	if (process_it)                               //Check if the data has been processed 
	{
		Serial.println("Recieved\r\n");             //UART - Notify if recived a byte from master
		process_it = false;                         //Set the Flag to False
	}  
}  