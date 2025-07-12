#include <iostream>
#include <memory>

template<typename T>
class SharedPtr {
private:
    T* _data;
    size_t* _count;

    void release() {
        if (_count && --(*_count) == 0) {
            delete _data;
            delete _count;
        }
    }

public:
    SharedPtr() : _data{nullptr}, _count{nullptr} {}

    explicit SharedPtr(T* data) : _data{data} {
        _count = new size_t(1);
    }

    SharedPtr(const SharedPtr& other) : _data{other._data}, _count{other._count} {
        ++(*_count);
    }

    SharedPtr(SharedPtr&& other) noexcept : _data{other._data}, _count{other._count} {
        other._data = nullptr;
        other._count = nullptr;
    }

    template<typename U>
    SharedPtr(std::unique_ptr<U>&& other) {
        _data = other.release();
        _count = new size_t(1);
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            _data = other._data;
            _count = other._count;
            ++(*_count);
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            _data = other._data;
            _count = other._count;
            other._data = nullptr;
            other._count = nullptr;
        }
        return *this;
    }

    ~SharedPtr() {
        release();
    }

    void reset(T* data) {
        release();
        _data = data;
        _count = new size_t(_data ? 1 : 0);
    }

    void swap(SharedPtr& other) {
        std::swap(_data, other._data);
        std::swap(_count, other._count);
    }

    size_t use_count() const {
        return _count ? *_count : 0;
    }

    T* get() const {
        return _data;
    }

    T& operator*() {
        return *_data;
    }

    T* operator->() {
        return _data;
    }

    operator bool() const {
        return _data != nullptr;
    }

    bool operator==(const SharedPtr& other) const {
        return _data == other._data;
    }
};

int main() {
    SharedPtr<int> ptr1(new int(10));
    std::cout << *ptr1 << std::endl;
    std::cout << "count: " << ptr1.use_count() << std::endl;

    auto ptr2 = ptr1;
    std::cout << "count after copy: " << ptr1.use_count() << std::endl;

    SharedPtr<int> ptr3(new int(20));
    std::cout << *ptr3 << std::endl;
    std::cout << "count ptr3: " << ptr3.use_count() << std::endl;

    return 0;
}