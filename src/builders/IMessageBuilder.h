#ifndef INPUT_EVENTS_IMESSAGE_BUILDER_H
#define INPUT_EVENTS_IMESSAGE_BUILDER_H

#include <Arduino.h> //Required for DEC

namespace input_events {

/**
 * @brief Encode outgoing messages and send via IMessageProcessor
 * 
 */
class IMessageBuilder {

    public:
    virtual ~IMessageBuilder() = default;

    /**
     * @brief Start a new message. Will clear an existing message if already started.
     * 
     */
    virtual void startMessage() = 0;
    
    /**
     * @brief End the message and write it to the IEventMessenger
     * 
     */
    virtual bool sendMessage() = 0;

    /**
     * @brief Clear a message (end without sending)
     * 
     */
    virtual void clearMessage() = 0;

    /**
     * @brief Returns true if the message has been started
     * 
     * @return true 
     * @return false 
     */
    virtual bool isMessageStarted() = 0;

    /**
     * @brief Get the length of the current message
     * 
     * @return size_t 
     */
    virtual size_t getMessageLength() = 0;

    /**
     * @brief Rollback a started message to a checkpoint
     * 
     * @param checkpoint  A previously obtained getMessageLength
     */
    virtual void rollback(size_t checkpoint) = 0;


};

}

#endif