#ifndef INPUT_EVENTS_BASIC_BUFFER_H
#define INPUT_EVENTS_BASIC_BUFFER_H

//#include <cstddef>
#include <Arduino.h>

namespace input_events {

/**
 * @brief The buffer class used by SerialMessageEvents 
 * 
 */
struct BasicBuffer {
    char* buffer;
    size_t bufferSize; //capacity
    size_t bufferLength; //used

    /**
     * @brief Construct a BasicBuffer
     * 
     * @param buffer A pointer to an external bufffer
     * @param bufferSize  The external buffer size (capacity)
     * @param bufferLength The length of the buffer contents
     */
    BasicBuffer(char* buffer, size_t bufferSize, size_t bufferLength = 0) : 
        buffer(buffer), bufferSize(bufferSize), bufferLength(bufferLength) 
        { //Sanity checks...
            if (!buffer || bufferLength > bufferSize) {
                this->buffer = nullptr;
                this->bufferSize = this->bufferLength = 0;
            }
        }            
        void clear() { 
            if (buffer && bufferSize > 0) {
                buffer[0] = '\0';
            }
            bufferLength = 0;
        } 

};

/**
 * @brief A read only buffer class for SerialMessageEvents messages and key/value pairs
 * 
 */
struct BasicBufferView {
    const char* buffer;
    const size_t bufferSize; //capacity
    const size_t bufferLength; //used

    /**
     * @brief Construct an empty buffer (used when a value of a key/value pair does not hols a value)
     */
    BasicBufferView() //An empty buffer view
        : buffer(nullptr), bufferSize(0), bufferLength(0) {}
    /**
     * @brief Construct a BasicBufferView from a char array
     * 
     * @param buffer A pointer to an external bufffer
     * @param bufferSize  The external buffer size (capacity)
     * @param bufferLength The length of the buffer contents
     */
    BasicBufferView(const char* buffer, size_t bufferSize, size_t bufferLength)
        : buffer(buffer), bufferSize(bufferSize), bufferLength(bufferLength) {}
    /**
     * @brief Construct a BasicBufferView from a BasicBuffer
     * 
     * @param buf A BasicBuffer
     */
    BasicBufferView(const BasicBuffer& buf) :
        buffer(buf.buffer), bufferSize(buf.bufferSize), bufferLength(buf.bufferLength) {}
};

} //namespace
#endif