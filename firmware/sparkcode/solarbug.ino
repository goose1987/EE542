#include "Serial2/Serial2.h"


char resultstr[64];
int message;
int voltage;

void setup() {
    pinMode(A0,INPUT);//setup A0 as analog input
    pinMode(A1,INPUT); //setup A1 as analog input
    //expose your char buffer to cloud API
    Spark.variable("result",&resultstr,STRING);
    Spark.variable("message",&message,INT);
  
    Spark.function("queryVolts",queryVolts);
    //Serial1.begin(9600);
    Serial2.begin(9600);
    
    message=0;
    voltage=0;
    /*
    //SPI for communication instead of serial
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV4) ;
    SPI.setDataMode(SPI_MODE0) ;
    */
    
}

int read16(){
    
    int MSB = Serial2.read();
    int LSB = Serial2.read();
    return (MSB<<8)|LSB;
}

int queryVolts(String args){
    
    Serial2.write('V');
    delay(20);
    //if(Serial2.available()>=2){
        voltage=read16();
        //message=Serial2.read();
        
        //message=100;
    //}
    
    return voltage;
    
}

void loop() {
    //int data1=analogRead(A0); //read some data
    //int data2=analogRead(A1); //some other data
    //format data as JSON, remember to escape the double quotes
    
    //delay(1000); //wait for a second
    
    //Serial.println("testing...");
    
    
    //message=200;
    
    //if(Serial1.available()) {
        //message = Serial1.read();
        //message=100;
        //char message[messageSize];
        
        
    //}
    sprintf(resultstr,"{\"data1\":%x,\"data2\":%d}",message,0);
    Serial2.write('V');
    delay(20);
    if(Serial2.available()>=2){
        message=read16();
        //message=Serial2.read();
        
        //message=100;
    }
    
    delay(200);
}