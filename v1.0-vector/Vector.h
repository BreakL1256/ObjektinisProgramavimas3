#ifndef Vector_H
#define Vector_H

#include <memory>         // Include for std::allocator
#include <iterator>       // Include for std::reverse_iterator and std::iterator_traits
#include <initializer_list> // Include for std::initializer_list
#include <ranges>         // Include for std::ranges

using namespace std;

namespace my_std {
  template<class T, class Allocator = std::allocator<T>>
  class Vector {
      private:
        // private members
        T* array;          // Pointer to the dynamic array
        size_t size_;      // Current number of elements in the Vector
        size_t capacity_;  // Current capacity of the dynamic array
        Allocator alloc;   // Allocator for memory management
      public:
        // types
        using value_type             = T;
        using allocator_type         = Allocator;
        using pointer                = typename std::allocator_traits<Allocator>::pointer;
        using const_pointer          = typename std::allocator_traits<Allocator>::const_pointer;
        using reference              = value_type&;
        using const_reference        = const value_type&;
        using size_type              = std::size_t;
        using difference_type        = std::ptrdiff_t;
        using iterator               = T*;
        using const_iterator         = const T*;
        using reverse_iterator       = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;


        // construct/copy/destroy
        constexpr Vector() noexcept(noexcept(Allocator())) : Vector(Allocator()) { }
        constexpr explicit Vector(const Allocator&) noexcept;
        constexpr explicit Vector(size_type n, const Allocator& = Allocator());
        constexpr Vector(size_type n, const T& value, const Allocator& = Allocator());
        template<class InputIt>
        constexpr Vector(InputIt first, InputIt last, const Allocator& = Allocator());
        template<std::ranges::input_range R>
        constexpr Vector(R&& rg, const Allocator& = Allocator());
        constexpr Vector(const Vector& x);
        constexpr Vector(Vector&&) noexcept;
        constexpr Vector(const Vector&, const std::type_identity_t<Allocator>&);
        constexpr Vector(Vector&&, const std::type_identity_t<Allocator>&);
        constexpr Vector(std::initializer_list<T>, const Allocator& = Allocator());
        constexpr ~Vector();
        constexpr Vector& operator=(const Vector& x);
        constexpr Vector& operator=(Vector&& x)
            noexcept(
                std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value ||
                std::allocator_traits<Allocator>::is_always_equal::value
            );
        constexpr Vector& operator=(std::initializer_list<T>);
        template<class InputIt>
        constexpr void assign(InputIt first, InputIt last);
        template<std::ranges::input_range R>
        constexpr void assign_range(R&& rg);
        constexpr void assign(size_type n, const T& u);
        constexpr void assign(std::initializer_list<T>);
        constexpr allocator_type get_allocator() noexcept;

        // iterators
        constexpr iterator               begin() noexcept;
        constexpr const_iterator         begin() const noexcept;
        constexpr iterator               end() noexcept;
        constexpr const_iterator         end() const noexcept;
        constexpr reverse_iterator       rbegin() noexcept;
        constexpr const_reverse_iterator rbegin() const noexcept;
        constexpr reverse_iterator       rend() noexcept;
        constexpr const_reverse_iterator rend() const noexcept;

        constexpr const_iterator         cbegin() const noexcept;
        constexpr const_iterator         cend() const noexcept;
        constexpr const_reverse_iterator crbegin() const noexcept;
        constexpr const_reverse_iterator crend() const noexcept;

        // capacity
        [[nodiscard]] constexpr bool empty() const noexcept;
        constexpr size_type size() const noexcept;
        constexpr size_type max_size() const noexcept;
        constexpr size_type capacity() const noexcept;
        constexpr void      resize(size_type sz);
        constexpr void      resize(size_type sz, const T& c);
        constexpr void      reserve(size_type n);
        constexpr void      shrink_to_fit();

        // element access
        constexpr reference       operator[](size_type n);
        constexpr const_reference operator[](size_type n) const;
        constexpr const_reference at(size_type n) const;
        constexpr reference       at(size_type n);
        constexpr reference       front();
        constexpr const_reference front() const;
        constexpr reference       back();
        constexpr const_reference back() const;

        // data access
        constexpr T*       data() noexcept;
        constexpr const T* data() const noexcept;

        // modifiers
        template<class... Args> constexpr reference emplace_back(Args&&... args);
        constexpr void push_back(const T& x);
        constexpr void push_back(T&& x);
        template<std::ranges::input_range R>
        constexpr void append_range(R&& rg);
        constexpr void pop_back();

        template<class... Args> constexpr iterator emplace(const_iterator position,
            Args&&... args);
        constexpr iterator insert(const_iterator position, const T& x);
        constexpr iterator insert(const_iterator position, T&& x);
        constexpr iterator insert(const_iterator position, size_type n, const T& x);
        template<class InputIt>
        constexpr iterator insert(const_iterator position,
            InputIt first, InputIt last);
        template<std::ranges::input_range R>
        constexpr iterator insert_range(const_iterator position, R&& rg);
        constexpr iterator insert(const_iterator position, std::initializer_list<T> il);
        constexpr iterator erase(const_iterator position);
        constexpr iterator erase(const_iterator first, const_iterator last);
        constexpr void     swap(Vector&)
            noexcept(std::allocator_traits<Allocator>::propagate_on_container_swap::value ||
                std::allocator_traits<Allocator>::is_always_equal::value);
        constexpr void     clear() noexcept;
  };

//   template<class InputIt, class Allocator = std::allocator<typename std::iterator_traits<InputIt>::value_type>>
//   Vector(InputIt, InputIt, Allocator = Allocator())
//       -> Vector<typename std::iterator_traits<InputIt>::value_type, Allocator>;

//   template<std::ranges::input_range R, class Allocator = std::allocator<std::ranges::range_value_t<R>>>
//   Vector(std::ranges::from_range_t, R&&, Allocator = Allocator())
//       -> Vector<std::ranges::range_value_t<R>, Allocator>;
}
#include "Vector.tpp"
#endif
