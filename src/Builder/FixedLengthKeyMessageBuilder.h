#ifndef INPUT_EVENTS_FIXED_LENGTH_KEY_MESSAGE_BUILDER_H
#define INPUT_EVENTS_FIXED_LENGTH_KEY_MESSAGE_BUILDER_H

#include "DefaultMessageBuilder.h"
#include "Formatter/IKeyValueEncoder.h"

namespace input_events {

/**
 * @brief Encode outgoing messages and send via IEventMessenger
 * 
 */
template<size_t KeyLength>
class FixedLengthKeyMessageBuilder : public DefaultMessageBuilder,  IKeyValueEncoder {

    public:

    /**
     * @brief Construct a new FixedLengthKeyMessageBuilder
     * 
     * @param writeBuffer This is the buffer where the message will be created (and passed as a BasicBufferView to the IEventMessenger)
     * @param messenger The IEventMessenger where the message will be sent
     */
    FixedLengthKeyMessageBuilder(BasicBuffer& writeBuffer, IEventMessenger* messenger) :
        DefaultMessageBuilder::DefaultMessageBuilder(writeBuffer, messenger),
        keyLength(KeyLength)
        { }

    FixedLengthKeyMessageBuilder(BasicBuffer& writeBuffer) :
        DefaultMessageBuilder::DefaultMessageBuilder(writeBuffer),
        keyLength(KeyLength)
        { }


    virtual ~FixedLengthKeyMessageBuilder() = default;

    
    virtual size_t encode(const char* key) override {
        normalizeKey(key);
        return this->appendMessage(normalisedKey);
    }

    virtual size_t encode(char key) override {
        return this->appendMessage(key);
    }

    virtual size_t encode(const char* key, const char* value) override {
        normalizeKey(key);
        size_t checkpoint = this->writeBuffer.bufferLength;
        size_t keyLen = this->appendMessage(normalisedKey);
        size_t valLen = this->appendMessage(value);
        return hasEncoded(keyLen, valLen, checkpoint);
    }

    virtual size_t encode(const char* key, char c) override {
        normalizeKey(key);
        size_t checkpoint = this->writeBuffer.bufferLength;
        size_t keyLen = this->appendMessage(normalisedKey);
        size_t valLen = this->appendMessage(c);
        return hasEncoded(keyLen, valLen, checkpoint);
    }

    virtual size_t encode(const char* key, unsigned char c, int b = DEC) override {
        normalizeKey(key);
        size_t checkpoint = this->writeBuffer.bufferLength;
        size_t keyLen = this->appendMessage(normalisedKey);
        size_t valLen = this->appendMessage(c, b);
        return hasEncoded(keyLen, valLen, checkpoint);
    }

    virtual size_t encode(const char* key, int value, int base = DEC) override {
        normalizeKey(key);
        size_t checkpoint = this->writeBuffer.bufferLength;
        size_t keyLen = this->appendMessage(normalisedKey);
        size_t valLen = this->appendMessage(value, base);
        return hasEncoded(keyLen, valLen, checkpoint);
    }

    virtual size_t encode(const char* key, unsigned int value, int base = DEC) override {
        normalizeKey(key);
        size_t checkpoint = this->writeBuffer.bufferLength;
        size_t keyLen = this->appendMessage(normalisedKey);
        size_t valLen = this->appendMessage(value, base);
        return hasEncoded(keyLen, valLen, checkpoint);
    }

    virtual size_t encode(const char* key, long value, int base = DEC) override {
        normalizeKey(key);
        size_t checkpoint = this->writeBuffer.bufferLength;
        size_t keyLen = this->appendMessage(normalisedKey);
        size_t valLen = this->appendMessage(value, base);
        return hasEncoded(keyLen, valLen, checkpoint);
    }

    virtual size_t encode(const char* key, unsigned long value, int base = DEC) override {
        normalizeKey(key);
        size_t checkpoint = this->writeBuffer.bufferLength;
        size_t keyLen = this->appendMessage(normalisedKey);
        size_t valLen = this->appendMessage(value, base);
        return hasEncoded(keyLen, valLen, checkpoint);
    }

    virtual size_t encode(const char* key, double value, int digits = 4) override {
        normalizeKey(key);
        size_t checkpoint = this->writeBuffer.bufferLength;
        size_t keyLen = this->appendMessage(normalisedKey);
        size_t valLen = this->appendMessage(value, digits);
        return hasEncoded(keyLen, valLen, checkpoint);
    }

    void setKeyLength(uint8_t keyLength) {
        if ( keyLength == 0 ) return;
        this->keyLength = min(min(keyLength, KeyLength), writeBuffer.bufferSize-1);
    }


    protected:

    /**
     * @brief Ensure key is exactly keyLength. Not thread safe but if you're using threads, you're probably not the target demoographic for this library...
     * 
     * @param input 
     */
    void normalizeKey(const char* input) {
        size_t i = 0;
        for (; i < keyLength && input[i] != '\0'; ++i)
            normalisedKey[i] = input[i];
        for (; i < keyLength; ++i)
            normalisedKey[i] = ' ';
        normalisedKey[keyLength] = '\0';
    }

    size_t hasEncoded(size_t keyLen, size_t valLen, size_t checkpoint) {
        if ( keyLen == 0 || valLen == 0 ) {
            this->rollback(checkpoint);
            return 0;
        }
        return keyLen + valLen;
    }

    
    
    private:
    
    uint8_t keyLength = KeyLength;
    char normalisedKey[KeyLength+1] = {0};


};


} //namespace

#endif