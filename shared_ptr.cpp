#include <iostream>

template<typename T>
class SharedPtr{
private:
    T *_data;
    size_t *_count; //baci datan countnel petqa yndhanur lini shared ptrneri hamar dra hamarel *count
    void release() {
        if (_data) {
            if (--(*_count) == 0) {
                delete _data;
                delete _count;
            }
        }
    }
public:
    SharedPtr() : _data(nullptr), _count(nullptr) {}
    explicit SharedPtr(T* data) : _data(data) {_count = new size_t(1); }
    SharedPtr(const SharedPtr &other) : _data(other._data), _count(other._count) {
        *_count++;
    }
    SharedPtr(SharedPtr &&ohter) noexcept: _data(other._data), _count{other._count; }{
        other.release();
    }
    template<typename U>
    SharedPtr(std::unique_ptr<U> &&other) {
        _data = other.release();
        *_count = 1;
    }
    SharedPtr &operator=(const SharedPtr &other) {
        if (this != &other) {
            _data = other._data;
            _count = other._count;
            ++*_count;
        }
        return *this;
    }
    SharedPtr &&operator=(SharedPtr &&other) noexcept {
        if (this != &other) {
            _data = other._data;
            _count = other._count;
            other.release();
        }

        return *this;
    }
    ~SharedPtr() {
        release();
    }


    void reset(T *data) {
        release();
        _data = data;
        _count = new size_t(new_data ? 1 : 0);
    }

    void swap(SharedPtr &other) {
        std::swap(_data, other._data);
        std::swap(_count, other._count);
    }

    size_t use_count() const{
        return *(_count);
    }

    T *get() const {
        return _data;
    }

    T &operator*() {
        return *(_data);
    }

    T *operator->() {
        return _data;
    }
 
    operator bool() const{
        return data != nullptr;
    }

    bool operator==(const SharedPtr &other) {
        return _data == other._data;
    }
};

int mian() {
    SharedPtr <int> ptr1(new int(10));
    std::cout << *ptr1 << std::endl;
    std::cout << "count: " << ptr1.use_count();

    auto ptr2 = ptr1;
    std::cout << "count: " << ptr1.use_count();

    SharedPtr <int> ptr3(new int(10));
}