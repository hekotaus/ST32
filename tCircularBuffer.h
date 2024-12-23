#pragma once
#include <array>
#include <stddef.h>

template <typename T, size_t TCapacity>
class tCircularBuffer {
private:
    size_t iIn = 0; // Where we pop from
    size_t iOut = 0; // Where we push to
    size_t Size = 0;
    size_t Capacity = TCapacity;
    bool Overflow = false; // Latching flag
    std::array<T, TCapacity> data;
    bool Overwrite = false; // if false, push will reject, when the buffer is full. ELSE it wil overwrite the oldest data

    size_t Cinc(size_t val) {
        if (Capacity == 0) return 0;
        if (val + 1 == Capacity) return 0; else return val + 1;
    }

    size_t Cdec(size_t val) {
        if (Capacity == 0) return 0;
        if (val == 0) return Capacity - 1; else return val - 1;
    }

public:
    //tCircularBuffer<T, Capacity>() {};
    size_t PeakSize = 0;
    bool IsOverflow() { return Overflow; }
    void ResetOverflow() { Overflow = false; }
    void setOverWrite(bool st) {
        Overwrite = st;
    }

    bool push(T val) {
    	if (Size == Capacity) Overflow = true;
        if (Overwrite || (Size < Capacity)) {
            data[iIn] = val;
            iIn = Cinc(iIn);
            if (Size < Capacity) // This can happen when overwriting
                Size++;
            else
                iOut = Cinc(iOut);
            if (PeakSize < Size) PeakSize = Size;
            return true;
        }
        return false; 
    }

    bool pop(T &val) { 
        if (Size > 0) {
            Size--;
            val = data[iOut];
            iOut = Cinc(iOut);
            return true;
        }
        return false; 
    }

    size_t size() const { return Size; }; // return actual number of elements
    
    size_t capacity() const {  // Return size of allocated storage capacity
        return Capacity;
    }

    bool empty() const {
        return (Size == 0);
    }

    bool full() const {
        return (Size == Capacity);
    }

    size_t freeSize() const { return Capacity - Size; }
    //front() const;
    //back() const;
    void clear() {
        Size = 0;
        iIn = 0;
        iOut = 0;
    }
};

