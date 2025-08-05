#ifndef INPUT_EVENTS_DEFAULT_MESSAGE_BUILDER_H
#define INPUT_EVENTS_DEFAULT_MESSAGE_BUILDER_H

#include "BaseMessageBuilder.h"

namespace input_events {

/**
 * @brief Append various types to a message
 * 
 * @details All the `appendMessage()` methods return the size appended or 0 if the append failed.
 * 
 */
class DefaultMessageBuilder : public BaseMessageBuilder, protected Print {

    public:

    using BaseMessageBuilder::BaseMessageBuilder;
    
    virtual ~DefaultMessageBuilder() = default;

    size_t appendMessage(const char* str) { 
        return print(str); 
    }
    size_t appendMessage(char c) { 
        return print(c); 
    }
    size_t appendMessage(unsigned char c, int b = DEC) { 
        return print(c, b); 
    }
    size_t appendMessage(int value, int base = DEC) { 
        return print(value, base); 
    }
    size_t appendMessage(unsigned int value, int base = DEC) { 
        return print(value, base); 
    }
    size_t appendMessage(long value, int base = DEC) { 
        return print(value, base); 
    }
    size_t appendMessage(unsigned long value, int base = DEC) { 
        return print(value, base); 
    }
    // size_t appendMessage(float value, int digits = 2) { 
    //     return print(value, digits); 
    // }
    size_t appendMessage(double value, int digits = 4) { 
        return print(value, digits); 
    }

    protected:

    // Required for Print
    virtual size_t write(uint8_t byte) override {
        if (this->writeBuffer.bufferLength < writeBuffer.bufferSize - 1) {
            this->writeBuffer.buffer[this->writeBuffer.bufferLength++] = byte;
            this->writeBuffer.buffer[this->writeBuffer.bufferLength] = '\0';  // Keep null-terminated
            return 1;
        }
        this->writeBuffer.buffer[writeBuffer.bufferSize - 1] = '\0';  // Always null-terminate
        return 0;  // Buffer full
    }

    // Used by Print for 'efficiency' (strings)
    virtual size_t write(const uint8_t* buffer, size_t size) override {
        size_t currentMessageLength = this->writeBuffer.bufferLength;
        size_t bytesWritten = 0;
        for (size_t i = 0; i < size; ++i) {
            size_t byteWritten = write(buffer[i]); 
            if ( byteWritten == 0 ) {  //Buffer has been blown
                this->writeBuffer.bufferLength = currentMessageLength;
                this->writeBuffer.buffer[this->writeBuffer.bufferLength] = '\0';
                return 0;
            }
            ++bytesWritten;
        }
        this->writeBuffer.buffer[writeBuffer.bufferSize - 1] = '\0';  // Always null-terminate
        return bytesWritten;
    }





    private:


};

}

#endif