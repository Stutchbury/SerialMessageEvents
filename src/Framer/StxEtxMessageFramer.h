#ifndef INPUT_EVENTS_STX_ETX_MESSAGE_FRAMER_H
#define INPUT_EVENTS_STX_ETX_MESSAGE_FRAMER_H

#include "BaseMessageFramer.h"
#include "SerialAdapter/ISerialAdapter.h"

namespace input_events {
/**
 * @brief An IMessageFramer that implements an STX/ETX wrapper for messages
 * 
 */
class StxEtxMessageFramer : public BaseMessageFramer {
public:
    static constexpr char STX = '\x02'; // Start of Text
    static constexpr char ETX = '\x03'; // End of Text

    StxEtxMessageFramer(ISerialAdapter* serial) : serial(serial) {}


    /**
     * @brief Read from serial to copy the actual message into the readBuffer, set messageStart if required and return message length
     * 
     * @details 
     * 
     * @param readBuffer 
     * @param messageStart 
     * @return size_t 
     */
    size_t readMessage(BasicBuffer& readBuffer) override {
        while (!messageReady && serial && serial->available()) {
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
        messageReady = false;
        messageStarted = false;
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
        #ifdef __AVR__ //Because AVR framework cannot see class static constexpr in linker... \_O_/
        char stx = input_events::StxEtxMessageFramer::STX;        
        char etx = input_events::StxEtxMessageFramer::ETX;
        written += serial->write(&stx, 1);
        written += serial->write(writeBuffer.buffer, writeBuffer.bufferLength);
        written += serial->write(&etx, 1);
        #else
        written += serial->write(&STX, 1);
        written += serial->write(writeBuffer.buffer, writeBuffer.bufferLength);
        written += serial->write(&ETX, 1);
        #endif
        return written;
    }



private:
    ISerialAdapter* serial;
    bool messageStarted = false;
    bool messageReady = false;

    void handleByte(char c, BasicBuffer& readBuffer) {
        // printf("handleByte: '%c' (%02X), started=%d, ready=%d, len=%zu\n",
        //     (isprint(c) ? c : '.'), (unsigned char)c, messageStarted, messageReady, messageLength);
        if (c == STX) {
            messageStarted = true;
            readBuffer.bufferLength = 0;
            return;
        }
        if (!messageStarted) return;

        if (c == ETX) {
            readBuffer.buffer[readBuffer.bufferLength] = '\0';
            messageReady = true;
            messageStarted = false;
            return;
        }

        if (readBuffer.bufferLength < readBuffer.bufferSize-1) {
            readBuffer.buffer[readBuffer.bufferLength++] = c;
        }
    }
};
}
#endif
