// lambda_func.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include<algorithm>
#include <functional>

void ForEach(const std::vector<int>& values, const std::function<void(int)>& func)
{
    for (auto it=values.begin();it!=values.end();it++)
        func(*it);
}

int main()
{
    std::vector<int> values = { 1,7,4,2,3 };
    auto it = std::find_if ( values.begin(), values.end(), [](int value) {return value > 3; });
    std::cout << *it << std::endl;

    int a = 5;

    auto lambda = [=](int value) {std::cout << "Value: " << value << std::endl; };
    ForEach(values, lambda);
    std::cin.get();
}

