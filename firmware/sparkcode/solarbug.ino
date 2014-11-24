#include "Serial2/Serial2.h"

int tinkerDigitalRead(String pin);
int tinkerDigitalWrite(String command);
int tinkerAnalogRead(String pin);
int tinkerAnalogWrite(String command);

char resultstr[64];
int message;
int voltage;


void setup() {
    pinMode(A0,INPUT);//setup A0 as analog input
    pinMode(A1,INPUT); //setup A1 as analog input
    //expose your char buffer to cloud API
    Spark.variable("result",&resultstr,STRING);
    Spark.variable("message",&message,INT);
    
    Spark.function("digitalread",tinkerDigitalRead);
    Spark.function("digitalwrite",tinkerDigitalWrite);
    Spark.function("analogread",tinkerAnalogRead);
    Spark.function("analogwrite",tinkerAnalogWrite);
  
    Spark.function("queryVolts",queryVolts);
    Spark.function("queryTemp",queryTemp);
    Spark.function("queryAmp",queryAmp);
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
    //delay(20);
    if(Serial2.available()>=2){
        voltage=read16();
        
        //message=Serial2.read();
        
        //message=100;
    }
    
    return voltage;
    
}
int queryAmp(String args){
    return 1;
}

int queryTemp(String args){
    
    return 1;
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

int tinkerDigitalRead(String pin) {
    int pinNumber = pin.charAt(1) - '0';
    if (pinNumber< 0 || pinNumber >7) return -1;
    if(pin.startsWith("D")) {
        pinMode(pinNumber, INPUT_PULLDOWN);
        return digitalRead(pinNumber);}
    else if (pin.startsWith("A")){
        pinMode(pinNumber+10, INPUT_PULLDOWN);
        return digitalRead(pinNumber+10);}
    return -2;}

int tinkerDigitalWrite(String command){
    bool value = 0;
    int pinNumber = command.charAt(1) - '0';
    if (pinNumber< 0 || pinNumber >7) return -1;
    if(command.substring(3,7) == "HIGH") value = 1;
    else if(command.substring(3,6) == "LOW") value = 0;
    else return -2;
    if(command.startsWith("D")){
        pinMode(pinNumber, OUTPUT);
        digitalWrite(pinNumber, value);
        return 1;}
    else if(command.startsWith("A")){
        pinMode(pinNumber+10, OUTPUT);
        digitalWrite(pinNumber+10, value);
        return 1;}
    else return -3;}

int tinkerAnalogRead(String pin){
    int pinNumber = pin.charAt(1) - '0';
    if (pinNumber< 0 || pinNumber >7) return -1;
    if(pin.startsWith("D")){
        pinMode(pinNumber, INPUT);
        return analogRead(pinNumber);}
    else if (pin.startsWith("A")){
        pinMode(pinNumber+10, INPUT);
        return analogRead(pinNumber+10);}
    return -2;}

int tinkerAnalogWrite(String command){
    int pinNumber = command.charAt(1) - '0';
    if (pinNumber< 0 || pinNumber >7) return -1;
    String value = command.substring(3);
    if(command.startsWith("D")){
        pinMode(pinNumber, OUTPUT);
        analogWrite(pinNumber, value.toInt());
        return 1;}
    else if(command.startsWith("A")){
        pinMode(pinNumber+10, OUTPUT);
        analogWrite(pinNumber+10, value.toInt());
        return 1;}
    else return -2;}
