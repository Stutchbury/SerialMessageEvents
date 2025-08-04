#ifndef INPUT_EVENTS_FIXED_LENGTH_KEY_VALUE_DECODER_H
#define INPUT_EVENTS_FIXED_LENGTH_KEY_VALUE_DECODER_H
#include "BaseKeyValueDecoder.h"

namespace input_events {

    /**
 * @brief A strict key+value length decoder. 
 * 
 * @details If the bufferLength is not a multiple of keyLength+valueLength will return false
 * If the bufferLength is greater than (keyLength+valueLength)*MaxRecords will return false
 * 
 * @tparam MaxRecords 
 */
template<size_t MaxRecords = SERIAL_MESSAGE_EVENTS_DEFAULT_NUM_DECODER_RECORDS>
class FixedLengthKeyValueDecoder : public BaseKeyValueDecoder<MaxRecords> {
public:
    FixedLengthKeyValueDecoder(size_t keyLength, size_t valueLength)
        : _keyLength(keyLength), _valueLength(valueLength) {}

bool decode(const BasicBufferView& message) override {

    this->resetRecords();

    if ( message.bufferLength % (_keyLength+_valueLength) != 0 ) return false;
    if ( message.bufferLength > (_keyLength+_valueLength)*MaxRecords ) return false;

    this->_recordCount = 0;
    this->_buffer = message.buffer;
    this->_bufferLength = message.bufferLength;

    size_t offset = 0;

    while (offset < this->_bufferLength && this->_recordCount < MaxRecords) {

        size_t key_start = offset;
        offset += _keyLength;
        size_t value_start = offset;
        offset += _valueLength;

        typename BaseKeyValueDecoder<MaxRecords>::Record record = {
            static_cast<uint16_t>(key_start),
            static_cast<uint16_t>(_keyLength),
            static_cast<uint16_t>(value_start),
            static_cast<uint16_t>(_valueLength)
        };

        this->records[this->_recordCount++] = record;
    }


    return this->_recordCount > 0;
}


private:
    size_t _keyLength;
    size_t _valueLength;

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