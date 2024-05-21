#pragma once

#include <type_traits>
#include <utility>

// Me think, why waste time write lot code, when few code do trick.
template <typename F, typename S, bool = std::is_empty_v<F> && !std::is_final_v<F>,
          bool = std::is_empty_v<S> && !std::is_final_v<S>, bool = std::is_same_v<F, S>>
class CompressedPair;

template <typename F, typename S>
class CompressedPair<F, S, false, false, false> {
public:
    CompressedPair() {
        first_ = F();
        second_ = S();
    };
    template <typename A, typename B>
    CompressedPair(A&& first, B&& second)
        : first_(std::forward<A>(first)), second_(std::forward<B>(second)){};

    F& GetFirst() {
        return first_;
    }

    const F& GetFirst() const {
        return first_;
    };

    const S& GetSecond() const {
        return second_;
    };

    S& GetSecond() {
        return second_;
    }

private:
    F first_;
    S second_;
};

template <typename F, typename S>
class CompressedPair<F, S, false, false, true> {
public:
    CompressedPair() = default;
    template <typename A, typename B>
    CompressedPair(A&& first, B&& second)
        : first_(std::forward<A>(first)), second_(std::forward<B>(second)){};

    F& GetFirst() {
        return first_;
    }

    const F& GetFirst() const {
        return first_;
    };

    const S& GetSecond() const {
        return second_;
    };

    S& GetSecond() {
        return second_;
    }

private:
    F first_;
    S second_;
};

template <typename F, typename S>
class CompressedPair<F, S, false, true, false> : public S {
    F first_;

public:
    CompressedPair() {
        first_ = F();
        S();
    };
    template <typename A, typename B>
    CompressedPair(A&& first, B&& second) : first_(std::forward<A>(first)), S(){};

    F& GetFirst() {
        return first_;
    }

    const F& GetFirst() const {
        return first_;
    };

    const S& GetSecond() const {
        return *this;
    };

    S& GetSecond() {
        return *this;
    }
};

template <typename F, typename S>
class CompressedPair<F, S, true, false, false> : public F {
    S second_;

public:
    CompressedPair() {
        F();
        second_ = S();
    };
    template <typename A, typename B>
    CompressedPair(A&& first, B&& second) : F(), second_(std::forward<B>(second)){};

    F& GetFirst() {
        return *this;
    }

    const F& GetFirst() const {
        return *this;
    };

    const S& GetSecond() const {
        return second_;
    };

    S& GetSecond() {
        return second_;
    }
};

template <typename F, typename S>
class CompressedPair<F, S, true, true, false> : public F, public S {
public:
    CompressedPair() {
        F();
        S();
    };

    template <typename A, typename B>
    CompressedPair(A&& first, B&& second) : F(), S(){};

    F& GetFirst() {
        return *this;
    }

    const F& GetFirst() const {
        return *this;
    };

    const S& GetSecond() const {
        return *this;
    };

    S& GetSecond() {
        return *this;
    }
};

template <typename F, typename S>
class CompressedPair<F, S, true, true, true> : public F {
    F first_;

public:
    CompressedPair() {
        first_();
        S();
    };

    template <typename A, typename B>
    CompressedPair(A&& first, B&& second) : first_(std::forward<A>(first)), S(){};

    F& GetFirst() {
        return first_;
    }

    const F& GetFirst() const {
        return first_;
    };

    const S& GetSecond() const {
        return *this;
    };

    S& GetSecond() {
        return *this;
    }
};