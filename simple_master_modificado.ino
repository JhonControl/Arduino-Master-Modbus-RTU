/**
 *  Modbus master example 1:
 *  The purpose of this example is to query an array of data
 *  from an external Modbus slave device. 
 *  The link media can be USB or RS232.
 *
 *  Recommended Modbus slave: 
 *  diagslave http://www.modbusdriver.com/diagslave.html
 *   https://github.com/smarmengol/Modbus-Master-Slave-for-Arduino/blob/master/README.md
 *  In a Linux box, run 
 *  "./diagslave /dev/ttyUSB0 -b 19200 -d 8 -s 1 -p none -m rtu -a 1"
 * 	This is:
 * 		serial port /dev/ttyUSB0 at 19200 baud 8N1
 *		RTU mode and address @1
 */

#include <ModbusRtu.h>

// data array for modbus network sharing
uint16_t au16data[16];
uint8_t u8state;

/**
 *  Modbus object declaration
 *  u8id : node id = 0 for master, = 1..247 for slave
 *  u8serno : serial port (use 0 for Serial)
 *  u8txenpin : 0 for RS-232 and USB-FTDI 
 *               or any pin number > 1 for RS-485
 */
Modbus master(0,0,0); // this is master and RS-232 or USB-FTDI



/*********************///

#include <SoftwareSerial.h>
// software serial #1: TX = digital pin 10, RX = digital pin 11
SoftwareSerial portOne(10,11);       /// pines software serial





/**
 * This is an structe which contains a query to an slave device
 */
modbus_t telegram;

unsigned long u32wait;

float p;

int adc;

void setup() {
  
  master.begin( 19200 ); // baud-rate at 19200
  master.setTimeOut( 2000 ); // if there is no answer in 2000 ms, roll over
  u32wait = millis() + 1000;
  u8state = 0; 
  

  portOne.begin(19200);   // Puerto Software serial  
  
    pinMode(9, OUTPUT);  
    pinMode(8, OUTPUT);  
    pinMode(7, OUTPUT);  
    
}

void loop() {
  
 
  
  switch( u8state ) {
  case 0: 
    if (millis() > u32wait) u8state++; // wait state
    break;
  case 1: 
    telegram.u8id = 1; // slave address                                         ---- direccion de slave
    telegram.u8fct = 3; // function code (this one is registers read)           ----funcion modbus
    telegram.u16RegAdd = 1; // start address in slave                           ----direccion de registro
    telegram.u16CoilsNo = 4; // number of elements (coils or registers) to read -----cantidad de registros
    telegram.au16reg = au16data; // pointer to a memory array in the Arduino    -----almacenamiento de datos  

    master.query( telegram ); // send query (only once)
    


    u8state++;
    break;
  case 2:
    master.poll(); // check incoming messages
    if (master.getState() == COM_IDLE) {
   
      
    /// conversion de ADC   
           adc= (au16data[1]);              
           float voltaje = adc * (5.0/1023.0);
           
           
           
           
           /// impresion port software serial 
///          portOne.println("  Holding Registers  Arduino ");
    
            portOne.print("adc slave 01  =  ");  
            portOne.println(au16data[1]);
            portOne.print("Voltage slave =  ");  
            portOne.println(voltaje);
           // portOne.print("Registro 05 =  ");  
           // portOne.println(au16data[3]);

                
        
        
          portOne.println("                   ");   
   
     
      analogWrite(9,au16data[1]>>2);
      
      u8state = 0;
      u32wait = millis() + 100; 
    }
    break;
  }
}

