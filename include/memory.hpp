#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <memory> // std::allocator

namespace ft {

template <typename T>
class allocator : public std::allocator<T>
{};

} // namespace ft

#endif
