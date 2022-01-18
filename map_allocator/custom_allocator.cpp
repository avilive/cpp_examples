// custom_allocator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <vector>

int fact(int n)
{
    if (n == 0)
        return 0;
    else
        return n + fact(n - 1);

}



///////////////////////////////////////////////////////////////
//TRACKING ALLOCATOR
template<class T>
class TrackingAllocator
{
public:
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;

    using size_type = size_t;

    TrackingAllocator() = default;

    template<class U>
    TrackingAllocator(const TrackingAllocator<U>& other) {}

    ~TrackingAllocator() = default;

    pointer allocate(size_type numObjects)
    {
        mAllocations += numObjects;
        std::cout << "Objects: " << numObjects << " Size:" << numObjects * sizeof(T) << std::endl;
        return static_cast<pointer>(operator new(sizeof(T) * numObjects));
    }

    void deallocate(pointer p, size_type numObjects)
    {
        operator delete(p);
    }

    size_type get_allocations() const
    {
        return mAllocations;
    }

private:
    static size_type mAllocations;
};

template<class T>
typename TrackingAllocator<T>::size_type TrackingAllocator<T>::mAllocations = 0;
///////////////////////////////////////////////////////////////


struct AllocationMetrics
{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;


    uint32_t Currentusage() { return TotalAllocated - TotalFreed; }

};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size)
{
    s_AllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
    s_AllocationMetrics.TotalFreed += size;
    free(memory);
}

static void PrintMemoryUsage()
{
    std::cout << "Memory usage: " << s_AllocationMetrics.Currentusage() << "bytes\n";
}

int main()
{
   /* std::map <int, int> mp = {
                                {1,11},
                                {2,22},
                                {3,33},
                                {4,44}
                             };
    int i=0;
    //fill
     for (int i =0;i<10;i++)
         mp.insert(std::make_pair(i, fact(i)));
         
    //print
    for (auto it = mp.begin(); it != mp.end(); it++)
        std::cout << it->first << ' '<<it->second << std::endl;



        */
    std::vector<int, TrackingAllocator<int>> v(5);
    auto m = std::map<int, int, std::less<int>,
        TrackingAllocator<std::pair<const int, int>>>{};
    for (int i = 0; i < 10; ++i) 
       m.insert(std::make_pair(i, fact(i)));
       //  std::cout << std::endl;
    for (auto it = m.begin(); it != m.end(); it++)
        std::cout << it->first << ' ' << it->second << std::endl;
    PrintMemoryUsage();
    std::cout << m.get_allocator().get_allocations() << std::endl;
    std::cout << v.get_allocator().get_allocations() << std::endl;
    system("PAUSE");
}


