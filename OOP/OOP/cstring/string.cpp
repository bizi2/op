#include "string.h"

/// <summary>
/// ����������� �� ���������.
/// </summary>
CString::CString() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new char[_capacity];
    _data[0] = '\0';
}

/// <summary>
/// ����������� �����������.
/// </summary>
/// <param name="str"> - ���������� ������</param>
CString::CString(const CString& str) {
    _size = str._size;
    _capacity = str._capacity;
    _data = new char[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = str._data[i];
    }
    _data[_size - 1] = '\0';
}
/// <summary>
/// 
/// </summary>
/// <param name="c_str"></param>
CString::CString(const char* c_str) {
    _size = 0;

    while (c_str[_size] != '\0') {
        _size++;
    }

    _capacity = (_size/STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;  
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = c_str[i];
    }
    _data[_size - 1] = '\0';

    
}
/// <summary>
///  ����������� �� ����� const char*
/// </summary>
/// <param name="c_str"></param>
/// <param name="n"></param>
CString::CString(const char* c_str, size_t n) {
    _size = n;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = c_str[i];
    }
    _data[_size - 1] = '\0';
}

CString::CString(size_t n, char c) {
    _size = n;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = c;
    }
    _data[_size - 1] = '\0';
}
CString::CString(const CString& str, size_t pos, size_t len) {
    
    if (pos > str._size) {
        throw std::out_of_range("Starting position is out of range.");
    }
    if (len == CString::npos || pos + len > str._size) {
        len = str._size - pos;
    }

    _size = len;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = str._data[pos + i];
    }
    _data[_size - 1] = '\0';
}



/// <summary>
/// ����������.
/// </summary>
CString::~CString() {
    delete[] _data;
    _data = nullptr;
}

/// <summary>
/// �������� ������ �� �������.
/// </summary>
/// <returns>
/// true - ���� ������ �����,
/// false - �����.
/// </returns>
bool CString::empty() const noexcept {
    return _size == 0;
}
void CString::print() const noexcept {
    for (int i = 0; i < _size; i++) {
        std::cout << _data[i];
    }
    
}
bool CString::full() const noexcept {
    return _size == _capacity;
}

/// <summary>
/// ������ ��� ������� ������.
/// </summary>
/// <returns>������ (�����) ������</returns>
size_t CString::size() const noexcept {
    return _size;
}
size_t CString::capacity() const noexcept {
    return _capacity;
}
const char* CString::data() const {
    return _data;
}
void CString::swap(CString& str) {
    std::swap(_data, str._data);
    std::swap(_size, str._size);
    std::swap(_capacity, str._capacity);
}
size_t CString::copy(char* buf, size_t len, size_t pos) const {
    size_t copyLen = std::min(len, _size - pos);
    std::memcpy(buf, _data + pos, copyLen);
    return copyLen;
}
CString CString::substr(size_t pos, size_t len) const {
    // �������� �� ������������ ��������� ������� � �����
    if (pos > _size) {
        throw std::out_of_range("Starting position is out of range.");
    }
    if (len == CString::npos || pos + len > _size) {
        len = _size - pos;
    }

    // �������� ���������
    return CString(_data + pos, len);
}
CString& CString::assign(const CString& str) {
    if (this != &str) {
        delete[] _data;
        _size = str._size;
        _capacity = str._capacity;
        _data = new char[_capacity];
        std::memcpy(_data, str._data, _size + 1);
    }
    return *this;
}


CString& CString::assign(const CString& str, size_t pos, size_t len) {
    // �������� �� ������������ ��������� ������� � �����
    if (pos > str._size) {
        throw std::out_of_range("Starting position is out of range.");
    }
    if (len == CString::npos || pos + len > str._size) {
        len = str._size - pos;
    }

    if (this != &str || pos != 0 || len != str._size) {
        delete[] _data;
        _size = len;
        _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
        _data = new char[_capacity];
        std::memcpy(_data, str._data + pos, _size);
        _data[_size] = '\0';
    }
    return *this;
}


CString& CString::assign(const char* s) {
    size_t len = std::strlen(s);
    if (_capacity < len) {
        delete[] _data;
        _size = len;
        _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
        _data = new char[_capacity];
    }
    strcpy_s(_data, _capacity, s);
    return *this;
}


CString& CString::assign(const char* s, size_t n) {
    if (_capacity < n) {
        delete[] _data;
        _size = n;
        _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
        _data = new char[_capacity];
    }
    std::memcpy(_data, s, n);
    _data[n] = '\0';
    return *this;
}


CString& CString::assign(size_t n, char c) {
    if (_capacity < n) {
        delete[] _data;
        _size = n;
        _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
        _data = new char[_capacity];
    }
    std::memset(_data, c, n);
    _data[n] = '\0';
    return *this;
}
/// <summary>
/// ������� ��������� (�������������������).
/// </summary>
/// <param name="str"> - ������ ��� ���������</param>
/// <returns>
/// 1 - ���� �������� ������ ������,
/// -1 - ���� �������� ������ ������,
/// 0 - ���� ������ ���������.
/// </returns>
int CString::compare(const CString& str) const noexcept {
    for (size_t i = 0; i < algorithms::min(_size, str._size); i++) {
        if (this->_data[i] < str._data[i]) {
            return 1;
        }
        else if (this->_data[i] > str._data[i]) {
            return -1;
        }
    }
    if (this->_size > str._size) return 1;
    else if (this->_size < str._size) return -1;
    else return 0;
}

int CString::compare(size_t pos, size_t len, const CString& str) const  {
    // �������� ��������� ������� ������ ��� ���������
    CString substr = this->substr(pos, len);
    return substr.compare(str);
}


int CString::compare(size_t pos, size_t len, const CString& str, size_t subpos, size_t sublen) const  {
    // �������� ��������� ������� ������ ��� ���������
    CString substr = this->substr(pos, len);
    // �������� ��������� ������ str ��� ���������
    CString substr_str = str.substr(subpos, sublen);
    return substr.compare(substr_str);
}


int CString::compare(const char* s) const  {
    return std::strcmp(_data, s);
}


int CString::compare(size_t pos, size_t len, const char* s) const  {
    // �������� ��������� ������� ������ ��� ���������
    CString substr = this->substr(pos, len);
    return substr.compare(s);
}


int CString::compare(size_t pos, size_t len, const char* s, size_t n) const  {
    // �������� ��������� ������� ������ ��� ���������
    CString substr = this->substr(pos, len);
    return substr.compare(CString(s, n));
}
/// <summary>
/// ������� ���������� ������, ����� �� ������.
/// ��� ����������� ���������� ������� ������ � 0.
/// </summary>
void CString::clear() noexcept {
    _size = 0; // ������������� ������ ������ � 0
}
/// <summary>
/// �������� ����� ������ �� �������� ���������� ��������.
/// ���� ����� ����� ������ �������, ��������� ������ 'c' � ����� ������ �� ���������� ����� �����.
/// ���� ����� ����� ������ �������, �������� ������ �� ����� �����.
/// </summary>
/// <param name="n">����� ����� ������.</param>
/// <param name="c">������ ��� ����������, ���� ����� ����� ������ ������� (�� ��������� - ������� ������).</param>
void CString::resize(size_t n, char c /* = '\0' */) {
    if (n == _size) {
        return; // ������ �� ������, ���� ����� ����� ����� �������.
    }
    else if (n < _size) {
        // ���� ����� ����� ������ �������, ������ �������� ������ �� ����� �����.
        _size = n;
        _data[_size] = '\0'; // ������������� ������� ������ � ����� ������.
    }
    else {
        // ���� ����� ����� ������ �������, ����������� ������ ���������, ���� ����������.
        if (n >= _capacity) {
            reserve(n); // ����������� ������ ���������, ���� ����� ����� ������ ������� �������.
        }
        // ��������� ��������� 'c' �������������� �������, ���� ����������.
        for (size_t i = _size; i < n; ++i) {
            _data[i] = c;
        }
        _size = n; // ������������� ����� ������ ������.
        _data[_size] = '\0'; // ������������� ������� ������ � ����� ������.
    }
}
/// <summary>
/// ����������� ������� ��������� �� ��������� �������� ��� �� ��������, ������������ ��� �������� ���������� ���������� ��������.
/// </summary>
/// <param name="n">�������� ������� ��������� (�� ��������� - 0).</param>
void CString::reserve(size_t n /* = 0 */) {
    if (n <= _capacity) {
        return; // ������ �� ������, ���� �������� ������� �� ��������� �������.
    }

    // ��������� ����� �������, �������� ��� ���������� � ������� ����� ������.
    size_t new_capacity = (n / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;

    // �������� ����� ���� ������ � ����������� ��������.
    char* new_data = new char[new_capacity];

    // �������� ������ �� ������� ��������� � �����.
    for (size_t i = 0; i < _size && i < _capacity; ++i) {
        new_data[i] = _data[i];
    }

    // ������� ������ ���������.
    delete[] _data;

    // ��������� ��������� �� ������ � ������� ���������.
    _data = new_data;
    _capacity = new_capacity;
}

/// <summary>
/// ������� ������� � ����� ������.
/// </summary>
/// <param name="c"> - ������ ��� �������</param>
void CString::push_back(char c) {
    if (this->full()) {
        this->reserve(_capacity);
    }

    _data[_size] = c;
    _data[++_size] = '\0';
}

/// <summary>
/// �������� ������� �� ����� ������.
/// <exception cref="std::logic_error">����������, ���� �������� ������ �����.</exception>
/// </summary>
void CString::pop_back() {
    if (this->empty()) {
        throw std::logic_error("Error in function \
                  \"void pop_back()\": source CString is empty");
    }
    _data[--_size] = '\0';
}
/// <summary>
/// ������� ������� ������, ������� � ��������� ������� � ������� �������� �����.
/// </summary>
/// <param name="pos">�������, � ������� ���������� ��������.</param>
/// <param name="len">����� ���������� �������.</param>
/// <returns>������ �� ��������� ������ ����� ��������.</returns>
CString& CString::erase(size_t pos, size_t len) {
    // ���� ��������� ������� ��������� �� ��������� ������ ��� ����� ������� ����� ����, ������ �� ������.
    if (pos >= _size || len == 0) {
        return *this;
    }

    // ���������� �������� ������� ������� (�� ��������� �� ������� ������).
    size_t end_pos = algorithms::min(pos + len, _size);

    // �������� ������� ����� ���������� ������� �� ����� ������ �������.
    for (size_t i = end_pos; i < _size; ++i) {
        _data[pos + i - end_pos] = _data[i];
    }

    // ��������� ����� ������.
    _size -= (end_pos - pos);
    // ��������� ����������� ������� ������ � ����� ����� ������.
    _data[_size] = '\0';

    return *this;
}
/// <summary>
/// ��������� ���������� ������ ������ � ����� ������� ������.
/// </summary>
/// <param name="str">������, ���������� ������� ����� ���������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ���������� �����������.</returns>
CString& CString::append(const CString& str) {
    // ��������� ����� ����� �����.
    size_t total_length = _size + str._size;

    // ���� �� ������� ����� � ��������� ������� ������, ����������� ���.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // �������� ���������� ������ ������ � ����� ������� ������.
    for (size_t i = 0; i < str._size; ++i) {
        _data[_size + i] = str._data[i];
    }

    // ��������� ����� ������� ������.
    _size = total_length;
    // ��������� ����������� ������� ������.
    _data[_size] = '\0';

    return *this;
}
/// <summary>
/// ��������� ��������� ������ ������ � ����� ������� ������.
/// </summary>
/// <param name="str">������, �� ������� ����� ����� ���������.</param>
/// <param name="subpos">������� ������ ��������� � ������ ������.</param>
/// <param name="sublen">����� ���������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ���������� ���������.</returns>
CString& CString::append(const CString& str, size_t subpos, size_t sublen) {
    // ��������� ������������ ��������� ������� ������ ��������� � � �����.
    if (subpos > str._size) {
        throw std::out_of_range("Invalid substring position");
    }
    if (sublen == std::string::npos || sublen > str._size - subpos) {
        sublen = str._size - subpos;
    }

    // ��������� ����� ����� �����.
    size_t total_length = _size + sublen;

    // ���� �� ������� ����� � ��������� ������� ������, ����������� ���.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // �������� ��������� ������ ������ � ����� ������� ������.
    for (size_t i = 0; i < sublen; ++i) {
        _data[_size + i] = str._data[subpos + i];
    }

    // ��������� ����� ������� ������.
    _size = total_length;
    // ��������� ����������� ������� ������.
    _data[_size] = '\0';

    return *this;
}

/// <summary>
/// ��������� ���������� C-������ � ����� ������� ������.
/// </summary>
/// <param name="s">C-������, ���������� ������� ����� ���������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ���������� �����������.</returns>
CString& CString::append(const char* s) {
    // ��������� ���������� C-������ �� ����������.
    if (s == nullptr) {
        throw std::invalid_argument("Null pointer exception");
    }

    // �������� ����� C-������.
    size_t len = strlen(s);

    // ��������� ���������� C-������ � ����� ������� ������.
    return append(s, len);
}

/// <summary>
/// ��������� ������ n �������� C-������ � ����� ������� ������.
/// </summary>
/// <param name="s">C-������, ���������� ������� ����� ���������.</param>
/// <param name="n">���������� �������� ��� ����������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ���������� �����������.</returns>
CString& CString::append(const char* s, size_t n) {
    // ��������� ���������� C-������ �� ����������.
    if (s == nullptr) {
        throw std::invalid_argument("Null pointer exception");
    }

    // ��������� ����� ����� �����.
    size_t total_length = _size + n;

    // ���� �� ������� ����� � ��������� ������� ������, ����������� ���.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // �������� ������ n �������� C-������ � ����� ������� ������.
    for (size_t i = 0; i < n; ++i) {
        _data[_size + i] = s[i];
    }

    // ��������� ����� ������� ������.
    _size = total_length;
    // ��������� ����������� ������� ������.
    _data[_size] = '\0';

    return *this;
}

/// <summary>
/// ��������� n ��������, ������ ������ ������� c, � ����� ������� ������.
/// </summary>
/// <param name="n">���������� �������� ��� ����������.</param>
/// <param name="c">������, ������� ����� �������� � ����� ������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ���������� ��������.</returns>
CString& CString::append(size_t n, char c) {
    // ��������� ����� ����� �����.
    size_t total_length = _size + n;

    // ���� �� ������� ����� � ��������� ������� ������, ����������� ���.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // ��������� ������ c � ����� ������� ������ n ���.
    for (size_t i = 0; i < n; ++i) {
        _data[_size + i] = c;
    }

    // ��������� ����� ������� ������.
    _size = total_length;
    // ��������� ����������� ������� ������.
    _data[_size] = '\0';

    return *this;
}

// ���� ������ ����������
/// <summary>
/// ������� ������ ����� �������� ������� � ��������.
/// </summary>
/// <param name="pos"> - ������� ��� ������� � �������� ������.</param>
/// <param name="str"> - ������ ��� �������</param>
/// <returns>��������� �������� ������</returns>
CString& CString::insert(size_t pos, const CString& str) {
    CString begin(*this, 0, pos);
    CString end(*this, pos, _size - pos);
    begin.append(str);
    begin.append(end);
    this->swap(begin);
    return *this;
}
/// <summary>
/// ��������� ��������� ������ ������ � ������� ������, ������� � ��������� �������.
/// </summary>
/// <param name="pos">������� � ������� ������, � ������� �������� �������.</param>
/// <param name="str">������, �� ������� ����� ����� ���������.</param>
/// <param name="subpos">������� ������ ��������� � ������ ������.</param>
/// <param name="sublen">����� ���������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ������� ���������.</returns>
CString& CString::insert(size_t pos, const CString& str, size_t subpos, size_t sublen) {
    // ��������� ������������ ��������� ������� �������.
    if (pos > _size) {
        throw std::out_of_range("Invalid insert position");
    }

    // ��������� ������������ ��������� ������� ������ ��������� � � �����.
    if (subpos > str._size) {
        throw std::out_of_range("Invalid substring position");
    }
    if (sublen == std::string::npos || sublen > str._size - subpos) {
        sublen = str._size - subpos;
    }

    // ��������� ����� ����� �����.
    size_t total_length = _size + sublen;

    // ���� �� ������� ����� � ��������� ������� ������, ����������� ���.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // �������� ����� ������, ������� � ������� �������, �� ����� ����������� ���������.
    for (size_t i = _size; i >= pos; --i) {
        _data[i + sublen] = _data[i];
    }

    // ��������� ��������� ������ ������ � ������� ������.
    for (size_t i = 0; i < sublen; ++i) {
        _data[pos + i] = str._data[subpos + i];
    }

    // ��������� ����� ������� ������.
    _size = total_length;
    // ��������� ����������� ������� ������.
    _data[_size] = '\0';

    return *this;
}

/// <summary>
/// ��������� ���������� C-������ � ������� ������, ������� � ��������� �������.
/// </summary>
/// <param name="pos">������� � ������� ������, � ������� �������� �������.</param>
/// <param name="s">C-������, ���������� ������� ����� ���������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ������� �����������.</returns>
CString& CString::insert(size_t pos, const char* s) {
    // ��������� ���������� C-������ �� ����������.
    if (s == nullptr) {
        throw std::invalid_argument("Null pointer exception");
    }

    // ��������� ���������� C-������ � ������� ������, ������� � ��������� �������.
    return insert(pos, s, strlen(s));
}

/// <summary>
/// ��������� ������ n �������� C-������ � ������� ������, ������� � ��������� �������.
/// </summary>
/// <param name="pos">������� � ������� ������, � ������� �������� �������.</param>
/// <param name="s">C-������, ���������� ������� ����� ���������.</param>
/// <param name="n">���������� �������� ��� �������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ������� �����������.</returns>
CString& CString::insert(size_t pos, const char* s, size_t n) {
    // ��������� ���������� C-������ �� ����������.
    if (s == nullptr) {
        throw std::invalid_argument("Null pointer exception");
    }

    // ��������� ����� ����� �����.
    size_t total_length = _size + n;

    // ���� �� ������� ����� � ��������� ������� ������, ����������� ���.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // �������� ����� ������, ������� � ������� �������, �� ����� ����������� ���������.
    for (size_t i = _size; i >= pos; --i) {
        _data[i + n] = _data[i];
    }

    // ��������� ������ n �������� C-������ � ������� ������.
    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = s[i];
    }

    // ��������� ����� ������� ������.
    _size = total_length;
    // ��������� ����������� ������� ������.
    _data[_size] = '\0';

    return *this;
}

/// <summary>
/// ��������� n ��������, ������ ������ ������� c, � ������� ������, ������� � ��������� �������.
/// </summary>
/// <param name="pos">������� � ������� ������, � ������� �������� �������.</param>
/// <param name="n">���������� �������� ��� �������.</param>
/// <param name="c">������, ������� ����� �������� � ������� ������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ������� ��������.</returns>
CString& CString::insert(size_t pos, size_t n, char c) {
    // ��������� ����� ����� �����.
    size_t total_length = _size + n;

    // ���� �� ������� ����� � ��������� ������� ������, ����������� ���.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // �������� ����� ������, ������� � ������� �������, �� ���������� ����������� ��������.
    for (size_t i = _size; i >= pos; --i) {
        _data[i + n] = _data[i];
    }

    // ��������� ������ c � ������� ������ n ���, ������� � ��������� �������.
    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = c;
    }

    // ��������� ����� ������� ������.
    _size = total_length;
    // ��������� ����������� ������� ������.
    _data[_size] = '\0';

    return *this;
}
/// <summary>
/// �������� ������� ������, ������� � ��������� �������, ������� str.
/// </summary>
/// <param name="pos">������� � ������� ������, � ������� �������� ������.</param>
/// <param name="len">����� �������, ������� ����� �������.</param>
/// <param name="str">������, ������� ����� ��������� ������ ���������� �������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ������.</returns>
CString& CString::replace(size_t pos, size_t len, const CString& str) {
    return replace(pos, len, str.data(), str.size());
}

/// <summary>
/// �������� ������� ������, ������� � ��������� �������, ���������� str.
/// </summary>
/// <param name="pos">������� � ������� ������, � ������� �������� ������.</param>
/// <param name="len">����� �������, ������� ����� �������.</param>
/// <param name="str">������, �� ������� ����� ����� ��������� ��� ������.</param>
/// <param name="subpos">������� ������ ��������� � ������ str.</param>
/// <param name="sublen">����� ���������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ������.</returns>
CString& CString::replace(size_t pos, size_t len, const CString& str, size_t subpos, size_t sublen) {
    // ��������� ���������� ��������� �� ����������.
    if (subpos > str.size()) {
        throw std::out_of_range("Invalid substring position");
    }
    if (sublen == CString::npos || sublen > str.size() - subpos) {
        sublen = str.size() - subpos;
    }
    return replace(pos, len, str.data() + subpos, sublen);
}

/// <summary>
/// �������� ������� ������, ������� � ��������� �������, ���������� C-������ s.
/// </summary>
/// <param name="pos">������� � ������� ������, � ������� �������� ������.</param>
/// <param name="len">����� �������, ������� ����� �������.</param>
/// <param name="s">C-������, ���������� ������� ������� ��������� �������.</param>
/// <param name="n">���������� �������� C-������, ������� ����� ������������ ��� ������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ������.</returns>
CString& CString::replace(size_t pos, size_t len, const char* s, size_t n) {
    // ��������� ���������� ��������� �� ����������.
    if (s == nullptr) {
        throw std::invalid_argument("Null pointer exception");
    }
    return replace(pos, len, CString(s, n));
}

/// <summary>
/// �������� ������� ������, ������� � ��������� �������, n ��������� c.
/// </summary>
/// <param name="pos">������� � ������� ������, � ������� �������� ������.</param>
/// <param name="len">����� �������, ������� ����� �������.</param>
/// <param name="n">���������� ��������, �������� ����� ������� ��������� �������.</param>
/// <param name="c">������, ������� ����� �������� ��������� �������.</param>
/// <returns>������ �� ��������� ������� ������ ����� ������.</returns>
CString& CString::replace(size_t pos, size_t len, size_t n, char c) {
    // �������� ��������� ������� n ��������� c ����� �������� � ����������� �������.
    erase(pos, len);
    insert(pos, n, c);
    return *this;
}
/// <summary>
/// ������� ������ ��������� ������ str � ������� ������, ������� � ������� pos.
/// </summary>
/// <param name="str">������, ������� ����� �����.</param>
/// <param name="pos">�������, � ������� �������� �����.</param>
/// <returns>������� ������� ������� ��������� ������, ���� ��� �������; CString::npos, ���� ������ �� �������.</returns>
size_t CString::find(const CString& str, size_t pos) const {
    if (pos > _size) {
        return npos;
    }
    const char* found = std::strstr(_data + pos, str.data());
    return found ? found - _data : npos;
}

/// <summary>
/// ������� ������ ��������� C-������ s � ������� ������, ������� � ������� pos.
/// </summary>
/// <param name="s">C-������, ������� ����� �����.</param>
/// <param name="pos">�������, � ������� �������� �����.</param>
/// <returns>������� ������� ������� ��������� ������, ���� ��� �������; CString::npos, ���� ������ �� �������.</returns>
size_t CString::find(const char* s, size_t pos) const {
    if (s == nullptr || pos > _size) {
        return npos;
    }
    const char* found = std::strstr(_data + pos, s);
    return found ? found - _data : npos;
}

/// <summary>
/// ������� ������ ��������� n �������� C-������ s � ������� ������, ������� � ������� pos.
/// </summary>
/// <param name="s">C-������, ������� ����� �����.</param>
/// <param name="pos">�������, � ������� �������� �����.</param>
/// <param name="n">���������� �������� ��� ������.</param>
/// <returns>������� ������� ������� ��������� ������, ���� ��� �������; CString::npos, ���� ������ �� �������.</returns>
size_t CString::find(const char* s, size_t pos, size_t n) const {
    if (s == nullptr || pos > _size) {
        return npos;
    }

    for (size_t i = pos; i <= _size - n; ++i) {
        bool found = true;
        for (size_t j = 0; j < n; ++j) {
            if (_data[i + j] != s[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }

    return npos;
}

/// <summary>
/// ������� ������ ��������� ������� c � ������� ������, ������� � ������� pos.
/// </summary>
/// <param name="c">������, ������� ����� �����.</param>
/// <param name="pos">�������, � ������� �������� �����.</param>
/// <returns>������� ���������� �������, ���� �� ������; CString::npos, ���� ������ �� ������.</returns>
size_t CString::find(char c, size_t pos) const {
    if (pos >= _size) {
        return npos;
    }
    const char* found = std::find(_data + pos, _data + _size, c);
    return found != _data + _size ? found - _data : npos;
}

/// <summary>
/// ����� ������� ���������� � �������� ������ � ����� �� �������� �������� ������.
/// </summary>
/// <param name="str"> - ����� �������� ��� ������</param>
/// <param name="pos"> - �������, � ������� ������� �������� �����</param>
/// <returns></returns>
size_t CString::find_first_of(const CString& str, size_t pos) const {
    for (size_t i = pos; i < _size; i++) {
        for (size_t j = 0; j < str._size; j++) {
            if (_data[i] == str._data[j]) {
                return i;
            }
        }
    }
    return -1;
}

/// <summary>
/// ������� ������ ��������� ������ �� �������� C-������ s � ������� ������, ������� � ������� pos.
/// </summary>
/// <param name="s">C-������, ���������� ������� ��� ������.</param>
/// <param name="pos">�������, � ������� �������� �����.</param>
/// <returns>������� ������� ���������� �������, ���� �� ������; CString::npos, ���� ������ �� ������.</returns>
size_t CString::find_first_of(const char* s, size_t pos) const {
    if (s == nullptr || pos >= _size) {
        return npos;
    }
    for (size_t i = pos; i < _size; i++) {
        for (size_t j = 0; s[j] != '\0'; j++) {
            if (_data[i] == s[j]) {
                return i;
            }
        }
    }
    return npos;
}
/// <summary>
/// ������� ������ ��������� ������ �� ������ n �������� C-������ s � ������� ������, ������� � ������� pos.
/// </summary>
/// <param name="s">C-������, ���������� ������� ��� ������.</param>
/// <param name="pos">�������, � ������� �������� �����.</param>
/// <param name="n">���������� �������� ��� ������.</param>
/// <returns>������� ������� ���������� �������, ���� �� ������; CString::npos, ���� ������ �� ������.</returns>
size_t CString::find_first_of(const char* s, size_t pos, size_t n) const {
    if (s == nullptr || pos >= _size) {
        return npos;
    }
    for (size_t i = pos; i < _size; i++) {
        for (size_t j = 0; j < n; j++) {
            if (_data[i] == s[j]) {
                return i;
            }
        }
    }
    return npos;
}

/// <summary>
/// ������� ������ ��������� ������� c � ������� ������, ������� � ������� pos.
/// </summary>
/// <param name="c">������, ������� ����� �����.</param>
/// <param name="pos">�������, � ������� �������� �����.</param>
/// <returns>������� ���������� �������, ���� �� ������; CString::npos, ���� ������ �� ������.</returns>
size_t CString::find_first_of(char c, size_t pos) const {
    if (pos >= _size) {
        return npos;
    }
    const char* found = std::find(_data + pos, _data + _size, c);
    return found != _data + _size ? found - _data : npos;
}
/// <summary>
/// ������� ������ ��������� ������ �������, �� �������������� ������ str, � ������� ������, ������� � ������� pos.
/// </summary>
/// <param name="str">������, ������� ������� ����� ��������� �� ������.</param>
/// <param name="pos">�������, � ������� �������� �����.</param>
/// <returns>������� ������� ���������� �������, �� �������������� ������ str, ���� ������; CString::npos, ���� ����� ������ �� ������.</returns>
size_t CString::find_first_not_of(const CString& str, size_t pos) const {
    for (size_t i = pos; i < _size; ++i) {
        if (str.find(_data[i]) == CString::npos) {
            return i;
        }
    }
    return npos;
}

/// <summary>
/// ������� ������ ��������� ������ �������, �� �������������� C-������ s, � ������� ������, ������� � ������� pos.
/// </summary>
/// <param name="s">C-������, ������� ������� ����� ��������� �� ������.</param>
/// <param name="pos">�������, � ������� �������� �����.</param>
/// <returns>������� ������� ���������� �������, �� �������������� C-������ s, ���� ������; CString::npos, ���� ����� ������ �� ������.</returns>
size_t CString::find_first_not_of(const char* s, size_t pos) const {
    if (s == nullptr) {
        return npos;
    }
    for (size_t i = pos; i < _size; ++i) {
        if (std::strchr(s, _data[i]) == nullptr) {
            return i;
        }
    }
    return npos;
}

/// <summary>
/// ������� ������ ��������� ������ �������, �� �������������� ������ n �������� C-������ s, � ������� ������, ������� � ������� pos.
/// </summary>
/// <param name="s">C-������, ������� ������� ����� ��������� �� ������.</param>
/// <param name="pos">�������, � ������� �������� �����.</param>
/// <param name="n">���������� �������� ��� ���������� �� ������.</param>
/// <returns>������� ������� ���������� �������, �� �������������� ������ n �������� C-������ s, ���� ������; CString::npos, ���� ����� ������ �� ������.</returns>
size_t CString::find_first_not_of(const char* s, size_t pos, size_t n) const {
    if (s == nullptr) {
        return npos;
    }
    for (size_t i = pos; i < _size; ++i) {
        if (std::memchr(s, _data[i], n) == nullptr) {
            return i;
        }
    }
    return npos;
}

/// <summary>
/// ������� ������ ��������� ������ �������, ��������� �� ������� c, � ������� ������, ������� � ������� pos.
/// </summary>
/// <param name="c">������, ������� ����� ��������� �� ������.</param>
/// <param name="pos">�������, � ������� �������� �����.</param>
/// <returns>������� ������� ���������� �������, ��������� �� ������� c, ���� ������; CString::npos, ���� ����� ������ �� ������.</returns>
size_t CString::find_first_not_of(char c, size_t pos) const {
    for (size_t i = pos; i < _size; ++i) {
        if (_data[i] != c) {
            return i;
        }
    }
    return npos;
}