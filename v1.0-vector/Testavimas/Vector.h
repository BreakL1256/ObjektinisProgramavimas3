#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace std
{
template<class T, class Allocator = allocator<T>>
class Vector
{
    typename allocator_traits<Allocator>::pointer data__;
    size_t size__;
    size_t capacity__;
    Allocator alloc__;
public:
    // types
    using value_type             = T;
    using allocator_type         = Allocator;
    using pointer                = typename allocator_traits<Allocator>::pointer;
    using const_pointer          = typename allocator_traits<Allocator>::const_pointer;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using size_type              = size_t;
    using difference_type        = ptrdiff_t;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // construct/copy/destroy
    constexpr Vector() noexcept(noexcept(Allocator())) : Vector(Allocator()) { }
    constexpr explicit Vector(const Allocator& alloc) noexcept : data__(nullptr), size__(0), capacity__(0), alloc__(alloc)
    {
        reserve(1);
    };
    constexpr explicit Vector(size_type n, const Allocator& alloc = Allocator()) : data__(nullptr), size__(0), capacity__(0), alloc__(alloc)
    {
        resize(n);
    };
    constexpr Vector(size_type n, const T& value, const Allocator& alloc = Allocator()): data__(nullptr), size__(0), capacity__(0), alloc__(alloc)
    {
        resize(n, value);
    };

    ~Vector() // I. destructor
    {
        if(data__)
            allocator_traits<Allocator>::deallocate(alloc__, data__, capacity__);
    };
    constexpr Vector(const Vector& x) // II. copy constructor
        : data__(nullptr), size__(0),
        capacity__(0),
        alloc__(allocator_traits<Allocator>::select_on_container_copy_construction(x.alloc__))
    {
        reserve(x.size__);
        for (size_type i = 0; i < x.size__; ++i) {
            allocator_traits<Allocator>::construct(alloc__, &data__[i], x.data__[i]);
        }
        size__ = x.size__;
    }

    constexpr Vector(Vector&& x) noexcept  // III. move constructor
        : data__(std::exchange(x.data__, nullptr)),
        size__(std::exchange(x.size__, 0)),
        capacity__(std::exchange(x.capacity__, 0)),
        alloc__(std::move(x.alloc__)) {}

    constexpr Vector& operator=(const Vector& x) { // IV. copy assignment
        if (this != &x) {
            if (allocator_traits<Allocator>::propagate_on_container_copy_assignment::value && alloc__ != x.alloc__) {
                if (data__) {
                    clear();
                    allocator_traits<Allocator>::deallocate(alloc__, data__, capacity__);
                }
                alloc__ = x.alloc__;
                data__ = nullptr;
                capacity__ = 0;
            }
            reserve(x.size__);
            if (x.size__ <= size__) {
                std::copy(x.data__, x.data__ + x.size__, data__);
                for (size_type i = x.size__; i < size__; ++i) {
                    allocator_traits<Allocator>::destroy(alloc__, &data__[i]);
                }
            } else {
                for (size_type i = 0; i < size__; ++i) {
                    allocator_traits<Allocator>::construct(alloc__, &data__[i], x.data__[i]);
                }
                for (size_type i = size__; i < x.size__; ++i) {
                    allocator_traits<Allocator>::construct(alloc__, &data__[i], x.data__[i]);
                }
            }
            size__ = x.size__;
        }
        return *this;
    }

    constexpr Vector& operator=(Vector&& x) // V. move assignment
      noexcept(
        allocator_traits<Allocator>::propagate_on_container_move_assignment::value ||
        allocator_traits<Allocator>::is_always_equal::value
      ){
        if (this != &x) {
            if (allocator_traits<Allocator>::propagate_on_container_move_assignment::value) {
                if (data__) {
                    clear();
                    allocator_traits<Allocator>::deallocate(alloc__, data__, capacity__);
                }
                alloc__ = std::move(x.alloc__);
                data__ = std::exchange(x.data__, nullptr);
                size__ = std::exchange(x.size__, 0);
                capacity__ = std::exchange(x.capacity__, 0);
            } else {
                if (data__) {
                    clear();
                    allocator_traits<Allocator>::deallocate(alloc__, data__, capacity__);
                }

                data__ = std::exchange(x.data__, nullptr);
                size__ = std::exchange(x.size__, 0);
                capacity__ = std::exchange(x.capacity__, 0);
            }
        }
        return *this;
    }

    constexpr Vector(initializer_list<T> il, const Allocator& alloc = Allocator()) : data__(nullptr), size__(0), capacity__(0), alloc__(alloc)
    {
        reserve(il.size());
        for (auto& elem : il) {
            allocator_traits<Allocator>::construct(alloc__, &data__[size__++], elem);
        }
    }

    constexpr Vector& operator=(initializer_list<T> il) {
        clear();
        reserve(il.size());
        for (auto& elem : il) {
            allocator_traits<Allocator>::construct(alloc__, &data__[size__++], elem);
        }
        return *this;
    }

    // iterators
    constexpr iterator begin() noexcept
    {
        return data__;
    }

    constexpr const_iterator begin() const noexcept
    {
        return data__;
    }

    constexpr iterator end() noexcept
    {
        return data__ + size__;
    }

    constexpr const_iterator end() const noexcept
    {
        return data__ + size__;
    }

    constexpr reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    constexpr const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    constexpr reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    constexpr const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    constexpr const_iterator cbegin() const noexcept
    {
        return data__;
    }

    constexpr const_iterator cend() const noexcept
    {
        return data__ + size__;
    }

    constexpr const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    constexpr const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    // capacity
    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return size__==0;
    }
    constexpr size_type size() const noexcept
    {
        return size__;
    }
    constexpr size_type max_size() const noexcept
    {
        return allocator_traits<Allocator>::max_size(alloc__);
    }
    constexpr size_type capacity() const noexcept
    {
        return capacity__;
    }

    constexpr void      resize(size_type sz)
    {
        if (sz > capacity__)
        {
            reserve(sz);
        }
        if (sz > size__)
        {
            for (size_type i = size__; i < sz; ++i)
            {
                allocator_traits<Allocator>::construct(alloc__, &data__[i]);
            }
        }
        else
        {
            for (size_type i = sz; i < size__; ++i)
            {
                allocator_traits<Allocator>::destroy(alloc__, &data__[i]);
            }
        }
        size__ = sz;
    };

    constexpr void      resize(size_type sz, const T& c)
    {
        if (sz > capacity__)
        {
            reserve(sz);
        }
        if (sz > size__)
        {
            for (size_type i = size__; i < sz; ++i)
            {
                allocator_traits<Allocator>::construct(alloc__, &data__[i], c);
            }
        }
        else
        {
            for (size_type i = sz; i < size__; ++i)
            {
                allocator_traits<Allocator>::destroy(alloc__, &data__[i]);
            }
        }
        size__ = sz;
    }

    constexpr void      reserve(size_type n)
    {
        if (n > capacity__)
        {
            pointer new_data = allocator_traits<Allocator>::allocate(alloc__, n);
            for (size_type i = 0; i < size__; ++i)
            {
                allocator_traits<Allocator>::construct(alloc__, &new_data[i], std::move(data__[i]));
                allocator_traits<Allocator>::destroy(alloc__, &data__[i]);
            }
            if (data__)
            {
                allocator_traits<Allocator>::deallocate(alloc__, data__, capacity__);
            }
            data__ = new_data;
            capacity__ = n;
        }
    }

    constexpr void      shrink_to_fit()
    {
        if (size__ < capacity__)
        {
            capacity__ = size__;
        }
    };

    // element access
    constexpr reference       operator[](size_type n)
    {
        return data__[n];
    }
    constexpr const_reference operator[](size_type n) const
    {
        return data__[n];
    }
    constexpr const_reference at(size_type n) const
    {
        if (n >= size__)
        {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data__[n];
    }
    constexpr reference       at(size_type n)
    {
        if (n >= size__)
        {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data__[n];
    }
    constexpr reference       front()
    {
        return data__[0];
    }
    constexpr const_reference front() const
    {
        return data__[0];
    }
    constexpr reference       back()
    {
        return data__[size__ - 1];
    }
    constexpr const_reference back() const
    {
        return data__[size__ - 1];
    }
    constexpr pointer         data() noexcept
    {
        return data__;
    }
    constexpr const_pointer   data() const noexcept
    {
        return data__;
    }

    // modifiers
    constexpr void assign(size_type n, const T& u)
    {
        clear();
        reserve(n);
        for (size_type i = 0; i < n; ++i)
        {
            allocator_traits<Allocator>::construct(alloc__, &data__[i], u);
        }
        size__ = n;
    }

    template<class InputIterator>
    constexpr void assign(InputIterator first, InputIterator last)
    {
        clear();
        insert(begin(), first, last);
    }

    constexpr void assign(initializer_list<T> il)
    {
        clear();
        insert(begin(), il);
    }

    constexpr void push_back(const T& x)
    {
        emplace_back(x);
    }

    constexpr void push_back(T&& x)
    {
        emplace_back(std::move(x));
    }

    template<class... Args>
    constexpr reference emplace_back(Args&&... args)
    {
        if (size__ == capacity__)
        {
            reserve(size__ > 0 ? 2 * size__ : 1);
        }
        allocator_traits<Allocator>::construct(alloc__, &data__[size__], std::forward<Args>(args)...);
        ++size__;
        return data__[size__ - 1];
    }

    constexpr void pop_back()
    {
        allocator_traits<Allocator>::destroy(alloc__, &data__[size__ - 1]);
        --size__;
    }

    constexpr iterator insert(const_iterator position, const T& x)
    {
        difference_type offset = position - cbegin();
        if (size__ == capacity__)
        {
            reserve(size__ > 0 ? 2 * size__ : 1);
        }
        iterator pos = begin() + offset;
        if (pos != end())
        {
            for (iterator it = end(); it != pos; --it)
            {
                allocator_traits<Allocator>::construct(alloc__, it, std::move(*(it - 1)));
                allocator_traits<Allocator>::destroy(alloc__, it - 1);
            }
        }
        allocator_traits<Allocator>::construct(alloc__, pos, x);
        ++size__;
        return pos;
    }

    constexpr iterator insert(const_iterator position, T&& x)
    {
        difference_type offset = position - cbegin();
        if (size__ == capacity__)
        {
            reserve(size__ > 0 ? 2 * size__ : 1);
        }
        iterator pos = begin() + offset;
        if (pos != end())
        {
            for (iterator it = end(); it != pos; --it)
            {
                allocator_traits<Allocator>::construct(alloc__, it, std::move(*(it - 1)));
                allocator_traits<Allocator>::destroy(alloc__, it - 1);
            }
        }
        allocator_traits<Allocator>::construct(alloc__, pos, std::move(x));
        ++size__;
        return pos;
    }

    constexpr iterator insert(const_iterator position, size_type n, const T& x)
    {
        difference_type offset = position - cbegin();
        if (size__ + n > capacity__)
        {
            reserve(size__ + n);
        }
        iterator pos = begin() + offset;
        if (pos != end())
        {
            for (iterator it = end() + n - 1; it != pos + n - 1; --it)
            {
                allocator_traits<Allocator>::construct(alloc__, it, std::move(*(it - n)));
                allocator_traits<Allocator>::destroy(alloc__, it - n);
            }
        }
        for (iterator it = pos; it != pos + n; ++it)
        {
            allocator_traits<Allocator>::construct(alloc__, it, x);
        }
        size__ += n;
        return pos;
    }

    template<class InputIterator>
    constexpr iterator insert(const_iterator position, InputIterator first, InputIterator last)
    {
        difference_type offset = position - cbegin();
        size_type n = std::distance(first, last);
        if (size__ + n > capacity__)
        {
            reserve(size__ + n);
        }
        iterator pos = begin() + offset;
        if (pos != end())
        {
            for (iterator it = end() + n - 1; it != pos + n - 1; --it)
            {
                allocator_traits<Allocator>::construct(alloc__, it, std::move(*(it - n)));
                allocator_traits<Allocator>::destroy(alloc__, it - n);
            }
        }
        for (iterator it = pos; first != last; ++it, ++first)
        {
            allocator_traits<Allocator>::construct(alloc__, it, *first);
        }
        size__ += n;
        return pos;
    }

    constexpr iterator insert(const_iterator position, initializer_list<T> il)
    {
        return insert(position, il.begin(), il.end());
    }

    template<class... Args>
    constexpr iterator emplace(const_iterator position, Args&&... args)
    {
        difference_type offset = position - cbegin();
        if (size__ == capacity__)
        {
            reserve(size__ > 0 ? 2 * size__ : 1);
        }
        iterator pos = begin() + offset;
        if (pos != end())
        {
            for (iterator it = end(); it != pos; --it)
            {
                allocator_traits<Allocator>::construct(alloc__, it, std::move(*(it - 1)));
                allocator_traits<Allocator>::destroy(alloc__, it - 1);
            }
        }
        allocator_traits<Allocator>::construct(alloc__, pos, std::forward<Args>(args)...);
        ++size__;
        return pos;
    }

    constexpr iterator erase(const_iterator position)
    {
        difference_type offset = position - cbegin();
        iterator pos = begin() + offset;
        allocator_traits<Allocator>::destroy(alloc__, pos);
        for (iterator it = pos; it != end() - 1; ++it)
        {
            allocator_traits<Allocator>::construct(alloc__, it, std::move(*(it + 1)));
            allocator_traits<Allocator>::destroy(alloc__, it + 1);
        }
        --size__;
        return pos;
    }

    constexpr iterator erase(const_iterator first, const_iterator last)
    {
        difference_type offset = first - cbegin();
        iterator pos = begin() + offset;
        difference_type n = last - first;
        for (iterator it = pos; it != pos + n; ++it)
        {
            allocator_traits<Allocator>::destroy(alloc__, it);
        }
        for (iterator it = pos; it != end() - n; ++it)
        {
            allocator_traits<Allocator>::construct(alloc__, it, std::move(*(it + n)));
            allocator_traits<Allocator>::destroy(alloc__, it + n);
        }
        size__ -= n;
        return pos;
    }

    constexpr void swap(Vector& x) noexcept(
    std::allocator_traits<Allocator>::propagate_on_container_swap::value ||
    std::allocator_traits<Allocator>::is_always_equal::value
    ) {
        if (this != &x) {
            if (std::allocator_traits<Allocator>::propagate_on_container_swap::value || alloc__ == x.alloc__) {
                std::swap(data__, x.data__);
                std::swap(size__, x.size__);
                std::swap(capacity__, x.capacity__);
                std::swap(alloc__, x.alloc__);
            } 
        }
    }

    constexpr void clear() noexcept
    {
        for (size_type i = 0; i < size__; ++i)
        {
            allocator_traits<Allocator>::destroy(alloc__, &data__[i]);
        }
        size__ = 0;
    }

    constexpr Allocator get_allocator() const noexcept
    {
        return alloc__;
    }
};

}
#endif



