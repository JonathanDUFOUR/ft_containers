#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include "type/fundamentals.hpp" // ft::t_{{i,u}{8,16,32,64},bool,char,double,float,long_double,wchar}

namespace ft {
template <typename T, T value>
struct integral_constant {
    operator T() const { return value; }
};

// clang-format off

typedef integral_constant<t_bool, false> t_false;
typedef integral_constant<t_bool, true > t_true;

template <t_bool, typename T = void> struct enable_if;
template <        typename T       > struct enable_if<true, T> {typedef T type;};

template <typename T> struct is_integral          : t_false{};
template <          > struct is_integral<t_i8>    : t_true {};
template <          > struct is_integral<t_i16>   : t_true {};
template <          > struct is_integral<t_i32>   : t_true {};
template <          > struct is_integral<t_i64>   : t_true {};
template <          > struct is_integral<t_u8>    : t_true {};
template <          > struct is_integral<t_u16>   : t_true {};
template <          > struct is_integral<t_u32>   : t_true {};
template <          > struct is_integral<t_u64>   : t_true {};
template <          > struct is_integral<t_bool>  : t_true {};
template <          > struct is_integral<t_char>  : t_true {};
template <          > struct is_integral<t_wchar> : t_true {};

template <typename T0, typename T1> struct is_same       : t_false{};
template <typename T>               struct is_same<T, T> : t_true {};

template <typename T> struct is_trivially_copyable                : t_false{};
template <          > struct is_trivially_copyable<t_bool>        : t_true {};
template <          > struct is_trivially_copyable<t_char>        : t_true {};
template <          > struct is_trivially_copyable<t_wchar>       : t_true {};
template <          > struct is_trivially_copyable<t_i8>          : t_true {};
template <          > struct is_trivially_copyable<t_i16>         : t_true {};
template <          > struct is_trivially_copyable<t_i32>         : t_true {};
template <          > struct is_trivially_copyable<t_i64>         : t_true {};
template <          > struct is_trivially_copyable<t_u8>          : t_true {};
template <          > struct is_trivially_copyable<t_u16>         : t_true {};
template <          > struct is_trivially_copyable<t_u32>         : t_true {};
template <          > struct is_trivially_copyable<t_u64>         : t_true {};
template <          > struct is_trivially_copyable<t_float>       : t_true {};
template <          > struct is_trivially_copyable<t_double>      : t_true {};
template <          > struct is_trivially_copyable<t_long_double> : t_true {};

template <typename T> struct make_unsigned;
template <          > struct make_unsigned<t_i8> {typedef t_u8  type;};
template <          > struct make_unsigned<t_i16>{typedef t_u16 type;};
template <          > struct make_unsigned<t_i32>{typedef t_u32 type;};
template <          > struct make_unsigned<t_i64>{typedef t_u64 type;};
template <          > struct make_unsigned<t_u8> {typedef t_u8  type;};
template <          > struct make_unsigned<t_u16>{typedef t_u16 type;};
template <          > struct make_unsigned<t_u32>{typedef t_u32 type;};
template <          > struct make_unsigned<t_u64>{typedef t_u64 type;};

// clang-format on
} // namespace ft

#endif
