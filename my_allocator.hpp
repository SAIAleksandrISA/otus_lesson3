#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T, std::size_t N>
class MyAllocator
{
public:
    using value_type = T;

    template<typename U>
    struct rebind
    {
        using other = MyAllocator<U, N>;
    };

    MyAllocator()
        : m_prtPool(static_cast<char*>(::operator new(N * sizeof(T))), [](char* p) { ::operator delete(p); })
        , m_offset(0)
    {
    }

    ~MyAllocator() = default;

    template <typename U, std::size_t NN>
    MyAllocator(const MyAllocator<U, NN>& other) noexcept
        : m_prtPool(reinterpret_cast<const MyAllocator<T, N>&>(other).m_prtPool)
        , m_offset(reinterpret_cast<const MyAllocator<T, N>&>(other).m_offset)
    {
    }

    T* allocate(std::size_t n)
    {
        if (n == 0) return nullptr;
        if (n > (std::size_t(-1) / sizeof(T))) throw std::bad_alloc();
        if (m_offset + n > N) throw std::bad_alloc();

        T* pData = reinterpret_cast<T*>(m_prtPool.get()) + m_offset;
        m_offset += n;
        return pData;
    }

    void deallocate([[maybe_unused]]T* pData, [[maybe_unused]]std::size_t n)
    {
    }

    template <typename U, std::size_t NN> friend class MyAllocator;

private:
    std::shared_ptr<char> m_prtPool;
    size_t m_offset;
};