#ifndef INPUT_EVENTS_DELIMITED_KEY_VALUE_DECODER_H
#define INPUT_EVENTS_DELIMITED_KEY_VALUE_DECODER_H

#include "BaseKeyValueDecoder.h"

namespace input_events {

/**
 * @brief Decode ke/values from a message using record and unit separators
 * 
 * @tparam MaxRecords 
 */
template<size_t MaxRecords = SERIAL_MESSAGE_EVENTS_DEFAULT_NUM_DECODER_RECORDS>
class DelimitedKeyValueDecoder : public BaseKeyValueDecoder<MaxRecords> {


    public:

    /**
     * @brief Construct a DelimitedKeyValueDecoder with the group and unit separator
     * 
     * @details Default separators are the ASCII <RS> and <US> but could be `:` and `=`. 
     * 
     * @param rs Any valid `char`
     * @param us Any valid `char`
     */
    DelimitedKeyValueDecoder(const char rs = 0x1E, const char us = 0x1F) :
        _rs(rs),
        _us(us)
        {}


    bool decode(const BasicBufferView& message) override {
        this->_recordCount = 0;
        this->_buffer = message.buffer;
        this->_bufferLength = message.bufferLength;
        this->resetRecords();

        size_t i = 0;
        while (i < this->_bufferLength && this->_recordCount < MaxRecords) {
            // Skip any leading record separators
            while (i < this->_bufferLength && this->_buffer[i] == _rs) {
                i++;
            }

            if (i >= this->_bufferLength) break;

            size_t key_start = i;
            size_t key_len = 0;
            size_t value_start = 0;
            size_t value_len = 0;

            // Scan for either unit separator or record separator
            while (i < this->_bufferLength && this->_buffer[i] != _us && this->_buffer[i] != _rs) i++;
            key_len = i - key_start;

            // Malformed: no key
            if (key_len == 0) {
                // Skip until next record
                while (i < this->_bufferLength && this->_buffer[i] != _rs) i++;
                if (i < this->_bufferLength && this->_buffer[i] == _rs) i++;
                continue;
            }

            if (i < this->_bufferLength && this->_buffer[i] == _us) {
                // Key-value pair
                i++; // skip _us
                value_start = i;
                while (i < this->_bufferLength && this->_buffer[i] != _rs) i++;
                value_len = i - value_start;
            }

            // Record separator (if present)
            if (i < this->_bufferLength && this->_buffer[i] == _rs) i++;

            if (key_len > 0) {
                typename BaseKeyValueDecoder<MaxRecords>::Record record = {
                    static_cast<uint16_t>(key_start),
                    static_cast<uint16_t>(key_len),
                    static_cast<uint16_t>(value_start),
                    static_cast<uint16_t>(value_len)
                };
                this->records[this->_recordCount++] = record;
            }

        }

        return this->_recordCount > 0;
    }


    /**
     * @brief Set a new record separator
     * 
     * @param rs `char`
     */
    void setRecordSeparator(char rs) {
        _rs = rs;
    }

    /**
     * @brief Set a new unit separator
     * 
     * @param us `char`
     */
    void setUnitSeparator(char us) {
        _us = us;
    }

    private:
    char _rs; //Record separater - often `\x1E` <RS>, ':', or ';'
    char _us; //Unit separater - often `\x1F` <US> or '='

};
} //namespace

#endif