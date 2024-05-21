#pragma once

#include <exception>
#include <cstddef>
#include <stdexcept>

struct ControlBlock {
    size_t counter = 1;
    size_t weak_counter = 0;
    virtual ~ControlBlock() = default;
    virtual void DeleteFromCounter() = 0;
    virtual void DeleteFromWeakCounter() = 0;

    void PlusCounter() {
        ++counter;
    }
    void PlusWeakCounter() {
        ++weak_counter;
    }
    void MinusCounter() {
        if (counter == 1) {
            DeleteFromCounter();
        }
        --counter;
        if (counter == 0 && weak_counter == 0) {
            DeleteFromWeakCounter();
        }
    }
    size_t GetCounter() {
        return counter;
    }
    void MinusWeakCounter() {
        --weak_counter;
        if (counter + weak_counter == 0) {
            DeleteFromWeakCounter();
        }
    }
};

template <typename T>
struct ControlBlockPointer : ControlBlock {
    T* ptr;
    ~ControlBlockPointer() override = default;

    ControlBlockPointer(T* p) : ptr(p){};

    void DeleteFromCounter() override {
        auto obj = ptr;
        ptr = nullptr;
        delete obj;
    }
    void DeleteFromWeakCounter() override {
        delete this;
    }
};
template <typename T>
struct ControlBlockAllocator : ControlBlock {
    ~ControlBlockAllocator() override = default;
    alignas(T) std::byte block[sizeof(T)];
    template <typename... Args>
    ControlBlockAllocator(Args&&... args) {
        new (&block) T(std::forward<Args>(args)...);
    }
    T* GetPtr() {
        return reinterpret_cast<T*>(&block);
    }
    void DeleteFromCounter() override {
        GetPtr()->~T();
    }
    void DeleteFromWeakCounter() override {
        delete this;
    }
};

class BadWeakPtr : public std::exception {};

template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr;
