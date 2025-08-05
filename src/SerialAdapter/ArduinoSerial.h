#ifndef INPUT_EVENTS_ARDUINO_SERIAL_H
#define INPUT_EVENTS_ARDUINO_SERIAL_H

#include <Arduino.h>
#include "ISerialAdapter.h"

namespace input_events {
/**
 * @brief An implementation od ISerialAdapter that can use any Arduino Stream
 * 
 * @details The Serial is to be configured externally. 
 * 
 */
class ArduinoSerial : public ISerialAdapter {
public:
    ArduinoSerial(Stream& serialPort) : serial(serialPort) {}

    /**
     * @brief Does nothing. Configure the Serial externally.
     * 
     */
    void begin() override {}

    void end() override {}

    int available() const override {
        return serial.available();
    }

    virtual int read() override {  // returns -1 if no data
        return serial.read();
    }

    int availableForWrite() const override {
        return serial.availableForWrite();
    }

    size_t write(const char* buffer, size_t len) override {
        return serial.write((const uint8_t*)buffer, len);
    }

private:
    Stream& serial;

    // void printBufferHex(const char* buffer, size_t len) {
    //     for (size_t i = 0; i < len; ++i) {
    //         if ((unsigned char)buffer[i] < 16) Serial.print("0");  // Pad single-digit hex
    //         Serial.print((unsigned char)buffer[i], HEX);           // Print byte in hex
    //         Serial.print(" ");  // Optional spacing
    //     }
    //     Serial.println();
    // }

};

}
#endif
