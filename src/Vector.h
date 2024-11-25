#pragma once

#include <stdexcept>

template<typename T>

class Vector {

private:

    T* elements;     

    size_t capacity;  

    size_t count;    
public:

    class Iterator {

    public:

        Iterator(T* ptr) : ptr_(ptr) {}

        T& operator*() const { return *ptr_; }



        Iterator& operator++() {

            ptr_++;

            return *this;

        }

        bool operator!=(const Iterator& other) const {

            return ptr_ != other.ptr_;

        }


    private:

        T* ptr_;

    };

    Iterator begin() {

        return Iterator(elements); 
    }

    Iterator end() {

        return Iterator(elements+count); 
    }

    // Default constructor
    Vector() : elements(nullptr), capacity(0), count(0) {}

    // Destructor
    ~Vector() {
        delete[] elements;
    }

    // Copy constructor
    Vector(const Vector& other) : capacity(other.capacity), count(other.count) {

        elements = new T[capacity];

        for (size_t i = 0; i < count; ++i) {

            elements[i] = other.elements[i];

        }

    }

    // Assignment operator
    Vector& operator=(const Vector& other) {

        if (this != &other) {

            delete[] elements;

            capacity = other.capacity;

            count = other.count;

            elements = new T[capacity];

            for (size_t i = 0; i < count; ++i) {

                elements[i] = other.elements[i];

            }

        }

        return *this;

    }

    // Function to add an element to the end of the vector
    void push_back(const T& value) {

        if (count >= capacity) {
            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;

            T* newElements = new T[newCapacity];

            for (size_t i = 0; i < count; ++i) {

                newElements[i] = elements[i];

            }

            delete[] elements;

            elements = newElements;

            capacity = newCapacity;

        }

        elements[count++] = value;

    }

    void pop_back() {

        if (count > 0) {

            --count;

        }

    }

    size_t size() const {

        return count;

    }

    T& at(size_t index) {

        if (index >= count) {

            throw std::out_of_range("Index out of range");

        }

        return elements[index];

    }


    const T& at(size_t index) const {

        if (index >= count) {

            throw std::out_of_range("Index out of range");

        }

        return elements[index];

    }




    T& operator[](size_t index) {

        return elements[index];

    }


    const T& operator[](size_t index) const {

        return elements[index];

    }


    bool empty() const {

        return size() == 0;

    }


    void clear() {

        count = 0;

    }
    template <typename... Args>

    void emplace_back(Args&&... args) {

        if (count >= capacity) {

            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;

            T* newElements = new T[newCapacity];

            for (size_t i = 0; i < count; ++i) {

                newElements[i] = elements[i]; 

            }

            delete[] elements; 

            elements = newElements;

            capacity = newCapacity;

        }


        new(&elements[count]) T(std::forward<Args>(args)...);

        ++count;

    }


    T& back() {

        if (count == 0) {

            throw std::out_of_range("Vector is empty");

        }

        return elements[count - 1];

    }
    T& front() {

        if (empty()) {

            throw std::out_of_range("Cannot access front of an empty vector.");

        }

        return elements[0];

    }


    const T& front() const {

        if (empty()) {

            throw std::out_of_range("Cannot access front of an empty vector.");

        }

        return elements[0];

    }

};

