#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <limits>

#define USE_PRETTY 1

template<typename T>
class limitedAllocator
{
public:
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = limitedAllocator<U>;
    };

    limitedAllocator() = default;

    ~limitedAllocator() = default;
        
    
    template<typename U>
    limitedAllocator(const limitedAllocator<U>&) {

    }

    T *allocate(std::size_t n) {/*
#ifndef USE_PRETTY
        std::cout << "allocate: [n = " << n << "]" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif*/


        auto p = std::malloc(n * sizeof(T));
        if (!p || ((mAllocations+n)>maxAllocations + 1))
            throw std::bad_alloc();

        mAllocations+=n;
      //  std::cout << "mAllocations = " << mAllocations << std::endl;
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
        /*
#ifndef USE_PRETTY
        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif*/
        std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
/*#ifndef USE_PRETTY
        std::cout << "construct" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif*/
        new(p) U(std::forward<Args>(args)...);
    };
    
    
    //template<typename U> //???
    void destroy(T *p) {
/*#ifndef USE_PRETTY
        std::cout << "destroy" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif*/
        p->~T();
    }
private:
    std::size_t  mAllocations=0;
    const std::size_t maxAllocations = 10;
};


//custom container 

template <class T, class A = std::allocator<T> >
class customContainer {
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;
 

    class iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category; //or another tag

        iterator();
        iterator(const iterator&);
        ~iterator();

        iterator& operator=(const iterator&);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        bool operator<(const iterator&) const; //optional
        bool operator>(const iterator&) const; //optional
        bool operator<=(const iterator&) const; //optional
        bool operator>=(const iterator&) const; //optional

        iterator& operator++();
        iterator operator++(int); //optional
        iterator& operator--(); //optional
        iterator operator--(int); //optional
        iterator& operator+=(size_type); //optional
        iterator operator+(size_type) const; //optional
        friend iterator operator+(size_type, const iterator&); //optional
        iterator& operator-=(size_type); //optional            
        iterator operator-(size_type) const; //optional
        difference_type operator-(iterator) const; //optional

        reference operator*() const;
        pointer operator->() const;
        reference operator[](size_type) const; //optional
    };
    class const_iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename const A::reference reference;
        typedef typename const A::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category; //or another tag

        const_iterator();
        const_iterator(const const_iterator&);
        const_iterator(const iterator&);
        ~const_iterator();

        const_iterator& operator=(const const_iterator&);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;
        bool operator<(const const_iterator&) const; //optional
        bool operator>(const const_iterator&) const; //optional
        bool operator<=(const const_iterator&) const; //optional
        bool operator>=(const const_iterator&) const; //optional

        const_iterator& operator++();
        const_iterator operator++(int); //optional
        const_iterator& operator--(); //optional
        const_iterator operator--(int); //optional
        const_iterator& operator+=(size_type); //optional
        const_iterator operator+(size_type) const; //optional
        friend const_iterator operator+(size_type, const const_iterator&); //optional
        const_iterator& operator-=(size_type); //optional            
        const_iterator operator-(size_type) const; //optional
        difference_type operator-(const_iterator) const; //optional

        reference operator*() const;
        pointer operator->() const;
        reference operator[](size_type) const; //optional
        
    };

    typedef std::reverse_iterator<iterator> reverse_iterator; //optional
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator; //optional

    customContainer()= default;
    customContainer(const customContainer&);
    ~customContainer() = default;

    customContainer& operator=(const customContainer&);
    bool operator==(const customContainer&) const;
    bool operator!=(const customContainer&) const;
    bool operator<(const customContainer&) const; //optional
    bool operator>(const customContainer&) const; //optional
    bool operator<=(const customContainer&) const; //optional
    bool operator>=(const customContainer&) const; //optional

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rbegin(); //optional
    const_reverse_iterator rbegin() const; //optional
    const_reverse_iterator crbegin() const; //optional
    reverse_iterator rend(); //optional
    const_reverse_iterator rend() const; //optional
    const_reverse_iterator crend() const; //optional

    reference front(); //optional
    const_reference front() const; //optional
    reference back(); //optional
    const_reference back() const; //optional
    template<class ...Args>
    void emplace_front(Args&&...); //optional
    template<class ...Args>
    void emplace_back(Args&&...); //optional
    void push_front(const T&); //optional
    void push_front(T&&); //optional
    void push_back(const T&); //optional
    void push_back(T&&); //optional
    void pop_front(); //optional
    void pop_back(); //optional
   // reference operator[](size_type); //optional
    reference operator[](size_type idx) //optional
    {
        return v[idx];
    }
    
    //const_reference operator[](size_type) const; //optional

 /*   const_reference operator[](size_type idx) const//optional
    {
        return v[idx];
    }*/
 
    const_reference at(const size_type idx) const //optional
    {
        return v.at(idx);
    }

    template<class ...Args>
    iterator emplace(const_iterator, Args&&...); //optional
    iterator insert(const_iterator, const T&); //optional
    iterator insert(const_iterator, T&&); //optional
    iterator insert(const_iterator, size_type, T&); //optional
    template<class iter>
    iterator insert(const_iterator, iter, iter); //optional
    iterator insert(const_iterator, std::initializer_list<T>); //optional
    iterator erase(const_iterator); //optional
    iterator erase(const_iterator, const_iterator); //optional
    void clear(); //optional
    template<class iter>
    void assign(iter, iter); //optional
    void assign(std::initializer_list<T>); //optional
    void assign(size_type, const T&); //optional

    void swap(customContainer&);
    size_type capacity()
    {
        return v.capacity();
    }

    size_type size() const
    {
        return v.size();
    }
    size_type max_size() const;
    bool empty() const;
    bool Reserve(size_t capacity)
    {
        if (capacity > maxCapacity) return false;
        v.reserve(capacity);
        return true;
    }
    bool PushBack(const T& item)
    {
        if (v.size() >= maxCapacity) return false;
        v.push_back(item);
        return true;
    }
    A get_allocator() const; //optional
private:
    std::vector<T,A> v;
    const size_t maxCapacity = 10;
};

template <class T, class A = std::allocator<T> >
void swap(customContainer<T, A>&, customContainer<T, A>&); //optional


//optional
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////

int fact(const int& n)
{
    if (n == 0)
        return 0;
    else
        return n + fact(n - 1);
}

int main(int, char* []) 
    {

    {
        //1.MAP 
        auto m1 = std::map<int, int>{};
       
        for (int i = 0; i < 10; i++) 
            m1.insert(std::pair<int, int>(i, fact(i)));
 
   
        std::cout << "Map print: " << std::endl;
       for (auto it = m1.begin(); it != m1.end(); it++)
            std::cout << it->first << ' ' << it->second << std::endl;
    }

    //map with custom allocators that allows only 10 elements
    {
        auto m = std::map<int, int, std::less<int>,
            limitedAllocator<std::pair<const int, int>>>{};
        for (int i = 0; i < 10; i++)
            m.insert(std::pair<int, int>(i, fact(i)));

        std::cout << "Map with allocator  print: " << std::endl;
        for (auto it = m.begin(); it != m.end(); it++)
            std::cout << it->first << ' ' << it->second << std::endl;


    }
   //custom container
    std::cout << "Custom vector  with allocator  print: " << std::endl;
    auto vec = customContainer<int, std::allocator<int>>{};
    /* vec.Reserve(10);
    for (int i =0 ;i<10;i++)
        vec.PushBack(fact(i));
    for (int i=0; i<10;i++)
        std::cout << vec.at(i) << std::endl;*/

    ///auto v1 = std::vector<int>{};
    std::cout << vec.capacity() << std::endl;

    vec.Reserve(5); // Add 399 to the end of the vector

    std::cout << vec.capacity() << std::endl;

    return 0;
}
