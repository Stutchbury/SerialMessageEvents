#ifndef INPUT_EVENTS_IMESSAGE_DECODER_H
#define INPUT_EVENTS_IMESSAGE_DECODER_H

#include <Arduino.h> //Required for DEC
#include "BasicBuffer.h"

namespace input_events {

/**
 * @brief Decode messages from an IMessageConsumer (after they have passed though IMessageFramer) and (usually) passes on to a specialised consumer (eg an IKeyValueConsumer)
 * 
 */
class IMessageDecoder {

    public:

    /**
     * @brief Decode the message and return true if successful
     * 
     * @param message A BasicBufferView passed in from IMessageProcessor
     * @return true Message has been decoded
     * @return false Decoding failed
     */
    virtual bool decode(const BasicBufferView& message) = 0;

    /**
     * @brief The number of records created by the decode() method.
     * 
     * @return size_t 
     */
    virtual size_t recordCount() const = 0;

    protected:

};

}

#endif