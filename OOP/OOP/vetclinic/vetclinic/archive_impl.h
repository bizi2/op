#pragma once
#pragma once

template <typename T>
TArchive<T>::TArchive() : _size(0), _capacity(STEP_CAPACITY), _deleted(0) {
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; ++i) {
        _states[i] = State::empty;
    }
}

template <typename T>
TArchive<T>::~TArchive() {
    delete[] _data;
    delete[] _states;
}

template <typename T>
bool TArchive<T>::empty() const noexcept {
    return _size == 0;
}

template <typename T>
bool TArchive<T>::full() const noexcept {
    return _size == _capacity;
}

template <typename T>
size_t TArchive<T>::size() const noexcept {
    return _size;
}

template <typename T>
size_t TArchive<T>::capacity() const noexcept {
    return _capacity;
}

template <typename T>
const T* TArchive<T>::data() const noexcept {
    return _data;
}

template <typename T>
void TArchive<T>::print() const noexcept {
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == State::busy) {
            std::cout << _data[i] << ", ";
        }
    }
}

template <typename T>
TArchive<T>& TArchive<T>::insert(T value, size_t pos) {
    if (pos > _size) {
        throw std::logic_error("Ошибка в функции \"TArchive<T>& insert(T value, size_t pos)\": неправильное значение позиции.");
    }

    if (full()) {
        reserve(_capacity + STEP_CAPACITY);
    }

    shift_right(pos);
    _data[pos] = value;
    _states[pos] = State::busy;
    ++_size;

    return *this;
}

template <typename T>
void TArchive<T>::shift_right(size_t from) {
    for (size_t i = _size; i > from; --i) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
}

template <typename T>
void TArchive<T>::shift_left(size_t from) {
    for (size_t i = from; i < _size - 1; ++i) {
        _data[i] = _data[i + 1];
        _states[i] = _states[i + 1];
    }
    _states[_size - 1] = State::empty;
}

template <typename T>
void TArchive<T>::clear() {
    delete[] _data;
    delete[] _states;
    _size = 0;
    _capacity = STEP_CAPACITY;
    _deleted = 0;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; ++i) {
        _states[i] = State::empty;
    }
}

template <typename T>
void TArchive<T>::reserve(size_t n) {
    if (n <= _capacity) {
        return;
    }

    T* new_data = new T[n];
    State* new_states = new State[n];

    for (size_t i = 0; i < _capacity; ++i) {
        new_data[i] = _data[i];
        new_states[i] = _states[i];
    }
    for (size_t i = _capacity; i < n; ++i) {
        new_states[i] = State::empty;
    }

    delete[] _data;
    delete[] _states;

    _data = new_data;
    _states = new_states;
    _capacity = n;
}

template <typename T>
void TArchive<T>::push_back(T value) {
    insert(value, _size);
}

template <typename T>
void TArchive<T>::pop_back() {
    if (_size > 0) {
        _states[_size - 1] = State::deleted;
        --_size;
    }
}

template <typename T>
void TArchive<T>::push_front(T value) {
    insert(value, 0);
}

template <typename T>
void TArchive<T>::pop_front() {
    if (_size > 0) {
        _states[0] = State::deleted;
        shift_left(0);
        --_size;
    }
}

template <typename T>
size_t TArchive<T>::count_value(T value) const noexcept {
    size_t count = 0;
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy && _data[i] == value) {
            ++count;
        }
    }
    return count;
}

template <typename T>
size_t* TArchive<T>::find_all(T value) const noexcept {
    size_t count = count_value(value);
    if (count == 0) {
        return nullptr;
    }
    size_t* positions = new size_t[count + 1];
    positions[0] = count;

    size_t index = 1;
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy && _data[i] == value) {
            positions[index++] = i;
        }
    }

    return positions;
}

template <typename T>
size_t TArchive<T>::find_first(T value) const noexcept {
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy && _data[i] == value) {
            return i;
        }
    }
    return -1;
}

template <typename T>
size_t TArchive<T>::find_last(T value) const noexcept {
    for (size_t i = _size; i > 0; --i) {
        if (_states[i - 1] == State::busy && _data[i - 1] == value) {
            return i - 1;
        }
    }
    return -1;
}

template <typename T>
TArchive<T>& TArchive<T>::remove_all(T value) {
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy && _data[i] == value) {
            _states[i] = State::deleted;
        }
    }
    size_t i = 0;
    while (i < _size) {
        if (_states[i] == State::deleted) {
            shift_left(i);
            --_size;
        }
        else {
            ++i;
        }
    }
    return *this;
}

template <typename T>
TArchive<T>& TArchive<T>::remove_first(T value) {
    size_t pos = find_first(value);
    if (pos != -1) {
        _states[pos] = State::deleted;
        shift_left(pos);
        --_size;
    }
    return *this;
}

template <typename T>
TArchive<T>& TArchive<T>::remove_last(T value) {
    size_t pos = find_last(value);
    if (pos != -1) {
        _states[pos] = State::deleted;
        shift_left(pos);
        --_size;
    }
    return *this;
}

template <typename T>
TArchive<T>& TArchive<T>::remove_by_index(size_t pos) {
    if (pos >= _size) {
        throw std::logic_error("Ошибка в функции \"TArchive<T>& remove_by_index(size_t pos)\": неправильное значение позиции.");
    }
    _states[pos] = State::deleted;
    shift_left(pos);
    --_size;
    return *this;
}