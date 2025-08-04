#ifndef INPUT_EVENTS_IMESSAGE_PROCESSOR_H
#define INPUT_EVENTS_IMESSAGE_PROCESSOR_H

// #include <cstddef>
// #include <stdint.h>
#include <Arduino.h>

#include "IMessageWriter.h"
#include "BasicBuffer.h"

namespace input_events {

/**
 * @brief Gets messages from framer and passes an IMessageConsumer and wtite messages to framer
 * 
 */
class IEventMessenger : public IMessageWriter {

    public:
    virtual ~IEventMessenger() = default;

    virtual void begin() = 0;
    virtual void end() = 0;

    /**
     * @brief Check for messages available from IMessageFramer and pass to an IMessageConsumer
     * 
     */
    virtual void update() = 0;

};

}

#endif