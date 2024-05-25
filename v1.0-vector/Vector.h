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
        T* data_;          // Pointer to the dynamic array
        size_t size_;      // Current number of elements in the Vector
        size_t capacity_;  // Current capacity of the dynamic array
        Allocator allocator_;   // Allocator for memory management
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
        template<class T, class Allocator>
        constexpr Vector(const Allocator& alloc) noexcept
            : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {}

        template<class T, class Allocator>
        constexpr Vector(size_type n, const Allocator& alloc)
            : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {
            if (n > 0) {
                data_ = allocator_.allocate(n);
                size_ = n;
                capacity_ = n;
                for (size_type i = 0; i < n; ++i) {
                    std::allocator_traits<Allocator>::construct(allocator_, data_ + i);
                }
            }
        }

        template<class T, class Allocator>
        constexpr Vector(size_type n, const T& value, const Allocator& alloc)
            : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {
            if (n > 0) {
                data_ = allocator_.allocate(n);
                size_ = n;
                capacity_ = n;
                for (size_type i = 0; i < n; ++i) {
                    std::allocator_traits<Allocator>::construct(allocator_, data_ + i, value);
                }
            }
        }

        template<class T, class Allocator>
        template<class InputIt>
        constexpr Vector(InputIt first, InputIt last, const Allocator& alloc)
            : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {
            size_type n = std::distance(first, last);
            if (n > 0) {
                data_ = allocator_.allocate(n);
                size_ = n;
                capacity_ = n;
                std::uninitialized_copy(first, last, data_);
            }
        }

        template<class T, class Allocator>
        template<std::ranges::input_range R>
        constexpr Vector(R&& rg, const Allocator& alloc)
            : Vector(std::ranges::begin(rg), std::ranges::end(rg), alloc) {}

        template<class T, class Allocator>
        constexpr Vector(const Vector& x)
            : data_(nullptr), size_(0), capacity_(0), allocator_(std::allocator_traits<Allocator>::select_on_container_copy_construction(x.allocator_)) {
            if (x.size_ > 0) {
                data_ = allocator_.allocate(x.size_);
                size_ = x.size_;
                capacity_ = x.capacity_;
                std::uninitialized_copy(x.data_, x.data_ + x.size_, data_);
            }
        }

        template<class T, class Allocator>
        constexpr Vector(Vector&& x) noexcept
            : data_(x.data_), size_(x.size_), capacity_(x.capacity_), allocator_(std::move(x.allocator_)) {
            x.data_ = nullptr;
            x.size_ = 0;
            x.capacity_ = 0;
        }

        template<class T, class Allocator>
        constexpr Vector(const Vector& x, const std::type_identity_t<Allocator>& alloc)
            : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {
            if (x.size_ > 0) {
                data_ = allocator_.allocate(x.size_);
                size_ = x.size_;
                capacity_ = x.capacity_;
                std::uninitialized_copy(x.data_, x.data_ + x.size_, data_);
            }
        }

        template<class T, class Allocator>
        constexpr Vector(Vector&& x, const std::type_identity_t<Allocator>& alloc)
            : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {
            if (allocator_ == x.allocator_) {
                data_ = x.data_;
                size_ = x.size_;
                capacity_ = x.capacity_;
                x.data_ = nullptr;
                x.size_ = 0;
                x.capacity_ = 0;
            } else {
                if (x.size_ > 0) {
                    data_ = allocator_.allocate(x.size_);
                    size_ = x.size_;
                    capacity_ = x.capacity_;
                    std::uninitialized_move(x.data_, x.data_ + x.size_, data_);
                }
            }
        }

        template<class T, class Allocator>
        constexpr Vector(std::initializer_list<T> il, const Allocator& alloc)
            : Vector(il.begin(), il.end(), alloc) {}

        template<class T, class Allocator>
        ~Vector() {
            if (data_) {
                for (size_type i = 0; i < size_; ++i) {
                    std::allocator_traits<Allocator>::destroy(allocator_, data_ + i);
                }
                allocator_.deallocate(data_, capacity_);
            }
        }

        template<class T, class Allocator>
        constexpr Vector& operator=(const Vector& x) {
            if (this != &x) {
                if constexpr (std::allocator_traits<Allocator>::propagate_on_container_copy_assignment::value) {
                    if (allocator_ != x.allocator_) {
                        clear();
                        allocator_ = x.allocator_;
                    }
                }
                if (x.size_ > capacity_) {
                    Vector temp(x);
                    swap(temp);
                } else {
                    if (size_ > x.size_) {
                        std::destroy(data_ + x.size_, data_ + size_);
                    } else if (size_ < x.size_) {
                        std::uninitialized_copy(x.data_ + size_, x.data_ + x.size_, data_ + size_);
                    }
                    std::copy(x.data_, x.data_ + std::min(size_, x.size_), data_);
                    size_ = x.size_;
                }
            }
            return *this;
        }

        template<class T, class Allocator>
        constexpr Vector& operator=(Vector&& x)
            noexcept(
                std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value ||
                std::allocator_traits<Allocator>::is_always_equal::value) {
            if (this != &x) {
                clear();
                allocator_ = std::move(x.allocator_);
                data_ = x.data_;
                size_ = x.size_;
                capacity_ = x.capacity_;
                x.data_ = nullptr;
                x.size_ = 0;
                x.capacity_ = 0;
            }
            return *this;
        }

        template<class T, class Allocator>
            constexpr Vector& operator=(std::initializer_list<T> il) {
                assign(il);
                return *this;
            }

            // Assign elements from the range specified by iterators [first, last)
            template<class T, class Allocator>
            template<class InputIt>
            constexpr void assign(InputIt first, InputIt last) {
                clear();
                insert(end(), first, last);
            }

            //Assign elements from the input range specified by rg
            template<class T, class Allocator>
            template<std::ranges::input_range R>
            constexpr void assign_range(R&& rg) {
                clear();
                insert(end(), std::ranges::begin(rg), std::ranges::end(rg));
            }


            // Assign n copies of u to the vector
            template<class T, class Allocator>
            constexpr void assign(size_type n, const T& u) {
                clear();
                insert(end(), n, u);
            }

            // Assign elements from the initializer list il
            template<class T, class Allocator>
            constexpr void assign(std::initializer_list<T> il) {
                clear();
                insert(end(), il);
            }

            // Get allocator
            template<class T, class Allocator>
            constexpr allocator_type get_allocator() noexcept {
                return allocator_;
            }

            //Iterators
            template<class T, class Allocator>
            constexpr iterator begin() noexcept {
                return data_;
            }

            template<class T, class Allocator>
            constexpr const_iterator begin() const noexcept {
                return data_;
            }

            template<class T, class Allocator>
            constexpr iterator end() noexcept {
                return data_ + size_;
            }

            template<class T, class Allocator>
            constexpr const_iterator end() const noexcept {
                return data_ + size_;
            }

            template<class T, class Allocator>
            constexpr reverse_iterator rbegin() noexcept {
                return reverse_iterator(end());
            }

            template<class T, class Allocator>
            constexpr const_reverse_iterator rbegin() const noexcept {
                return const_reverse_iterator(end());
            }

            template<class T, class Allocator>
            constexpr reverse_iterator rend() noexcept {
                return reverse_iterator(begin());
            }

            template<class T, class Allocator>
            constexpr const_reverse_iterator rend() const noexcept {
                return const_reverse_iterator(begin());
            }

            template<class T, class Allocator>
            constexpr const_iterator cbegin() const noexcept {
                return begin();
            }

            template<class T, class Allocator>
            constexpr const_iterator cend() const noexcept {
                return end();
            }

            template<class T, class Allocator>
            constexpr const_reverse_iterator crbegin() const noexcept {
                return rbegin();
            }

            template<class T, class Allocator>
            constexpr const_reverse_iterator crend() const noexcept {
                return rend();
            }
            //capacity
            template<class T, class Allocator>
            constexpr bool empty() const noexcept {
                return size_ == 0;
            }

            template<class T, class Allocator>
            constexpr size_type size() const noexcept {
                return size_;
            }

            template<class T, class Allocator>
            constexpr size_type max_size() const noexcept {
                return std::allocator_traits<Allocator>::max_size(allocator_);
            }

            template<class T, class Allocator>
            constexpr size_type capacity() const noexcept {
                return capacity_;
            }

            template<class T, class Allocator>
            constexpr void resize(size_type sz) {
                if (sz > capacity_) {
                    reserve(sz);
                }
                if (sz > size_) {
                    std::uninitialized_value_construct(data_ + size_, data_ + sz);
                } else {
                    std::destroy(data_ + sz, data_ + size_);
                }
                size_ = sz;
            }

            template<class T, class Allocator>
            constexpr void resize(size_type sz, const T& c) {
                if (sz > capacity_) {
                    reserve(sz);
                }
                if (sz > size_) {
                    std::uninitialized_fill(data_ + size_, data_ + sz, c);
                } else {
                    std::destroy(data_ + sz, data_ + size_);
                }
                size_ = sz;
            }

            template<class T, class Allocator>
            constexpr void reserve(size_type n) {
                if (n > capacity_) {
                    T* new_data = allocator_.allocate(n);
                    std::uninitialized_move(data_, data_ + size_, new_data);
                    std::destroy(data_, data_ + size_);
                    allocator_.deallocate(data_, capacity_);
                    data_ = new_data;
                    capacity_ = n;
                }
            }

            template<class T, class Allocator>
            constexpr void shrink_to_fit() {
                if (size_ < capacity_) {
                    T* new_data = allocator_.allocate(size_);
                    std::uninitialized_move(data_, data_ + size_, new_data);
                    std::destroy(data_, data_ + size_);
                    allocator_.deallocate(data_, capacity_);
                    data_ = new_data;
                    capacity_ = size_;
                }
            }
            // element access
            template<class T, class Allocator>
            constexpr reference operator[](size_type n) {
                return data_[n];
            }

            template<class T, class Allocator>
            constexpr const_reference operator[](size_type n) const {
                return data_[n];
            }

            template<class T, class Allocator>
            constexpr const_reference at(size_type n) const {
                if (n >= size_) {
                    throw std::out_of_range("Vector::at");
                }
                return data_[n];
            }

            template<class T, class Allocator>
            constexpr reference at(size_type n) {
                if (n >= size_) {
                    throw std::out_of_range("Vector::at");
                }
                return data_[n];
            }

            template<class T, class Allocator>
            constexpr reference front() {
                return data_[0];
            }

            template<class T, class Allocator>
            constexpr const_reference front() const {
                return data_[0];
            }

            template<class T, class Allocator>
            constexpr reference back() {
                return data_[size_ - 1];
            }

            template<class T, class Allocator>
            constexpr const_reference back() const {
                return data_[size_ - 1];
            }

            // data access
            template<class T, class Allocator>
            constexpr T* data() noexcept {
                return data_;
            }

            template<class T, class Allocator>
            constexpr const T* data() const noexcept {
                return data_;
            }
            // modifiers
            template<class T, class Allocator>
            template<class... Args>
            constexpr reference emplace_back(Args&&... args) {
                if (size_ == capacity_) {
                    reserve(capacity_ == 0 ? 1 : 2 * capacity_);
                }
                allocator_.construct(data_ + size_, std::forward<Args>(args)...);
                ++size_;
                return back();
            }

            template<class T, class Allocator>
            constexpr void push_back(const T& x) {
                emplace_back(x);
            }

            template<class T, class Allocator>
            constexpr void push_back(T&& x) {
                emplace_back(std::move(x));
            }

            template<class T, class Allocator>
            template<std::ranges::input_range R>
            constexpr void append_range(R&& rg) {
                for (const auto& element : rg) {
                    push_back(element);
                }
            }

            template<class T, class Allocator>
            constexpr void pop_back() {
                if (size_ > 0) {
                    allocator_.destroy(data_ + (--size_));
                }
            }

            template<class T, class Allocator>
            template<class... Args>
            constexpr iterator emplace(const_iterator position, Args&&... args) {
                const auto index = position - begin();
                if (size_ == capacity_) {
                    reserve(capacity_ == 0 ? 1 : 2 * capacity_);
                }
                std::move_backward(data_ + index, data_ + size_, data_ + size_ + 1);
                allocator_.construct(data_ + index, std::forward<Args>(args)...);
                ++size_;
                return begin() + index;
            }

            template<class T, class Allocator>
            constexpr iterator insert(const_iterator position, const T& x) {
                return emplace(position, x);
            }

            template<class T, class Allocator>
            constexpr iterator insert(const_iterator position, T&& x) {
                return emplace(position, std::move(x));
            }

            template<class T, class Allocator>
            constexpr iterator insert(const_iterator position, size_type n, const T& x) {
                const auto index = position - begin();
                if (n > 0) {
                    if (size_ + n > capacity_) {
                        reserve(size_ + n);
                    }
                    std::move_backward(data_ + index, data_ + size_, data_ + size_ + n);
                    std::fill_n(data_ + index, n, x);
                    size_ += n;
                }
                return begin() + index;
            }

            template<class T, class Allocator>
            template<class InputIt>
            constexpr iterator insert(const_iterator position, InputIt first, InputIt last) {
                const auto index = position - begin();
                const size_type n = std::distance(first, last);
                if (n > 0) {
                    if (size_ + n > capacity_) {
                        reserve(size_ + n);
                    }
                    std::move_backward(data_ + index, data_ + size_, data_ + size_ + n);
                    std::copy(first, last, data_ + index);
                    size_ += n;
                }
                return begin() + index;
            }

            template<class T, class Allocator>
            template<std::ranges::input_range R>
            constexpr iterator insert_range(const_iterator position, R&& rg) {
                return insert(position, std::ranges::begin(rg), std::ranges::end(rg));
            }

            template<class T, class Allocator>
            constexpr iterator insert(const_iterator position, std::initializer_list<T> il) {
                return insert(position, il.begin(), il.end());
            }

            template<class T, class Allocator>
            constexpr iterator erase(const_iterator position) {
                const auto index = position - begin();
                if (position != end()) {
                    std::move(data_ + index + 1, data_ + size_, data_ + index);
                    allocator_.destroy(data_ + (--size_));
                }
                return begin() + index;
            }

            template<class T, class Allocator>
            constexpr iterator erase(const_iterator first, const_iterator last) {
                const auto index = first - begin();
                const auto count = last - first;
                if (count > 0) {
                    std::move(data_ + index + count, data_ + size_, data_ + index);
                    std::destroy(data_ + size_ - count, data_ + size_);
                    size_ -= count;
                }
                return begin() + index;
            }

            template<class T, class Allocator>
            constexpr void swap(Vector& other) noexcept(
                std::allocator_traits<Allocator>::propagate_on_container_swap::value ||
                std::allocator_traits<Allocator>::is_always_equal::value) {
                using std::swap;
                swap(data_, other.data_);
                swap(size_, other.size_);
                swap(capacity_, other.capacity_);
                swap(allocator_, other.allocator_);
            }

            template<class T, class Allocator>
            constexpr void clear() noexcept {
                while (!empty()) {
                    pop_back();
                }
            }
  };

//   template<class InputIt, class Allocator = std::allocator<typename std::iterator_traits<InputIt>::value_type>>
//   Vector(InputIt, InputIt, Allocator = Allocator())
//       -> Vector<typename std::iterator_traits<InputIt>::value_type, Allocator>;

//   template<std::ranges::input_range R, class Allocator = std::allocator<std::ranges::range_value_t<R>>>
//   Vector(std::ranges::from_range_t, R&&, Allocator = Allocator())
//       -> Vector<std::ranges::range_value_t<R>, Allocator>;
}

#endif
