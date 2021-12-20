// memory_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <memory>

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
struct Object
{
    int x, y, z;
};

static void PrintMemoryUsage()
{
    std::cout << "Memory usage: " << s_AllocationMetrics.Currentusage() << "bytes\n";
}
int main()
{
   // Object* obj = new Object;
    try
    {
        {
            std::unique_ptr<Object> obj = std::make_unique<Object>();
            PrintMemoryUsage();
        }
        PrintMemoryUsage();
    }
    catch (const std::exception& e)
    {
        std::cerr<< e.what() << std::endl;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

