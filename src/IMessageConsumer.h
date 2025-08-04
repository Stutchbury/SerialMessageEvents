#ifndef INPUT_EVENTS_IMESSAGE_CONSUMER_H
#define INPUT_EVENTS_IMESSAGE_CONSUMER_H

//#include <cstddef>
#include "FunctionalSupported.h"
#include "BasicBuffer.h"

namespace input_events {

/**
 * @brief Passes messages to a decoder after they have passed though IMessageFramer
 * 
 */
class IMessageConsumer {

    public:

    /**
     * @brief Process a received message
     * 
     * @param message Message passed in from IEventMessenger. This will normally be null terminated.
     */
    virtual void onMessageReceived(const BasicBufferView& message) = 0;


    #if defined(FUNCTIONAL_SUPPORTED)
    /**
     * @brief If <code>std::function</code> is supported, use to create the callback type.
     */
    typedef std::function<void(const BasicBufferView& message)> MessageReceivedFunction;
    #else
    /**
     * @brief Create the callback type as pointer if <code>std::function</code> is not supported.
     */
    typedef void (*MessageReceivedFunction)(const BasicBufferView& message);
    #endif

};

}

#endif