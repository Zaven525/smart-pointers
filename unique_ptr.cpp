#include <iostream>

template<typename T>
class UniquePtr {
public:
    UniquePtr() : _data{nullptr} {}
    explicit UniquePtr(T *data) : _data(data) {};
    UniquePtr(UniquePtr&) = delete;
    UniquePtr operator=(UniquePtr&) = delete;
    UniquePtr(UniquePtr &&other) noexcept : _data{other._data} { release(); }
    UniquePtr& operator=(UniquePtr &&other) noexcept {
        if (this != &other) {
            delete _data;
            _data = other._data;
            other._data = nullptr;
        }
        return *this;
    }
    ~UniquePtr() { release(); }

    T* release() {
        T *tmp = _data;
        if (_data) {
            _data = nullptr;
        }
        return tmp;
    }

    void reset(T *data) {
        if (_data != data) {
            delete _data;
            _data = data;
        }
    }
    
    void swap(UniquePtr &other) {
        std::swap(_data, other._data);
    }

    T* get() const{
        return _data;
    }

    operator bool() const{
        return _data;
    }

    T& operator*() {
        return *(_data);
    }

    T* operator->() {
        return _data;
    }


private:
    T *_data;
};


int main() {
    UniquePtr<int> a(new int(4));
    if (a) std::cout << "a = " << *a.get() << std::endl;

    UniquePtr b(new int(3));
    std::cout << "b = " << *b.get() << std::endl;

    int *p = a.release();
    std::cout << "p = " << *p << std::endl;

    b.reset(p);
    std::cout << "b = " << *b.get() << std::endl;



    return 0;
}
// template<typename T>
// class UniquePtr {
// public:
//     explicit UniquePtr(T* ptr) : _ptr{ptr} {}
//     UniquePtr(UniquePtr&) = delete;
//     UniquePtr& operator = (UniquePtr&) = delete; 
//     ~UniquePtr() {
//         delete _ptr;
//     }
    
//     int* get() {
//         return _ptr;
//     }

//     int* release() {
//         int *tmp = _ptr;
//         _ptr = nullptr;
//         return tmp;
//     }

//     void reset(int* ptr) {
//         if (ptr != _ptr) {
//             delete _ptr;
//             _ptr = ptr;
//         }
//     }

//     void swap(int* ptr) {
//         int* tmp = ptr;
//         ptr = _ptr;
//         _ptr = tmp;
//     }
// private:
//     int* _ptr;
// };

// int main() {
//     UniquePtr a(new int(3));
//     int* y = new int(1);
//     a.swap(y);
//     std::cout << *a.get();
//     return 0;
// }