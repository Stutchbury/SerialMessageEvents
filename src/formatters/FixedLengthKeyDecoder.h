#ifndef INPUT_EVENTS_FIXED_LENGTH_KEY_DECODER_H
#define INPUT_EVENTS_FIXED_LENGTH_KEY_DECODER_H
#include "BaseKeyValueDecoder.h"

namespace input_events {

/**
 * @brief A fixed key length (and variable value) decoder. Can only return a single record, so template arg is fixed.
 * 
 */
class FixedLengthKeyDecoder : public BaseKeyValueDecoder<1> {
public:
    /**
     * @brief Construct a FixedLengthKeyDecoder passing the key length
     * 
     * @param keyLength 
     */
    FixedLengthKeyDecoder(size_t keyLength)
        : _keyLength(keyLength) {}

    /**
     * @brief Decode a message into a key/value pair. Can only crete a single record.
     * 
     * @param message 
     * @return true 
     * @return false 
     */
    bool decode(const BasicBufferView& message) override {

        this->resetRecords();

        if ( message.bufferLength == 0 ) return false;

        this->_recordCount = 0;
        this->_buffer = message.buffer;
        this->_bufferLength = message.bufferLength;

        size_t offset = 0;

        //Can only create a single record
        size_t key_start = offset;
        size_t key_length = min(_keyLength, _bufferLength); //For short key and no value
        offset += key_length;
        size_t value_start = offset;
        size_t value_length = _bufferLength - offset;

        typename BaseKeyValueDecoder<1>::Record record = {
            static_cast<uint16_t>(key_start),
            static_cast<uint16_t>(key_length),
            static_cast<uint16_t>(value_start),
            static_cast<uint16_t>(value_length)
        };

        this->records[this->_recordCount++] = record;


        return this->_recordCount > 0;
    }


private:
    size_t _keyLength;

// void dumpBuffer(const char* label, const char* buf, size_t len) {
//     printf("%s: \"", label);
//     for (size_t i = 0; i < len; ++i) {
//         unsigned char c = static_cast<unsigned char>(buf[i]);
//         if (isprint(c)) {
//             printf("%c", c);
//         } else {
//             printf("\\x%02X", c);
//         }
//     }
//     printf("\"\n");
// }



};

} // namespace input_events

#endif