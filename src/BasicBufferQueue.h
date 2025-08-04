#ifndef INPUT_EVENTS_BASIC_BUFFER_QUEUE_H
#define INPUT_EVENTS_BASIC_BUFFER_QUEUE_H

#include <Arduino.h>
#include "BasicBuffer.h"

namespace input_events {

template<size_t MaxQueueSize = 10, size_t BufferSize = 64>
class BasicBufferQueue {
public:
    // static constexpr size_t MAX_QUEUE_SIZE = 8;
    // static constexpr size_t BUFFER_CAPACITY = 64;

    BasicBufferQueue() : head(0), tail(0), count(0) {
        for (size_t i = 0; i < MaxQueueSize; ++i) {
            // Construct each BasicBuffer in-place using the pre-allocated buffer
            new (&slots[i]) BasicBuffer(storage[i], BufferSize);
        }
    }

    // Enqueue: Deep copy input buffer into internal storage
    bool enqueue(const BasicBuffer& input) {
        if (isFull() || input.bufferLength > BufferSize)
            return false;

        BasicBuffer& target = slots[tail];
        memcpy(target.buffer, input.buffer, input.bufferLength);
        target.bufferLength = input.bufferLength;
        target.buffer[target.bufferLength] = '\0'; // Optional null termination

        tail = (tail + 1) % MaxQueueSize;
        ++count;
        return true;
    }

    // Enqueue: Deep copy input buffer into internal storage
    bool enqueue(const BasicBufferView& input) {
        if (isFull() || input.bufferLength > BufferSize)
            return false;

        BasicBuffer& target = slots[tail];
        memcpy(target.buffer, input.buffer, input.bufferLength);
        target.bufferLength = input.bufferLength;
        target.buffer[target.bufferLength] = '\0'; // Optional null termination

        tail = (tail + 1) % MaxQueueSize;
        ++count;
        return true;
    }


    bool enqueue(const char* str) {
        if (!str) return false;

        size_t len = strlen(str);
        if (len > BufferSize || isFull()) return false;

        // Create a temporary buffer to wrap the string
        char temp[BufferSize + 1];
        memcpy(temp, str, len);
        temp[len] = '\0';

        BasicBuffer tempBuffer(temp, sizeof(temp), len);
        return enqueue(tempBuffer);  // Delegate to main enqueue
    }

    bool enqueue(const char* str, size_t bufferLength) {
        if (!str) return false;

        //size_t len = strlen(str);
        if (bufferLength > BufferSize || isFull()) return false;

        // Create a temporary buffer to wrap the string
        char temp[BufferSize + 1];
        memcpy(temp, str, bufferLength);
        temp[bufferLength] = '\0';

        BasicBuffer tempBuffer(temp, sizeof(temp), bufferLength);
        return enqueue(tempBuffer);  // Delegate to main enqueue
    }


    // Dequeue: Deep copy into user-provided BasicBuffer
    bool dequeue(BasicBuffer& output) {
        if ( isEmpty() ) return false;
        if ( slots[head].bufferLength > output.bufferSize ) return false;
        BasicBuffer& source = slots[head];
        memcpy(output.buffer, source.buffer, source.bufferLength);
        output.bufferLength = source.bufferLength;
        output.buffer[output.bufferLength] = '\0'; // Optional

        head = (head + 1) % MaxQueueSize;
        --count;
        return true;
    }

    void clear() {
        head = tail = count = 0;
        for (size_t i = 0; i < MaxQueueSize; ++i) {
            slots[i].bufferLength = 0;
            slots[i].buffer[0] = '\0';
        }
    }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == MaxQueueSize; }
    size_t size() const { return count; }

private:
    // Pre-allocated buffer storage
    char storage[MaxQueueSize][BufferSize + 1];

    // `slots` contains `BasicBuffer` objects constructed with placement new
    alignas(BasicBuffer) uint8_t rawSlots[MaxQueueSize * sizeof(BasicBuffer)];
    BasicBuffer* slots = reinterpret_cast<BasicBuffer*>(rawSlots);

    size_t head;
    size_t tail;
    size_t count;
};
} //namespace

#endif