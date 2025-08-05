#ifndef INPUT_EVENTS_IKEY_VALUE_DECODER_H
#define INPUT_EVENTS_IKEY_VALUE_DECODER_H

#include <Arduino.h> //Required for DEC
#include "IMessageDecoder.h"

namespace input_events {

/**
 * @brief Decode messages from an IMessageConsumer into key/value pairs
 *  
 */
class IKeyValueDecoder : public IMessageDecoder {

    public:

    /**
     * @brief Return the key BasicBufferView for the record at `index. Will return an empy buffer if the index is invalid
     * 
     * @param index 
     * @return BasicBufferView 
     */
    virtual BasicBufferView key(size_t index) const = 0;

    /**
     * @brief Return the value BasicBufferView for the record at `index`. May be an empty buffer if there is no value set for the key or the index is invalid
     * 
     * @param index 
     * @return BasicBufferView 
     */
    virtual BasicBufferView value(size_t index) const = 0;

    protected:

};

}

#endif