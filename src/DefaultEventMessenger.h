#ifndef INPUT_EVENTS_DEFAULT_BASE_MESSENGER_H
#define INPUT_EVENTS_DEFAULT_BASE_MESSENGER_H

// #include <cstddef>
// #include <stdint.h>
#include <Arduino.h>

#include "BaseEventMessenger.h"
#include "BasicBuffer.h"

namespace input_events {

/**
 * @brief The default implementation of IEventMessenger that Gets messages from framer, passing to an IMessageConsumer and optionally writes messages to framer
 * 
 */
class DefaultEventMessenger : public BaseEventMessenger {

    public:
    virtual ~DefaultEventMessenger() = default;

    /**
     * @brief Construct a DefaultEventMessenger with a read BasicBuffer and a framer
     * 
     * @param readBuffer 
     * @param framer 
     */
    DefaultEventMessenger(BasicBuffer& readBuffer, IMessageFramer* framer) :
        BaseEventMessenger(framer), 
        readBuffer(readBuffer)
        {}

    /**
     * @brief Construct a DefaultEventMessenger with a BasicBuffer, a framer and a consumer
     * 
     * @param readBuffer 
     * @param framer 
     * @param consumer 
     */
    DefaultEventMessenger(BasicBuffer& readBuffer, IMessageFramer* framer, IMessageConsumer* consumer) :
        BaseEventMessenger(framer, consumer),
        readBuffer(readBuffer)
        {}


    /**
     * @brief Check for messages available from IMessageFramer and pass to an IMessageConsumer or IMessageConsumer::MessageReceivedFunction
     * 
     */
    virtual void update() override {
        if ( this->framer != nullptr && this->framer->readMessage(this->readBuffer) != 0 ) {
            if ( this->consumer != nullptr ) {
                this->consumer->onMessageReceived(BasicBufferView(this->readBuffer));
            } else if ( this->callbackFunction != nullptr ) {
                this->callbackFunction(BasicBufferView(this->readBuffer));
            }
            this->framer->consumeMessage();
        }
    }

    /**
     * @brief Write a message to an IMessageFramer
     * 
     * @param message A BasicBufferView
     * @param priority Only used if a message queue is implemented
     * @return size_t 
     */
    virtual size_t writeMessage(const BasicBufferView& message, uint8_t priority=10) override {
        if ( this->framer != nullptr ) {
            return this->framer->writeMessage(message);
        }
        return 0;
    }

    private:

    BasicBuffer& readBuffer;

};

}

#endif