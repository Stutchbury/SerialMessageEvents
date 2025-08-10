#ifndef INPUT_EVENTS_BASE_EVENT_MESSENGER_H
#define INPUT_EVENTS_BASE_EVENT_MESSENGER_H

// #include <cstddef>
// #include <stdint.h>
#include <Arduino.h>

#include "IEventMessenger.h"
#include "Framer/IMessageFramer.h"
#include "IMessageConsumer.h"

namespace input_events {

/**
 * @brief The default implementation of IEventMessenger that gets messages from an IMessageFramer and passes to an IMessageConsumer. Also writes messages to the IMessageFramer
 * 
 */
class BaseEventMessenger : public IEventMessenger {

    public:


    virtual ~BaseEventMessenger() = default;

    /**
     * @brief Construct a BaseEventMessenger with just a framer (set the consumer later with setMessageConsumer())
     * 
     * @param framer 
     */
    BaseEventMessenger(IMessageFramer* framer) :
        framer(framer)
        {}

    /**
     * @brief Construct a BaseEventMessenger with a framer and a consumer
     * 
     * @param framer 
     * @param consumer 
     */
    BaseEventMessenger(IMessageFramer* framer, IMessageConsumer* consumer) :
        framer(framer),
        consumer(consumer)
        {}

    /**
     * @brief Will call the framer's begin()
     * 
     */
    virtual void begin() override {
        if ( framer != nullptr ) framer->begin();
    }

    /**
     * @brief Will call the framer's end()
     * 
     */
    virtual void end() override {
        if ( framer != nullptr ) framer->end();
    }

    /**
     * @brief Set the MessageFramer
     * 
     * @param framer 
     */
    void setMessageFramer(IMessageFramer* framer) {
        this->framer = framer;
    }

    /**
     * @brief Get the MessageFramer
     * 
     * @return IMessageFramer* 
     */
    IMessageFramer* getMessageFramer() {
        return this->framer;
    }

    /**
     * @brief Set the MessageConsumer
     * 
     * @param consumer 
     */
    void setMessageConsumer(IMessageConsumer* consumer) {
        this->framer = framer;
    }

    /**
     * @brief Get the MessageConsumer
     * 
     * @return IMessageConsumer* 
     */
    IMessageConsumer* getMessageConsumer() {
        return this->consumer;
    }

    /**
     * @brief Set the Callback function.
     * 
     * @param f A function of type <code>IMessageConsumer::MessageReceivedFunction</code> type.
     */
    void setCallback(IMessageConsumer::MessageReceivedFunction f) {
        callbackFunction = f;
    }

    void unsetCallback() {
        callbackFunction = nullptr;
    }

    bool isCallbackSet() {
        return callbackFunction != nullptr;
    }

    protected:

    IMessageFramer* framer = nullptr;
    IMessageConsumer* consumer = nullptr;
    IMessageConsumer::MessageReceivedFunction callbackFunction = nullptr;

};

}

#endif