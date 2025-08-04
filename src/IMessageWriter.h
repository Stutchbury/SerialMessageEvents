#ifndef INPUT_EVENTS_IMESSAGE_WRITER_H
#define INPUT_EVENTS_IMESSAGE_WRITER_H


#include <Arduino.h>
#include "BasicBuffer.h"

namespace input_events {

/**
 * @brief The IMessageWriter interface (implemented by both IEventMessenger and IMessageFramer)
 * 
 */
class IMessageWriter {

public:

    /**
     * @brief Write the message provided in the writeBuffer to serial and return the number of bytes written
     * 
     * @param writeBuffer 
     * @return size_t Because the framer may top and tail the message, the returned size_t may be longer than the message length
     */
    virtual size_t writeMessage(const BasicBufferView& writeBuffer, uint8_t priority=10) = 0;

};

} //namespace


#endif