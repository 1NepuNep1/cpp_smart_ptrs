#pragma once

#include "sw_fwd.h"  // Forward declaration

// https://en.cppreference.com/w/cpp/memory/weak_ptr
template <typename T>
class WeakPtr {
    T* ptr_ = nullptr;
    ControlBlock* block_ = nullptr;

    template <typename Z>
    friend class SharedPtr;

    template <typename Z>
    friend class WeakPtr;

    template <typename Z>
    friend class EnableSharedFromThis;

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors

    WeakPtr() = default;

    template <typename Z>
    WeakPtr(const WeakPtr<Z>& other) : ptr_(other.ptr_), block_(other.block_) {
        if (block_ != nullptr) {
            block_->PlusWeakCounter();
        }
    };

    WeakPtr(const WeakPtr& other) : ptr_(other.ptr_), block_(other.block_) {
        if (block_ != nullptr) {
            block_->PlusWeakCounter();
        }
    };
    template <typename Z>
    WeakPtr(WeakPtr<Z>&& other) : ptr_(other.ptr_), block_(other.block_) {
        other.ptr_ = nullptr;
        other.block_ = nullptr;
    };

    WeakPtr(WeakPtr&& other) : ptr_(other.ptr_), block_(other.block_) {
        other.ptr_ = nullptr;
        other.block_ = nullptr;
    };

    // Demote `SharedPtr`
    // #2 from https://en.cppreference.com/w/cpp/memory/weak_ptr/weak_ptr
    WeakPtr(const SharedPtr<T>& other) : ptr_(other.Get()), block_(other.GetBlock()) {
        if (block_ != nullptr) {
            block_->PlusWeakCounter();
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // `operator=`-s
    template <typename Z>
    WeakPtr& operator=(const WeakPtr<Z>& other) {
        if (this->ptr_ != other.ptr_) {
            Reset();
            ptr_ = other.ptr_;
            block_ = other.block_;

            if (block_ != nullptr) {
                block_->PlusWeakCounter();
            }
        }
        return *this;
    };
    template <typename Z>
    WeakPtr& operator=(WeakPtr<Z>&& other) {
        if (this->ptr_ != other.ptr_) {
            Reset();
            ptr_ = other.ptr_;
            block_ = other.block_;
            other.ptr_ = nullptr;
            other.block_ = nullptr;
        }
        return *this;
    };
    WeakPtr& operator=(WeakPtr&& other) {
        if (this->ptr_ != other.ptr_) {
            Reset();
            ptr_ = other.ptr_;
            block_ = other.block_;
            other.ptr_ = nullptr;
            other.block_ = nullptr;
        }
        return *this;
    };

    template <typename Z>
    WeakPtr& operator=(WeakPtr<Z>& other) {
        if (this->ptr_ != other.ptr_) {
            Reset();
            ptr_ = other.ptr_;
            block_ = other.block_;

            if (block_ != nullptr) {
                block_->PlusWeakCounter();
            }
        }
        return *this;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Destructor

    ~WeakPtr() {
        Reset();
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    void Reset() {
        if (block_ != nullptr) {
            block_->MinusWeakCounter();
            ptr_ = nullptr;
            block_ = nullptr;
        }
    };
    void Swap(WeakPtr& other) {
        std::swap(ptr_, other.ptr_);
        std::swap(block_, other.block_);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    size_t UseCount() const {
        if (block_ != nullptr) {
            return block_->GetCounter();
        }
        return 0;
    };
    bool Expired() const {
        return UseCount() == 0;
    };
    SharedPtr<T> Lock() const {
        if (Expired()) {
            return SharedPtr<T>();
        } else {
            return SharedPtr<T>(*this);
        }
    };
};
