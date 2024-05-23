#pragma once
#include <iostream>
#include <stdexcept>

#define STEP_CAPACITY 15

enum State { empty, busy, deleted };

template <typename T>
class TArchive {
    T* _data;
    State* _states;
    size_t _capacity;
    size_t _size;
    size_t _deleted;

public:
    TArchive();
    TArchive(const TArchive& archive);
    TArchive(const T* arr, size_t n);
    TArchive(size_t n, T value);
    TArchive(const TArchive& archive, size_t pos, size_t n);
    ~TArchive();

    void print() const noexcept;
    bool empty() const noexcept;
    bool full() const noexcept;
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    const T* data() const noexcept;

    void swap(TArchive& archive);
    TArchive& assign(const TArchive& archive);
    void clear();
    void resize(size_t n, T value);
    void reserve(size_t n);

    void push_back(T value);
    void pop_back();
    void push_front(T value);
    void pop_front();

    TArchive& insert(const T* arr, size_t n, size_t pos);
    TArchive& insert(T value, size_t pos);
    TArchive& replace(size_t pos, T new_value);
    TArchive& erase(size_t pos, size_t n);
    TArchive& remove_all(T value);
    TArchive& remove_first(T value);
    TArchive& remove_last(T value);
    TArchive& remove_by_index(size_t pos);

    size_t* find_all(T value) const noexcept;
    size_t find_first(T value) const noexcept;
    size_t find_last(T value) const noexcept;

private:
    size_t count_value(T value) const noexcept;
    void shift_right(size_t from);
    void shift_left(size_t from);
};

#include "archive_impl.h"