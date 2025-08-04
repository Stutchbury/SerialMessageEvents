#include <Arduino.h>

#include "serial/ArduinoSerial.h"       //An adapter for the standard Arduino Serial port
#include "framers/CrLfMessageFramer.h"  //Strips CR/LF from input and passes message  to...
#include "DefaultEventMessenger.h"      //...the default messenger


//A simple message consumer class that implements the IMessageConsumer::onMessageReceived() method
class MockMessageConsumer : public input_events::IMessageConsumer {
public:
    void onMessageReceived(const input_events::BasicBufferView& message) override {
        Serial.print("You said: ");
        Serial.println(message.buffer); //The CrLfMessageFramer null terminates the message so it is safe to do this
    }
};

input_events::ArduinoSerial mySerial(Serial);               //Create the Serial adapter
input_events::CrLfMessageFramer messageFramer(&mySerial);   //Create the framer
MockMessageConsumer messageConsumer;                        //Create the message consumer

char readBuf[128]; //This is the buffer that the message will be read into. 
input_events::BasicBuffer readBuffer(readBuf, sizeof(readBuf)); //Create a BasicBuffer that holds a pointer to the readBuf

input_events::DefaultEventMessenger eventMessenger(readBuffer, &messageFramer, &messageConsumer); //Pass all of the above to the messenger.



void setup() {
    Serial.begin(9600);
    Serial.println("Starting SerialMessageEvents Basic Class Consumer Example");
    eventMessenger.begin();
}



void loop() {
    eventMessenger.update();
}