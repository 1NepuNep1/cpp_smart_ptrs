#pragma once

#include "compressed_pair.h"

#include <cstddef>  // std::nullptr_t

template <typename T>
struct DefaultDeleter {
    DefaultDeleter() = default;
    template <typename K>
    DefaultDeleter(const DefaultDeleter<K>&){};
    void operator()(T* ptr) const {
        delete ptr;
    }
};
template <>
struct DefaultDeleter<void> {
    void operator()(void* ptr) {
        delete reinterpret_cast<char*>(ptr);
    }
};

template <typename T>
struct DefaultDeleter<T[]> {
    void operator()(T* ptr) const {
        delete[] ptr;
    }
};

// Primary template
template <typename T, typename Deleter = DefaultDeleter<T>>
class UniquePtr {
    CompressedPair<T*, Deleter> data_;

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors

    explicit UniquePtr(T* ptr = nullptr) noexcept : data_(ptr, Deleter{}){};
    UniquePtr(T* ptr, Deleter deleter) noexcept : data_(ptr, std::forward<Deleter>(deleter)){};

    template <class K, class DD>
    UniquePtr(UniquePtr<K, DD>&& other) noexcept {
        data_.GetFirst() = other.Release();
        data_.GetSecond() = std::forward<DD>(other.GetDeleter());
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // `operator=`-s

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            Reset(other.Release());
            data_.GetSecond() = std::forward<Deleter>(other.data_.GetSecond());
        }
        return *this;
    };
    UniquePtr& operator=(std::nullptr_t) noexcept {
        Reset();
        return *this;
    };
    template <class K, class DD>
    UniquePtr& operator=(UniquePtr<K, DD>&& other) noexcept {
        if (data_.GetFirst() != other.Get()) {
            Reset(other.Release());
            data_.GetSecond() = std::forward<DD>(other.GetDeleter());
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Destructor

    ~UniquePtr() {
        if (data_.GetFirst()) {
            data_.GetSecond()(data_.GetFirst());
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    T* Release() noexcept {
        T* ptr = data_.GetFirst();
        data_.GetFirst() = nullptr;
        return ptr;
    };
    void Reset(T* ptr = nullptr) {
        auto obj = data_.GetFirst();
        data_.GetFirst() = ptr;
        if (obj != nullptr) {
            data_.GetSecond()(obj);
        }
    };
    void Swap(UniquePtr& other) noexcept {
        std::swap(data_, other.data_);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    T* Get() const noexcept {
        return data_.GetFirst();
    };
    Deleter& GetDeleter() noexcept {
        return data_.GetSecond();
    };
    const Deleter& GetDeleter() const noexcept {
        return data_.GetSecond();
    };
    explicit operator bool() const noexcept {
        return data_.GetFirst() != nullptr;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Single-object dereference operators

    T operator*() const noexcept {
        return *data_.GetFirst();
    };
    T* operator->() const noexcept {
        return data_.GetFirst();
    };
};

// Specialization for arrays
template <typename T, typename Deleter>
class UniquePtr<T[], Deleter> {
    CompressedPair<T*, Deleter> data_;

public:
    explicit UniquePtr(T* ptr = nullptr) noexcept : data_(ptr, Deleter{}){};
    UniquePtr(T* ptr, Deleter deleter) noexcept : data_(ptr, std::forward<Deleter>(deleter)){};

    UniquePtr(UniquePtr&& other) noexcept {
        data_.GetFirst() = other.data_.GetFirst();
        data_.GetSecond() = std::forward<Deleter>(other.data_.GetSecond());
        other.data_.GetFirst() = nullptr;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // `operator=`-s

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            Reset(other.Release());
            data_.GetSecond() = std::forward<Deleter>(other.data_.GetSecond());
        }
        return *this;
    };
    UniquePtr& operator=(std::nullptr_t) noexcept {
        Reset();
        return *this;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Destructor

    ~UniquePtr() {
        if (data_.GetFirst()) {
            data_.GetSecond()(data_.GetFirst());
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    T* Release() noexcept {
        T* ptr = data_.GetFirst();
        data_.GetFirst() = nullptr;
        return ptr;
    };
    void Reset(T* ptr = nullptr) {
        auto obj = data_.GetFirst();
        data_.GetFirst() = ptr;
        if (obj != nullptr) {
            data_.GetSecond()(obj);
        }
    };
    void Swap(UniquePtr& other) noexcept {
        std::swap(data_, other.data_);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    T* Get() const noexcept {
        return data_.GetFirst();
    };
    Deleter& GetDeleter() noexcept {
        return data_.GetSecond();
    };
    const Deleter& GetDeleter() const noexcept {
        return data_.GetSecond();
    };
    explicit operator bool() const noexcept {
        return data_.GetFirst() != nullptr;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////

    T operator*() const noexcept {
        return *data_.GetFirst();
    };
    T* operator->() const noexcept {
        return data_.GetFirst();
    };

    T& operator[](size_t index) const noexcept {
        return data_.GetFirst()[index];
    };
};
