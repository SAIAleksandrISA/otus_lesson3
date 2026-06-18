#pragma once
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T, typename Allocator = std::allocator<T>>
class MyContainer
{
public:
    using AllocTraits = std::allocator_traits<Allocator>;

public:
    explicit MyContainer(size_t capacity, const Allocator& alloc = Allocator())
        : m_alloc(alloc), m_size(0), m_capacity(capacity)
    {
        m_pData = AllocTraits::allocate(m_alloc, m_capacity);
    }

    MyContainer(const MyContainer&) = delete;

    MyContainer& operator=(const MyContainer&) = delete;

    ~MyContainer()
    {
        clear();
        AllocTraits::deallocate(m_alloc, m_pData, m_capacity);
    }
public:
    void push_back(const T& val)
    {
        if (m_size >= m_capacity)
        {
            throw std::overflow_error("Container full");
        }

        AllocTraits::construct(m_alloc, m_pData + m_size, val);
        m_size++;
    }

    void clear()
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            AllocTraits::destroy(m_alloc, m_pData + i);
        }
        m_size = 0;
    }

    T* begin() { return m_pData; }
    T* end() { return m_pData + m_size; }
    size_t size() const { return m_size; }

private:
    Allocator m_alloc;
    T* m_pData;
    size_t m_size;
    size_t m_capacity;
};