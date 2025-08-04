#ifndef INPUT_EVENTS_IMESSAGE_ENCODER_H
#define INPUT_EVENTS_IMESSAGE_ENCODER_H

#include <Arduino.h> //Required for DEC
#include "IEventMessenger.h"

namespace input_events {


/**
 * @brief Used by the IMessageBuilder to create key/value pairs as a string
 * 
 */
class IKeyValueEncoder {

    public:
    virtual ~IKeyValueEncoder() = default;

    virtual size_t encode(const char* key) = 0;
    virtual size_t encode(char key) = 0;
    virtual size_t encode(const char* key, const char* value) = 0;
    virtual size_t encode(const char* key, char c) = 0;
    virtual size_t encode(const char* key, unsigned char c, int b = DEC) = 0;
    virtual size_t encode(const char* key, int value, int base = DEC) = 0;
    virtual size_t encode(const char* key, unsigned int value, int base = DEC) = 0;
    virtual size_t encode(const char* key, long value, int base = DEC) = 0;
    virtual size_t encode(const char* key, unsigned long value, int base = DEC) = 0;
    virtual size_t encode(const char* key, double value, int digits = 4) = 0;



};

}

#endif