#ifndef VECTOR_H
#define VECTOR_H

#include <memory>         // Include for std::allocator
#include <iterator>       // Include for std::reverse_iterator and std::iterator_traits
#include <initializer_list> // Include for std::initializer_list
#include <ranges>         // Include for std::ranges

using namespace std;

namespace my_std {
  template<class T, class Allocator = std::allocator<T>>
  class vector {
      private:
        // private members
        T* array;          // Pointer to the dynamic array
        size_t size_;      // Current number of elements in the vector
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
        using size_type              = /* implementation-defined */;
        using difference_type        = /* implementation-defined */;
        using iterator               = /* implementation-defined */;
        using const_iterator         = /* implementation-defined */;
        using reverse_iterator       = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        // construct/copy/destroy
        constexpr vector() noexcept(noexcept(Allocator())) : vector(Allocator()) { }
        constexpr explicit vector(const Allocator&) noexcept;
        constexpr explicit vector(size_type n, const Allocator& = Allocator());
        constexpr vector(size_type n, const T& value, const Allocator& = Allocator());
        template<class InputIt>
        constexpr vector(InputIt first, InputIt last, const Allocator& = Allocator());
        template<std::ranges::input_range R>
        constexpr vector(std::ranges::from_range_t, R&& rg, const Allocator& = Allocator());
        constexpr vector(const vector& x);
        constexpr vector(vector&&) noexcept;
        constexpr vector(const vector&, const std::type_identity_t<Allocator>&);
        constexpr vector(vector&&, const std::type_identity_t<Allocator>&);
        constexpr vector(std::initializer_list<T>, const Allocator& = Allocator());
        constexpr ~vector();
        constexpr vector& operator=(const vector& x);
        constexpr vector& operator=(vector&& x)
            noexcept(
                std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value ||
                std::allocator_traits<Allocator>::is_always_equal::value
            );
        constexpr vector& operator=(std::initializer_list<T>);
        template<class InputIt>
        constexpr void assign(InputIt first, InputIt last);
        template<std::ranges::input_range R>
        constexpr void assign_range(R&& rg);
        constexpr void assign(size_type n, const T& u);
        constexpr void assign(std::initializer_list<T>);
        constexpr allocator_type get_allocator() const noexcept;

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
        constexpr void     swap(vector&)
            noexcept(std::allocator_traits<Allocator>::propagate_on_container_swap::value ||
                std::allocator_traits<Allocator>::is_always_equal::value);
        constexpr void     clear() noexcept;
  };

  template<class InputIt, class Allocator = std::allocator<typename std::iterator_traits<InputIt>::value_type>>
  vector(InputIt, InputIt, Allocator = Allocator())
      -> vector<typename std::iterator_traits<InputIt>::value_type, Allocator>;

  template<std::ranges::input_range R, class Allocator = std::allocator<std::ranges::range_value_t<R>>>
  vector(std::ranges::from_range_t, R&&, Allocator = Allocator())
      -> vector<std::ranges::range_value_t<R>, Allocator>;
}

#endif
