// custom_allocator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>

int fact(int n)
{
    if (n == 0)
        return 0;
    else
        return n + fact(n - 1);

}
int main()
{
    std::map <int, int> mp = {
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


    std::cout << "Hello World!\n";
}

