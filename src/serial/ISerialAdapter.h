#ifndef INPUT_EVENTS_ISerialAdapter_H
#define INPUT_EVENTS_ISerialAdapter_H

// #include <cstddef>
// #include <stdint.h>
#include <Arduino.h>

namespace input_events {
/**
 * @brief An adapter interface for any seraial char stream
 * 
 */
class ISerialAdapter {
public:

    virtual ~ISerialAdapter() = default;

    virtual void begin() = 0;

    virtual void end() = 0;

    /**
     * @brief Returns number of bytes available for read()
     * 
     * @return int 
     */
    virtual int available() const = 0;

    /**
     * @brief Read the stream 
     * 
     * @param buffer 
     * @param maxLen 
     * @return size_t 
     */
    virtual int read() = 0;  // returns -1 if no data

    /**
     * @brief Returns number of bytes available for write()
     * 
     * Note: Software UART serial implementations will always return 0
     * https://docs.arduino.cc/language-reference/en/functions/communication/serial/availableForWrite/#notes-and-warnings
     * 
     * @return int 
     */
    virtual int availableForWrite() const = 0;

    /**
     * @brief 
     * 
     * @param buffer 
     * @param len 
     * @return size_t 
     */
    virtual size_t write(const char* buffer, size_t len) = 0; //Add uint8_t messagePriority=10 if queueing is implemented

};

}

#endif
