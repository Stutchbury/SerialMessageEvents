#ifndef INPUT_EVENTS_BASE_MESSAGE_FRAMER_H
#define INPUT_EVENTS_BASE_MESSAGE_FRAMER_H

#include "IMessageFramer.h"
#include "serial/ISerialAdapter.h"

namespace input_events {
/**
 * @brief Base class for concrete IMessageFramer, adds a setter for ISerialAdapter
 * 
 */
class BaseMessageFramer : public IMessageFramer {
public:
    virtual ~BaseMessageFramer() = default;


    virtual void begin() {
        if ( this->serial != nullptr ) this->serial->begin();
    }

    virtual void end() {
        if ( this->serial != nullptr ) this->serial->end();
    }

    /**
     * @brief Set the ISerialAdapter to read from/write to.
     * 
     * @param serial 
     */
    void setSerial(ISerialAdapter* serial) {
        this->serial = serial;
    }


    private:
    ISerialAdapter* serial;

};
}
#endif
