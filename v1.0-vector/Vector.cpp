#include "Vector.h"

namespace my_std {

// construct/copy/destroy
template<class T, class Allocator>
constexpr Vector<T, Allocator>::Vector(const Allocator& alloc) noexcept
    : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {}

template<class T, class Allocator>
constexpr Vector<T, Allocator>::Vector(size_type n, const Allocator& alloc)
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
constexpr Vector<T, Allocator>::Vector(size_type n, const T& value, const Allocator& alloc)
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
constexpr Vector<T, Allocator>::Vector(InputIt first, InputIt last, const Allocator& alloc)
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
constexpr Vector<T, Allocator>::Vector(std::ranges::from_range_t, R&& rg, const Allocator& alloc)
    : Vector(std::ranges::begin(rg), std::ranges::end(rg), alloc) {}

template<class T, class Allocator>
constexpr Vector<T, Allocator>::Vector(const Vector& x)
    : data_(nullptr), size_(0), capacity_(0), allocator_(std::allocator_traits<Allocator>::select_on_container_copy_construction(x.allocator_)) {
    if (x.size_ > 0) {
        data_ = allocator_.allocate(x.size_);
        size_ = x.size_;
        capacity_ = x.capacity_;
        std::uninitialized_copy(x.data_, x.data_ + x.size_, data_);
    }
}

template<class T, class Allocator>
constexpr Vector<T, Allocator>::Vector(Vector&& x) noexcept
    : data_(x.data_), size_(x.size_), capacity_(x.capacity_), allocator_(std::move(x.allocator_)) {
    x.data_ = nullptr;
    x.size_ = 0;
    x.capacity_ = 0;
}

template<class T, class Allocator>
constexpr Vector<T, Allocator>::Vector(const Vector& x, const std::type_identity_t<Allocator>& alloc)
    : data_(nullptr), size_(0), capacity_(0), allocator_(alloc) {
    if (x.size_ > 0) {
        data_ = allocator_.allocate(x.size_);
        size_ = x.size_;
        capacity_ = x.capacity_;
        std::uninitialized_copy(x.data_, x.data_ + x.size_, data_);
    }
}

template<class T, class Allocator>
constexpr Vector<T, Allocator>::Vector(Vector&& x, const std::type_identity_t<Allocator>& alloc)
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
constexpr Vector<T, Allocator>::Vector(std::initializer_list<T> il, const Allocator& alloc)
    : Vector(il.begin(), il.end(), alloc) {}

template<class T, class Allocator>
constexpr Vector<T, Allocator>::~Vector() {
    if (data_) {
        for (size_type i = 0; i < size_; ++i) {
            std::allocator_traits<Allocator>::destroy(allocator_, data_ + i);
        }
        allocator_.deallocate(data_, capacity_);
    }
}

template<class T, class Allocator>
constexpr Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& x) {
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
Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& x) noexcept {
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
    constexpr Vector<T, Allocator>& Vector<T, Allocator>::operator=(std::initializer_list<T> il) {
        assign(il);
        return *this;
    }

    // Assign elements from the range specified by iterators [first, last)
    template<class T, class Allocator>
    template<class InputIt>
    constexpr void Vector<T, Allocator>::assign(InputIt first, InputIt last) {
        clear();
        insert(end(), first, last);
    }

    // Assign elements from the input range specified by rg
    template<class T, class Allocator>
    template<std::ranges::input_range R>
    void Vector<T, Allocator>::assign_range(R&& rg) {
        clear();
        insert(end(), std::ranges::begin(rg), std::ranges::end(rg));
    }

    // Assign n copies of u to the vector
    template<class T, class Allocator>
    constexpr void Vector<T, Allocator>::assign(size_type n, const T& u) {
        clear();
        insert(end(), n, u);
    }

    // Assign elements from the initializer list il
    template<class T, class Allocator>
    constexpr void Vector<T, Allocator>::assign(std::initializer_list<T> il) {
        clear();
        insert(end(), il);
    }

    // Get allocator
    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::allocator_type Vector<T, Allocator>::get_allocator() noexcept {
        return allocator_;
    }

    //Iterators
    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::iterator Vector<T, Allocator>::begin() noexcept {
        return data_;
    }

    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::begin() const noexcept {
        return data_;
    }

    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::iterator Vector<T, Allocator>::end() noexcept {
        return data_ + size_;
    }

    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::end() const noexcept {
        return data_ + size_;
    }

    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rbegin() noexcept {
        return reverse_iterator(end());
    }

    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rend() noexcept {
        return reverse_iterator(begin());
    }

    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cbegin() const noexcept {
        return begin();
    }

    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cend() const noexcept {
        return end();
    }

    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::crbegin() const noexcept {
        return rbegin();
    }

    template<class T, class Allocator>
    constexpr typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::crend() const noexcept {
        return rend();
    }
    //capacity
    template<class T, class Allocator>
    [[nodiscard]] constexpr bool Vector<T, Allocator>::empty() const noexcept {
        return size_ == 0;
    }

    template<class T, class Allocator>
    [[nodiscard]] constexpr typename Vector<T, Allocator>::size_type Vector<T, Allocator>::size() const noexcept {
        return size_;
    }

    template<class T, class Allocator>
    [[nodiscard]] constexpr typename Vector<T, Allocator>::size_type Vector<T, Allocator>::max_size() const noexcept {
        return std::allocator_traits<Allocator>::max_size(allocator_);
    }

    template<class T, class Allocator>
    [[nodiscard]] constexpr typename Vector<T, Allocator>::size_type Vector<T, Allocator>::capacity() const noexcept {
        return capacity_;
    }

    template<class T, class Allocator>
    void Vector<T, Allocator>::resize(size_type sz) {
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
    constexpr void Vector<T, Allocator>::resize(size_type sz, const T& c) {
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
    constexpr void Vector<T, Allocator>::reserve(size_type n) {
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
    constexpr void Vector<T, Allocator>::shrink_to_fit() {
        if (size_ < capacity_) {
            T* new_data = allocator_.allocate(size_);
            std::uninitialized_move(data_, data_ + size_, new_data);
            std::destroy(data_, data_ + size_);
            allocator_.deallocate(data_, capacity_);
            data_ = new_data;
            capacity_ = size_;
        }
    }
}; // namespace my_std
