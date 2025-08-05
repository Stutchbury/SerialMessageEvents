#ifndef INPUT_EVENTS_BASE_KEY_VALUE_DECODER_H
#define INPUT_EVENTS_BASE_KEY_VALUE_DECODER_H

#include "IKeyValueDecoder.h"

namespace input_events {

#ifndef SERIAL_MESSAGE_EVENTS_DEFAULT_NUM_DECODER_RECORDS
#define SERIAL_MESSAGE_EVENTS_DEFAULT_NUM_DECODER_RECORDS 10
#endif

/**
 * @brief Decode messages after they have passed though IMessageFramer. Default number of records ia 10.
 * 
 * @details The 'records' are just offsets + lengths of keys/values (ie 4 x `uint16_t` per record)
 * 
 */
template<size_t MaxRecords = SERIAL_MESSAGE_EVENTS_DEFAULT_NUM_DECODER_RECORDS>
class BaseKeyValueDecoder : public IKeyValueDecoder {

    public:

    virtual size_t recordCount() const override {
        return _recordCount;
    }

    virtual BasicBufferView key(size_t index) const {
        if (index >= _recordCount) return {};
        const Record& r = records[index];
        return BasicBufferView(_buffer + r.keyOffset, r.keyLength, r.keyLength);
    }

    virtual BasicBufferView value(size_t index) const {
        if (index >= _recordCount) return {};
        const Record& r = records[index];
        return BasicBufferView(_buffer + r.valueOffset, r.valueLength, r.valueLength);
    }

    virtual void resetRecords() {
        for ( size_t i=0; i<MaxRecords; ++i ) {
            records[i].keyOffset = 0;
            records[i].keyLength = 0;
            records[i].valueOffset = 0;
            records[i].valueLength = 0;
        }
    }

    protected:

    struct Record {
        uint16_t keyOffset;
        uint16_t keyLength;
        uint16_t valueOffset;
        uint16_t valueLength;
    };


    Record records[MaxRecords];
    size_t _recordCount = 0;
    const char* _buffer = nullptr;
    size_t _bufferLength = 0;


};

}

#endif