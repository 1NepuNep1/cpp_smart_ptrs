#pragma once

#include "sw_fwd.h"  // Forward declaration
#include <cstddef>   // std::nullptr_t

// https://en.cppreference.com/w/cpp/memory/shared_ptr

// Look for usage examples in tests
class EnableSharedFromThisBase {};

template <typename T>
class EnableSharedFromThis : public EnableSharedFromThisBase {
    template <typename Z>
    friend class WearPtr;

    template <typename Z>
    friend class SharedPtr;

    WeakPtr<T> weak_this_;

public:
    EnableSharedFromThis() = default;
    SharedPtr<T> SharedFromThis() {
        return weak_this_.Lock();
    };
    SharedPtr<const T> SharedFromThis() const {
        return weak_this_.Lock();
    };

    WeakPtr<T> WeakFromThis() noexcept {
        return weak_this_;
    };
    WeakPtr<const T> WeakFromThis() const noexcept {
        return weak_this_;
    };
};

template <typename T>
class SharedPtr {
    T* ptr_ = nullptr;
    ControlBlock* block_ = nullptr;

    template <typename K, typename... Args>
    friend SharedPtr<K> MakeShared(Args&&... args);

    template <typename Z>
    friend class SharedPtr;

    template <typename Z>
    friend class WeakPtr;

    template <typename Z>
    friend class EnableSharedFromThis;

    void SharedFromThisIfNeeded(T* ptr) {
        if (ptr_ && block_) {
            if constexpr (std::is_convertible_v<T*, EnableSharedFromThisBase*>) {
                InitWeakThis(ptr);
            }
        }
    }

    template <typename Y>
    void InitWeakThis(EnableSharedFromThis<Y>* e) {
        e->weak_this_ = WeakPtr<Y>(*this);
    }

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors

    SharedPtr() = default;
    SharedPtr(std::nullptr_t) : ptr_(nullptr), block_(nullptr){};
    template <typename Z>
    explicit SharedPtr(Z* ptr) : ptr_(ptr), block_(new ControlBlockPointer<Z>(ptr)) {
        SharedFromThisIfNeeded(ptr);
    };

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), block_(other.block_) {
        if (block_ != nullptr) {
            block_->PlusCounter();
        }
    };
    template <typename Z>
    SharedPtr(const SharedPtr<Z>& other) : ptr_(other.ptr_), block_(other.block_) {
        if (block_ != nullptr) {
            block_->PlusCounter();
        }
    };
    template <typename Z>
    SharedPtr(SharedPtr<Z>&& other) : ptr_(other.ptr_), block_(other.block_) {
        other.ptr_ = nullptr;
        other.block_ = nullptr;
    };
    SharedPtr(SharedPtr&& other) : ptr_(other.ptr_), block_(other.block_) {
        other.ptr_ = nullptr;
        other.block_ = nullptr;
    }
    template <typename Z>
    SharedPtr(ControlBlock* block, Z* ptr) : ptr_(ptr), block_(block) {
        SharedFromThisIfNeeded(ptr);
    }

    // Aliasing constructor
    // #8 from https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr
    template <typename Z>
    SharedPtr(const SharedPtr<Z>& other, T* ptr) : ptr_(ptr), block_(other.block_) {
        if (block_ != nullptr) {
            block_->PlusCounter();
        }
    }

    // Promote WeakPtr
    // #11 from https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr
    explicit SharedPtr(const WeakPtr<T>& other) {
        if (other.block_ != nullptr && other.UseCount() != 0) {
            ptr_ = other.ptr_;
            block_ = other.block_;
            block_->PlusCounter();
        } else {
            throw BadWeakPtr();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // operator=-s

    template <typename Z>
    SharedPtr& operator=(const SharedPtr<Z>& other) {
        if (this->Get() != other.Get()) {
            Reset();
            ptr_ = other.ptr_;
            block_ = other.block_;

            if (block_ != nullptr) {
                block_->PlusCounter();
            }
        }
        return *this;
    }

    template <typename Z>
    SharedPtr& operator=(SharedPtr<Z>&& other) {
        if (this->Get() != other.Get()) {
            Reset();
            ptr_ = other.ptr_;
            block_ = other.block_;

            other.ptr_ = nullptr;
            other.block_ = nullptr;
        }
        return *this;
    }

    template <typename Z>
    SharedPtr& operator=(SharedPtr<Z>& other) {
        if (this->Get() != other.Get()) {
            Reset();
            ptr_ = other.ptr_;
            block_ = other.block_;

            if (block_ != nullptr) {
                block_->PlusCounter();
            }
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Destructor

    ~SharedPtr() {
        Reset();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    void Reset() {
        if (block_ != nullptr) {
            block_->MinusCounter();
            ptr_ = nullptr;
            block_ = nullptr;
        }
    }
    template <typename Z>
    void Reset(Z* ptr) {
        SharedPtr(ptr).Swap(*this);
    }
    void Swap(SharedPtr& other) {
        std::swap(ptr_, other.ptr_);
        std::swap(block_, other.block_);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    ControlBlock* GetBlock() const {
        return block_;
    }

    T* Get() const {
        return ptr_;
    }
    T& operator*() const {
        return *ptr_;
    }
    T* operator->() const {
        return ptr_;
    }
    size_t UseCount() const {
        if (block_ != nullptr) {
            return block_->GetCounter();
        }
        return 0;
    }
    explicit operator bool() const {
        return ptr_ != nullptr;
    }
};

template <typename T, typename U>
inline bool operator==(const SharedPtr<T>& left, const SharedPtr<U>& right) {
    return left.Get() == right.Get();
}

// Allocate memory only once
template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args) {
    auto block = new ControlBlockAllocator<T>(std::forward<Args>(args)...);
    return SharedPtr<T>(block, block->GetPtr());
}