#ifndef INPUT_EVENTS_IKEY_VALUE_CONSUMER_H
#define INPUT_EVENTS_IKEY_VALUE_CONSUMER_H

#include <Arduino.h> //Required for DEC
#include "BasicBuffer.h"

namespace input_events {

/**
 * @brief Process key/value pairs after they have passed though IMessageDecoder
 * 
 * @details This is the entry point to your app.
 * 
 */
class IKeyValueConsumer {

    public:

    /**
     * @brief Process or handle the key/value pair from IMessageDecoder
     * 
     * @param key BasicBufferView NOTE: The buffer is *not* null termnated - user the bufferLength
     * @param value BasicBufferView NOTE: The buffer is *not* null termnated - user the bufferLength. This may be an empty buffer.
     */
    virtual void onKeyValueReceived(const BasicBufferView& key, const BasicBufferView& value = {}) = 0;

    
};

}

#endif