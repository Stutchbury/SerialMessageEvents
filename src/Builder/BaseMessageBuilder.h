#ifndef INPUT_EVENTS_BASE_MESSAGE_BUILDER_H
#define INPUT_EVENTS_BASE_MESSAGE_BUILDER_H

#include "BasicBuffer.h"
#include "IMessageBuilder.h"
//#include "IEventMessenger.h"
#include "IMessageWriter.h"

namespace input_events {

/**
 * @brief Encode outgoing messages and send via IMessageProcessor
 * 
 */
class BaseMessageBuilder : public IMessageBuilder {

    public:

    //BaseMessageBuilder() {}

    BaseMessageBuilder(BasicBuffer& writeBuffer, IMessageWriter* writer) :
        writeBuffer(writeBuffer),
        messageStarted(false),
        writer(writer) 
        {}

    BaseMessageBuilder(BasicBuffer& writeBuffer) :
        writeBuffer(writeBuffer),
        messageStarted(false)
        {}


    virtual ~BaseMessageBuilder() = default;

    /**
     * @brief Start a new message. Will clear an existing message if already started.
     * 
     */
    virtual void startMessage() override {
        writeBuffer.clear();
        messageStarted = true;
    }
    
    /**
     * @brief End the message and write it to the IEventMessenger
     * 
     */
    virtual bool sendMessage() override {
        if ( writer == nullptr ) return false;
        return writer->writeMessage(writeBuffer);
    }

    /**
     * @brief Clear a message (end without sending)
     * 
     */
    virtual void clearMessage() override {
        writeBuffer.clear();
        messageStarted = false;
    }

    /**
     * @brief Returns true if the message has been started
     * 
     * @return true 
     * @return false 
     */
    virtual bool isMessageStarted() override {
        return messageStarted;
    }

    /**
     * @brief Get the length of the current message
     * 
     * @return size_t 
     */
    virtual size_t getMessageLength() override {
        return writeBuffer.bufferLength;
    }

    /**
     * @brief Rollback a started message to a checkpoint
     * 
     * @param checkpoint  A previously obtained getMessageLength
     */
    virtual void rollback(size_t checkpoint) {
        writeBuffer.bufferLength = checkpoint;
        writeBuffer.buffer[writeBuffer.bufferLength] = '\0';
    }
    
    
    /**
     * @brief Set the IEventMessenger for the builder
     * 
     * @param messenger 
     */
    // void setEventMessenger(IEventMessenger* messenger) {
    //     this->messenger = messenger;
    // }
    void setMessageWriter(IMessageWriter* writer) {
        //this->messenger = messenger;
        this->writer = writer;
    }

    protected:
    BasicBuffer writeBuffer;
    bool messageStarted = false;

    private:

    //IEventMessenger* messenger;
    IMessageWriter* writer = nullptr;



};

}

#endif