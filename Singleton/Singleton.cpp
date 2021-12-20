// Singleton.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

class Random
{
public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;
    static Random& Get()
    {
        static Random instance;
        return instance;
    }

    static float Float() { return Get().IFloat(); }

private:
    float IFloat() { return m_RandomGenerator; }
    Random() {}
    float m_RandomGenerator =0.5f;
};
//Random Random::s_Instance;

int main()
{
    //Random::Get().Float();
    std::cout << Random::Float() << std::endl;
    return 0;
}

