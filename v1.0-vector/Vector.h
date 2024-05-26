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
    /*pointer*/ typename allocator_traits<Allocator>::pointer data__;
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
    constexpr explicit Vector(const Allocator&) noexcept : data__(nullptr), size__(0), capacity__(0), alloc__(Allocator())
    {
        reserve(1);
    };
    constexpr explicit Vector(size_type n, const Allocator& = Allocator()) : data__(nullptr), size__(0), capacity__(0), alloc__(Allocator())
    {
        resize(n);
    };
    constexpr Vector(size_type n, const T& value, const Allocator& = Allocator()): data__(nullptr), size__(0), capacity__(0), alloc__(Allocator())
    {
        resize(n, value);
    };

    ~Vector() // I. destructor
    {
        if(data__)
            alloc__.deallocate(data__, capacity__);
    };
    constexpr Vector(const Vector& x) // II. copy constructor
        : data__(nullptr), size__(0),
        capacity__(0),
        alloc__(allocator_traits<Allocator>::select_on_container_copy_construction(x.alloc__))
    {
        reserve(x.size__);
        for (size_type i = 0; i < x.size__; ++i) {
            emplace_back(x.data__[i]);
        }
    }

//    constexpr Vector(const Vector&, const type_identity_t<Allocator>&): // II. copy constructor
//        data__(nullptr), size__(0), capacity__(0), alloc__(alloc)
//    {
//        reserve(x.size__);
//        for (size_type i = 0; i < x.size__; ++i) {
//            emplace_back(x.data__[i]);
//        }
//    }

    constexpr Vector(Vector&& x) noexcept  // III. move constructor
        : data__(std::exchange(x.data__, nullptr)),
        size__(std::exchange(x.size__, 0)),
        capacity__(std::exchange(x.capacity__, 0)),
        alloc__(std::move(x.alloc__)) {}


//    constexpr Vector(Vector&&, const type_identity_t<Allocator>&): // III. move constructor
//        data__(std::exchange(x.data__, nullptr)),
//        size__(std::exchange(x.size__, 0)),
//        capacity__(std::exchange(x.capacity__, 0)),
//        alloc__(alloc__) {}



    constexpr Vector& operator=(const Vector& x) { // IV. copy assignment
        if (this != &x) {
            if (allocator_traits<Allocator>::propagate_on_container_copy_assignment::value && alloc__ != x.alloc__) {
                if (data__) {
                    clear();
                    alloc__.deallocate(data__, capacity__);
                }
                alloc__ = x.alloc__;
                data__ = nullptr;
                capacity__ = 0;
            }
            reserve(x.size__);
            if (x.size__ <= size__) {
                std::copy(x.data__, x.data__ + x.size__, data__);
                for (size_type i = x.size__; i < size__; ++i) {
                    alloc__.destroy(&data__[i]);
                }
            } else {
                for (size_type i = 0; i < size__; ++i) {
                    alloc__.construct(&data__[i], x.data__[i]);
                }
                for (size_type i = size__; i < x.size__; ++i) {
                    alloc__.construct(&data__[i], x.data__[i]);
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
                    alloc__.deallocate(data__, capacity__);
                }
                alloc__ = std::move(x.alloc__);
                data__ = std::exchange(x.data__, nullptr);
                size__ = std::exchange(x.size__, 0);
                capacity__ = std::exchange(x.capacity__, 0);
            } else {
                if (data__) {
                    clear();
                    alloc__.deallocate(data__, capacity__);
                }

                data__ = std::exchange(x.data__, nullptr);
                size__ = std::exchange(x.size__, 0);
                capacity__ = std::exchange(x.capacity__, 0);
            }
        }
        return *this;
    }

    constexpr Vector(initializer_list<T> il, const Allocator& = Allocator()) : data__(nullptr), size__(0), capacity__(0), alloc__(Allocator())
   {
        insert(begin(), il);
    }

    constexpr Vector& operator=(initializer_list<T> il) {
        clear();
        reserve(il.size());
        for (auto& elem : il) {
            emplace_back(elem);
        }
        return *this;
    }


//    constexpr Vector& operator=(initializer_list<T> il){
//        clear();
//        reserve(il.size());
//        for (auto& elem : il) {
//            emplace_back(elem);
//        }
//        return *this;
//    }

//    template<class InputIt>
//      constexpr void assign(InputIt first, InputIt last);
//    template<container-compatible-range<T> R>
//      constexpr void assign_range(R&& rg);
//    constexpr void assign(size_type n, const T& u);
//    constexpr void assign(initializer_list<T>);
//    constexpr allocator_type get_allocator() const noexcept;

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
        return alloc__.max_size();
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
                alloc__.construct(&data__[i]);
            }
        }
        else
        {
            for (size_type i = sz; i < size__; ++i)
            {
                alloc__.destroy(&data__[i]);
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
                alloc__.construct(&data__[i], c);
            }
        }
        else
        {
            for (size_type i = sz; i < size__; ++i)
            {
                alloc__.destroy(&data__[i]);
            }
        }
        size__ = sz;
    }

    constexpr void      reserve(size_type n)
    {
        if (n > capacity__)
        {
            pointer new_data = alloc__.allocate(n);
            for (size_type i = 0; i < size__; ++i)
            {
                alloc__.construct(&new_data[i], std::move(data__[i]));
                alloc__.destroy(&data__[i]);
            }
            if (data__)
            {
                alloc__.deallocate(data__, capacity__);
            }
            data__ = new_data;
            capacity__ = n;
        }
    }

    constexpr void      shrink_to_fit()
    {
        if (size__ < capacity__)
        {
            resize(size__);
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
        return data__[size__-1];
    }
    constexpr const_reference back() const
    {
        return data__[size__-1];
    }


    // data access
    constexpr T*       data() noexcept
    {
        return data__;
    }
    constexpr const T* data() const noexcept
    {
        return data__;
    }


    // modifiers
    template<class... Args> constexpr reference emplace_back(Args&&... args)
    {
        if (size__ == capacity__)
        {
            reserve(capacity__ * 2);
        }
        alloc__.construct(&data__[size__], std::forward<Args>(args)...);
        return data__[size__++];
    }

    constexpr void push_back(const T& x)
    {
        if (size__ == capacity__)
        {
            reserve(capacity__* 2);
        }
        alloc__.construct(&data__[size__++], x);
    }
    constexpr void push_back(T&& x)
    {
        emplace_back(std::move(x));
    }

//    template<container-compatible-range<T> R>
//      constexpr void append_range(R&& rg);

    constexpr void pop_back()
    {
        if (size__ > 0)
        {
            alloc__.destroy(&data__[--size__]);
        }
    }

    template<class... Args> constexpr iterator emplace(const_iterator position,
            Args&&... args)
    {
        size_type pos_index = position - cbegin();
        if (size__ == capacity__)
        {
            reserve(2 *capacity__);
        }
        if (pos_index < size__)
        {
            for (size_type i = size__; i > pos_index; --i)
            {
                alloc__.construct(&data__[i], std::move(data__[i - 1]));
                alloc__.destroy(&data__[i - 1]);
            }
        }
        alloc__.construct(&data__[pos_index], std::forward<Args>(args)...);
        ++size__;
        return begin() + pos_index;
    }

    constexpr iterator insert(const_iterator position, const T& x)
    {
        return emplace(position, x);
    }

    constexpr iterator insert(const_iterator position, T&& x)
    {
        return emplace(position, std::move(x));
    }

    constexpr iterator insert(const_iterator position, size_type n, const value_type& x)
    {
        size_type pos_index = position - cbegin();
        if (size__ + n > capacity__)
        {
            reserve(size__ + n);
        }
        for (size_type i = size__; i > pos_index; --i)
        {
            alloc__.construct(&data__[i + n - 1], std::move(data__[i - 1]));
            alloc__.destroy(&data__[i - 1]);
        }
        for (size_type i = 0; i < n; ++i)
        {
            alloc__.construct(&data__[pos_index + i], x);
        }
        size__ += n;
        return begin() + pos_index;
    }

    template<class InputIt, typename = std::_RequireInputIter<InputIt>>
    constexpr iterator insert(const_iterator position, InputIt first, InputIt last)
    {
        size_type pos_index = position - cbegin();
        size_type n = std::distance(first, last);
        if (size__ + n > capacity__)
        {
            reserve(size__ + n);
        }
        for (size_type i = size__; i > pos_index; --i)
        {
            alloc__.construct(&data__[i + n - 1], std::move(data__[i - 1]));
            alloc__.destroy(&data__[i - 1]);
        }
        for (size_type i = 0; first != last; ++i, ++first)
        {
            alloc__.construct(&data__[pos_index + i], *first);
        }
        size__ += n;
        return begin() + pos_index;
    }

    constexpr iterator insert(const_iterator position, initializer_list<T> il)
    {
        return insert(position, il.begin(), il.end());
    }


    constexpr iterator erase(const_iterator position)
    {
        size_type pos_index = position - cbegin();
        if (pos_index >= size__)
        {
            throw std::out_of_range("Vector::erase: position out of range");
        }
        alloc__.destroy(&data__[pos_index]);
        for (size_type i = pos_index; i < size__ - 1; ++i)
        {
            alloc__.construct(&data__[i], std::move(data__[i + 1]));
            alloc__.destroy(&data__[i + 1]);
        }
        --size__;
        return begin() + pos_index;
    }

    constexpr iterator erase(const_iterator first, const_iterator last)
    {
        size_type start_index = first - cbegin();
        size_type end_index = last - cbegin();
        if (start_index >= size__ || end_index > size__ || start_index > end_index)
        {
            throw std::out_of_range("Vector::erase: range out of range");
        }

        for (size_type i = start_index; i < end_index; ++i)
        {
            alloc__.destroy(&data__[i]);
        }
        for (size_type i = end_index; i < size__; ++i)
        {
            alloc__.construct(&data__[i - (end_index - start_index)], std::move(data__[i]));
            alloc__.destroy(&data__[i]);
        }
        size__ -= (end_index - start_index);
        return begin() + start_index;
    }

    constexpr void     swap(Vector& other)
    noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value ||
             allocator_traits<Allocator>::is_always_equal::value)
    {
        std::swap(data__, other.data__);
        std::swap(size__, other.size__);
        std::swap(capacity__, other.capacity__);
        std::swap(alloc__, other.alloc__);
    }

    constexpr void     clear() noexcept
    {
        for (size_type i = 0; i < size__; ++i)
        {
            alloc__.destroy(&data__[i]);
        }
        size__ = 0;
    }
};
}
#endif