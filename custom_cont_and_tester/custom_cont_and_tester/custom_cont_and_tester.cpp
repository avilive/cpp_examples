#include <cassert>
#include <vector>

template<typename T>
struct It
{
    std::vector<T>& vec_;
    int pointer_;

    It(std::vector<T>& vec) : vec_{ vec }, pointer_{ 0 } {}

    It(std::vector<T>& vec, int size) : vec_{ vec }, pointer_{ size } {}

    bool operator!=(const It<T>& other) const
    {
        return !(*this == other);
    }

    bool operator==(const It<T>& other) const
    {
        return pointer_ == other.pointer_;
    }

    It& operator++()
    {
        ++pointer_;
        return *this;
    }

    T& operator*() const
    {
        return vec_.at(pointer_);
    }
};

template<typename T>
struct Vector
{
    std::vector<T> vec_;

    void push_back(T item)
    {
        vec_.push_back(item);
    };

    It<T> begin()
    {
        return It<T>(vec_);
    }

    It<T> end()
    {
        return It<T>(vec_, vec_.size());
    }
};



struct verify;
class tester {
    friend verify;
    static int livecount;
    const tester* self;
public:
    tester() :self(this) { ++livecount; }
    tester(const tester&) :self(this) { ++livecount; }
    ~tester() { assert(self == this); --livecount; }
    tester& operator=(const tester& b) {
        assert(self == this && b.self == &b);
        return *this;
    }
    void cfunction() const { assert(self == this); }
    void mfunction() { assert(self == this); }
};
int tester::livecount = 0;

struct verify {
    ~verify() { assert(tester::livecount == 0); }
}verifier;

int main()
{

    return 0;
}