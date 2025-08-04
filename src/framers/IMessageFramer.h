#ifndef INPUT_EVENTS_IMESSAGE_FRAMER_H
#define INPUT_EVENTS_IMESSAGE_FRAMER_H

//#include <cstddef>
#include "IMessageReader.h"
#include "IMessageWriter.h"
#include "BasicBuffer.h"


namespace input_events {
/**
 * @brief Converts a stream to a whole message, stripping start/end markers an doing any required LRC checks etc
 * 
 */
class IMessageFramer : public IMessageReader, public IMessageWriter{
public:
    virtual ~IMessageFramer() = default;

    virtual void begin() = 0;

    virtual void end() = 0;

    /**
     * @brief Tell the framer the current message has been consumed and a new message can be made available for readMessage().
     * 
     */
    virtual void consumeMessage() = 0;

};
}
#endif
