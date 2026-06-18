#include <iostream>
#include <map>
#include "my_allocator.hpp"
#include "my_container.hpp"

int factorial(int n)
{
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

template <typename M>
void printMap(const M& map, const std::string& name)
{
    std::cout << name << ":" << std::endl;
    for (const auto& [key, value] : map)
    {
        std::cout << key << " = " << value << std::endl;
    }
}

template <typename C>
void printContainer(C& container, const std::string& name)
{
    std::cout << name << ": ";
    for (const auto& val : container)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::map<int, int> mapSTL;
    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>, 11>> mapAllacator;

    for (int i = 0; i < 10; ++i)
    {
        mapSTL[i] = factorial(i);
        mapAllacator[i] = factorial(i);
    }

    printMap(mapSTL, "mapSTL");
    printMap(mapAllacator, "mapAllacator");

    MyContainer<int> myContainer(10);
    for (int i = 0; i < 10; ++i)
    {
        myContainer.push_back(i);
    }
    printContainer(myContainer, "Elements in myContainer");

    MyContainer<int, MyAllocator<int, 10>> myContainerAllacator(10);
    for (int i = 0; i < 10; ++i)
    {
        myContainerAllacator.push_back(i);
    }
    printContainer(myContainerAllacator, "Elements in myContainerAllacator");

    return 0;
}