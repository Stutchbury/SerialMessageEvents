#ifndef INPUT_EVENTS_IMESSAGE_READER_H
#define INPUT_EVENTS_IMESSAGE_READER_H

#include <Arduino.h>
#include "BasicBuffer.h"

namespace input_events {

/**
 * @brief The IMessageReader interface
 * 
 */
class IMessageReader {

public:

    /**
     * @brief Put a message into the readBuffer and return the size of the message.
     * 
     * @param readBuffer 
     * @return size_t 
     */
    virtual size_t readMessage(BasicBuffer& readBuffer) = 0;


};

} //namespace
#endif