#ifndef INPUT_EVENTS_CRLF_MESSAGE_FRAMER_H
#define INPUT_EVENTS_CRLF_ETX_MESSAGE_FRAMER_H

#include "BaseMessageFramer.h"
#include "serial/ISerialAdapter.h"

namespace input_events {
/**
 * @brief An IMessageFramer that implements a CR/LF message (primarily used for dev/testing via a terminal)
 * 
 */
class CrLfMessageFramer : public BaseMessageFramer {
public:

    CrLfMessageFramer(ISerialAdapter* serial) : serial(serial) {}

    /**
     * @brief Read from serial to copy the actual message into the readBuffer, set messageStart if required and return message lenght
     * 
     * @param readBuffer 
     * @return size_t 
     */
    size_t readMessage(BasicBuffer& readBuffer) override {
        while (!messageReady && serial && serial->available()) {
            if ( !messageStarted ) readBuffer.clear();
            char c = serial->read();
            if ( c != -1) {
                handleByte(c, readBuffer);
            }
        }
        return messageReady ? readBuffer.bufferLength : 0;
    }

    /**
     * @brief Consume the current message
     * 
     */
    void consumeMessage() override {
        //messageConsumed = true;
        messageStarted = false;
        messageReady = false;
        //messageLength = 0;
    }

    /**
     * @brief Frame the message and write to serial
     * 
     * @param writeBuffer 
     * @return size_t 
     */
    size_t writeMessage(const BasicBufferView& writeBuffer, uint8_t priority=10) override {
    //size_t writeMessage(const BasicBufferView& writeBuffer) override {
        if (!serial) return 0;
        size_t written = 0;
        written += serial->write(writeBuffer.buffer, writeBuffer.bufferLength);
        const char crlf[] = "\r\n";
        written += serial->write(crlf, 2);
        //written += serial->write("", 1); //Add `\0` in the most 'C' way possible...not required?
        return written;
    }


private:
    ISerialAdapter* serial;
    bool messageStarted = false;
    bool messageReady = false;

    void handleByte(char c, BasicBuffer& readBuffer) {
        //if ( c == '\r') return;
        if (c != '\n' && c != '\t' && (static_cast<unsigned char>(c) < 32 || static_cast<unsigned char>(c) == 127)) return; //Ignore control chars except new line and tab
        messageStarted = true;
        if (c == '\n') {
            readBuffer.buffer[readBuffer.bufferLength] = '\0';
            messageReady = true;
            messageStarted = false;
            return;
        }

        if ( readBuffer.bufferLength < readBuffer.bufferSize-1) { // Leave room for null terminator
            readBuffer.buffer[readBuffer.bufferLength++] = c;
        }
    }

};
}
#endif
