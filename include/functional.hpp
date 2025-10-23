#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

#define EQ(T) equal_to<T>()
#define LT(T) less<T>()
#define GT(T) greater<T>()
#define LE(T) less_equal<T>()
#define GE(T) greater_equal<T>()

namespace ft {

template <class Arg0, class Arg1, class Result>
struct binary_function {
    typedef Arg0   first_argument_type;
    typedef Arg1   second_argument_type;
    typedef Result result_type;
};

template <typename T>
struct equal_to : binary_function<T, T, bool> {
    bool operator()(
        T const &a, T const &b
    ) const
    {
        return a == b;
    }
};

template <typename T>
struct greater : binary_function<T, T, bool> {
    bool operator()(
        T const &a, T const &b
    ) const
    {
        return a > b;
    }
};

template <typename T>
struct less : binary_function<T, T, bool> {
    bool operator()(
        T const &a, T const &b
    ) const
    {
        return a < b;
    }
};

template <typename T>
struct greater_equal : binary_function<T, T, bool> {
    bool operator()(
        T const &a, T const &b
    ) const
    {
        return a >= b;
    }
};

template <typename T>
struct less_equal : binary_function<T, T, bool> {
    bool operator()(
        T const &a, T const &b
    ) const
    {
        return a <= b;
    }
};

} // namespace ft

#endif
