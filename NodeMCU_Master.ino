#include <SPI.h>

#define CS 15                 //define chip select line for manual control           

void setup() 
{
	pinMode(CS,OUTPUT);         //configure the line as output
	Serial.begin(115200);       //Set UART baud rate
	digitalWrite(CS,HIGH);      //Initialize the CS line to HIGH
	SPI.begin();                //Initialize the SPI module--> configures the MOSI, MISO and CLOCK lines

	/*Configure the SPI bus as follows
  1. SPI bus speed = 1 MHz
  2. Data Out = From MSB bit ---> To LSB bit
  3. Data Mode = SPI MODE0*/
	SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));      

}

void loop() 
{
	byte spi_dat;

	digitalWrite(CS,LOW);           //Pull CS Line Low
	SPI.transfer(0x02);             //Send a byte (0x02) to the slave i.e. Arduino UNO 
	digitalWrite(CS,HIGH);          //Pull CS Line High

	delayMicroseconds(10);          //Give some time for the slave to process/do something with the recived data

	digitalWrite(CS,LOW);           //Pull CS Line Low
	spi_dat = SPI.transfer(0x00);   //Recieve the processed data byte from the slave
	digitalWrite(CS,HIGH);          //Pull CS Line High
	Serial.println("Processed Data Recieved from Slave is: "); 
	Serial.print(spi_dat);          //UART - Print the data recieved from the slave
	Serial.println("\r\n");
	delay(1000);                     //Delay of 1s
}

