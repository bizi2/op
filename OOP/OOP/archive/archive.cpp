#include "archive.h"

template <typename T>
TArchive<T>& TArchive<T>::insert(const T* arr, size_t n, size_t pos) {
    if (_size < pos) {
        throw std::logic_error("������ � ������� \"TArchive<T>& insert(const T* arr, size_t n, size_t pos)\": ������������ �������� �������.");
    }
    // �������� ��� ������������
    if (_size + n > _capacity) {
        reserve(_capacity + n);
    }
    // �������� �������� ������
    for (size_t i = _size; i > pos; --i) {
        _data[i + n - 1] = _data[i - 1];
        _states[i + n - 1] = _states[i - 1];
    }
    // ��������� ����� ��������
    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = arr[i];
        _states[pos + i] = State::busy;
    }
    _size += n;
    return *this;
}

// ����� ������������ ������� ��� ���� int
template class TArchive<int>;