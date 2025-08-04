#include <Arduino.h>

#include "serial/ArduinoSerial.h"       //An adapter for the standard Arduino Serial port
#include "framers/CrLfMessageFramer.h"  //Strips CR/LF from input and passes message  to...
#include "DefaultEventMessenger.h"      //...the default messenger


//A simple message consumer function that implements the IMessageConsumer::onMessageReceived() method
void onMessageReceived(const input_events::BasicBufferView& message) {
    Serial.print("You said: ");
    Serial.println(message.buffer); //The CrLfMessageFramer null terminates the message so it is safe to do this
}

input_events::ArduinoSerial mySerial(Serial);               //Create the Serial adapter
input_events::CrLfMessageFramer messageFramer(&mySerial);   //Create the framer

char readBuf[128]; //This is the buffer that the message will be read into. 
input_events::BasicBuffer readBuffer(readBuf, sizeof(readBuf)); //Create a BasicBuffer that holds a pointer to the readBuf

input_events::DefaultEventMessenger eventMessenger(readBuffer, &messageFramer); //Do not pass an ImessageConsumer to the constructor


void setup() {
    Serial.begin(9600);
    Serial.println("Starting SerialMessageEvents Basic Function Consumer Example");
    eventMessenger.begin();
    eventMessenger.setCallback(onMessageReceived);
}



void loop() {
    eventMessenger.update();
}