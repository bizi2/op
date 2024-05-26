#include "string.h"

/// <summary>
/// Конструктор по умолчанию.
/// </summary>
CString::CString() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new char[_capacity];
    _data[0] = '\0';
}

/// <summary>
/// Конструктор копирования.
/// </summary>
/// <param name="str"> - копируемая строка</param>
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
///  Конструктор из части const char*
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
/// Деструктор.
/// </summary>
CString::~CString() {
    delete[] _data;
    _data = nullptr;
}

/// <summary>
/// Проверка строки на пустоту.
/// </summary>
/// <returns>
/// true - если строка пуста,
/// false - иначе.
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
/// Геттер для размера строки.
/// </summary>
/// <returns>размер (длина) строки</returns>
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
    // Проверка на корректность начальной позиции и длины
    if (pos > _size) {
        throw std::out_of_range("Starting position is out of range.");
    }
    if (len == CString::npos || pos + len > _size) {
        len = _size - pos;
    }

    // Создание подстроки
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
    // Проверка на корректность начальной позиции и длины
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
/// Функция сравнения (лексикографического).
/// </summary>
/// <param name="str"> - строка для сравнения</param>
/// <returns>
/// 1 - если исходная строка больше,
/// -1 - если исходная строка меньше,
/// 0 - если строки совпадают.
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
    // Получаем подстроку текущей строки для сравнения
    CString substr = this->substr(pos, len);
    return substr.compare(str);
}


int CString::compare(size_t pos, size_t len, const CString& str, size_t subpos, size_t sublen) const  {
    // Получаем подстроку текущей строки для сравнения
    CString substr = this->substr(pos, len);
    // Получаем подстроку строки str для сравнения
    CString substr_str = str.substr(subpos, sublen);
    return substr.compare(substr_str);
}


int CString::compare(const char* s) const  {
    return std::strcmp(_data, s);
}


int CString::compare(size_t pos, size_t len, const char* s) const  {
    // Получаем подстроку текущей строки для сравнения
    CString substr = this->substr(pos, len);
    return substr.compare(s);
}


int CString::compare(size_t pos, size_t len, const char* s, size_t n) const  {
    // Получаем подстроку текущей строки для сравнения
    CString substr = this->substr(pos, len);
    return substr.compare(CString(s, n));
}
/// <summary>
/// Очищает содержимое строки, делая ее пустой.
/// Это достигается установкой размера строки в 0.
/// </summary>
void CString::clear() noexcept {
    _size = 0; // Устанавливаем размер строки в 0
}
/// <summary>
/// Изменяет длину строки на заданное количество символов.
/// Если новая длина больше текущей, добавляет символ 'c' в конец строки до достижения новой длины.
/// Если новая длина меньше текущей, обрезает строку до новой длины.
/// </summary>
/// <param name="n">Новая длина строки.</param>
/// <param name="c">Символ для заполнения, если новая длина больше текущей (по умолчанию - нулевой символ).</param>
void CString::resize(size_t n, char c /* = '\0' */) {
    if (n == _size) {
        return; // Ничего не делаем, если новая длина равна текущей.
    }
    else if (n < _size) {
        // Если новая длина меньше текущей, просто обрезаем строку до новой длины.
        _size = n;
        _data[_size] = '\0'; // Устанавливаем нулевой символ в конец строки.
    }
    else {
        // Если новая длина больше текущей, увеличиваем размер хранилища, если необходимо.
        if (n >= _capacity) {
            reserve(n); // Увеличиваем размер хранилища, если новая длина больше текущей ёмкости.
        }
        // Заполняем символами 'c' дополнительные позиции, если необходимо.
        for (size_t i = _size; i < n; ++i) {
            _data[i] = c;
        }
        _size = n; // Устанавливаем новый размер строки.
        _data[_size] = '\0'; // Устанавливаем нулевой символ в конец строки.
    }
}
/// <summary>
/// Увеличивает ёмкость хранилища до заданного значения или до значения, достаточного для хранения указанного количества символов.
/// </summary>
/// <param name="n">Желаемая ёмкость хранилища (по умолчанию - 0).</param>
void CString::reserve(size_t n /* = 0 */) {
    if (n <= _capacity) {
        return; // Ничего не делаем, если желаемая ёмкость не превышает текущую.
    }

    // Вычисляем новую ёмкость, учитывая шаг увеличения и текущую длину строки.
    size_t new_capacity = (n / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;

    // Выделяем новый блок памяти с увеличенной ёмкостью.
    char* new_data = new char[new_capacity];

    // Копируем данные из старого хранилища в новое.
    for (size_t i = 0; i < _size && i < _capacity; ++i) {
        new_data[i] = _data[i];
    }

    // Удаляем старое хранилище.
    delete[] _data;

    // Обновляем указатель на данные и ёмкость хранилища.
    _data = new_data;
    _capacity = new_capacity;
}

/// <summary>
/// Вставка символа в конец строки.
/// </summary>
/// <param name="c"> - символ для вставки</param>
void CString::push_back(char c) {
    if (this->full()) {
        this->reserve(_capacity);
    }

    _data[_size] = c;
    _data[++_size] = '\0';
}

/// <summary>
/// Удаление символа из конца строки.
/// <exception cref="std::logic_error">Исключение, если исходная строка пуста.</exception>
/// </summary>
void CString::pop_back() {
    if (this->empty()) {
        throw std::logic_error("Error in function \
                  \"void pop_back()\": source CString is empty");
    }
    _data[--_size] = '\0';
}
/// <summary>
/// Удаляет участок строки, начиная с указанной позиции и имеющий заданную длину.
/// </summary>
/// <param name="pos">Позиция, с которой начинается удаление.</param>
/// <param name="len">Длина удаляемого участка.</param>
/// <returns>Ссылка на изменённую строку после удаления.</returns>
CString& CString::erase(size_t pos, size_t len) {
    // Если начальная позиция находится за пределами строки или длина участка равна нулю, ничего не делаем.
    if (pos >= _size || len == 0) {
        return *this;
    }

    // Определяем конечную позицию участка (не выходящую за пределы строки).
    size_t end_pos = algorithms::min(pos + len, _size);

    // Сдвигаем символы после удаляемого участка на место начала участка.
    for (size_t i = end_pos; i < _size; ++i) {
        _data[pos + i - end_pos] = _data[i];
    }

    // Обновляем длину строки.
    _size -= (end_pos - pos);
    // Добавляем завершающий нулевой символ в новом конце строки.
    _data[_size] = '\0';

    return *this;
}
/// <summary>
/// Добавляет содержимое другой строки в конец текущей строки.
/// </summary>
/// <param name="str">Строка, содержимое которой будет добавлено.</param>
/// <returns>Ссылка на изменённую текущую строку после добавления содержимого.</returns>
CString& CString::append(const CString& str) {
    // Вычисляем общую длину строк.
    size_t total_length = _size + str._size;

    // Если не хватает места в хранилище текущей строки, увеличиваем его.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // Копируем содержимое другой строки в конец текущей строки.
    for (size_t i = 0; i < str._size; ++i) {
        _data[_size + i] = str._data[i];
    }

    // Обновляем длину текущей строки.
    _size = total_length;
    // Добавляем завершающий нулевой символ.
    _data[_size] = '\0';

    return *this;
}
/// <summary>
/// Добавляет подстроку другой строки в конец текущей строки.
/// </summary>
/// <param name="str">Строка, из которой будет взята подстрока.</param>
/// <param name="subpos">Позиция начала подстроки в другой строке.</param>
/// <param name="sublen">Длина подстроки.</param>
/// <returns>Ссылка на изменённую текущую строку после добавления подстроки.</returns>
CString& CString::append(const CString& str, size_t subpos, size_t sublen) {
    // Проверяем корректность указанной позиции начала подстроки и её длины.
    if (subpos > str._size) {
        throw std::out_of_range("Invalid substring position");
    }
    if (sublen == std::string::npos || sublen > str._size - subpos) {
        sublen = str._size - subpos;
    }

    // Вычисляем общую длину строк.
    size_t total_length = _size + sublen;

    // Если не хватает места в хранилище текущей строки, увеличиваем его.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // Копируем подстроку другой строки в конец текущей строки.
    for (size_t i = 0; i < sublen; ++i) {
        _data[_size + i] = str._data[subpos + i];
    }

    // Обновляем длину текущей строки.
    _size = total_length;
    // Добавляем завершающий нулевой символ.
    _data[_size] = '\0';

    return *this;
}

/// <summary>
/// Добавляет содержимое C-строки в конец текущей строки.
/// </summary>
/// <param name="s">C-строка, содержимое которой будет добавлено.</param>
/// <returns>Ссылка на изменённую текущую строку после добавления содержимого.</returns>
CString& CString::append(const char* s) {
    // Проверяем переданную C-строку на валидность.
    if (s == nullptr) {
        throw std::invalid_argument("Null pointer exception");
    }

    // Получаем длину C-строки.
    size_t len = strlen(s);

    // Добавляем содержимое C-строки в конец текущей строки.
    return append(s, len);
}

/// <summary>
/// Добавляет первые n символов C-строки в конец текущей строки.
/// </summary>
/// <param name="s">C-строка, содержимое которой будет добавлено.</param>
/// <param name="n">Количество символов для добавления.</param>
/// <returns>Ссылка на изменённую текущую строку после добавления содержимого.</returns>
CString& CString::append(const char* s, size_t n) {
    // Проверяем переданную C-строку на валидность.
    if (s == nullptr) {
        throw std::invalid_argument("Null pointer exception");
    }

    // Вычисляем общую длину строк.
    size_t total_length = _size + n;

    // Если не хватает места в хранилище текущей строки, увеличиваем его.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // Копируем первые n символов C-строки в конец текущей строки.
    for (size_t i = 0; i < n; ++i) {
        _data[_size + i] = s[i];
    }

    // Обновляем длину текущей строки.
    _size = total_length;
    // Добавляем завершающий нулевой символ.
    _data[_size] = '\0';

    return *this;
}

/// <summary>
/// Добавляет n символов, каждый равный символу c, в конец текущей строки.
/// </summary>
/// <param name="n">Количество символов для добавления.</param>
/// <param name="c">Символ, который будет добавлен в конец строки.</param>
/// <returns>Ссылка на изменённую текущую строку после добавления символов.</returns>
CString& CString::append(size_t n, char c) {
    // Вычисляем общую длину строк.
    size_t total_length = _size + n;

    // Если не хватает места в хранилище текущей строки, увеличиваем его.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // Добавляем символ c в конец текущей строки n раз.
    for (size_t i = 0; i < n; ++i) {
        _data[_size + i] = c;
    }

    // Обновляем длину текущей строки.
    _size = total_length;
    // Добавляем завершающий нулевой символ.
    _data[_size] = '\0';

    return *this;
}

// лишь пример реализации
/// <summary>
/// Вставка строки после заданной позиции в исходной.
/// </summary>
/// <param name="pos"> - позиция для вставки в исходной строке.</param>
/// <param name="str"> - строка для вставки</param>
/// <returns>изменённая исходная строка</returns>
CString& CString::insert(size_t pos, const CString& str) {
    CString begin(*this, 0, pos);
    CString end(*this, pos, _size - pos);
    begin.append(str);
    begin.append(end);
    this->swap(begin);
    return *this;
}
/// <summary>
/// Вставляет подстроку другой строки в текущую строку, начиная с указанной позиции.
/// </summary>
/// <param name="pos">Позиция в текущей строке, с которой начнется вставка.</param>
/// <param name="str">Строка, из которой будет взята подстрока.</param>
/// <param name="subpos">Позиция начала подстроки в другой строке.</param>
/// <param name="sublen">Длина подстроки.</param>
/// <returns>Ссылка на изменённую текущую строку после вставки подстроки.</returns>
CString& CString::insert(size_t pos, const CString& str, size_t subpos, size_t sublen) {
    // Проверяем корректность указанной позиции вставки.
    if (pos > _size) {
        throw std::out_of_range("Invalid insert position");
    }

    // Проверяем корректность указанной позиции начала подстроки и её длины.
    if (subpos > str._size) {
        throw std::out_of_range("Invalid substring position");
    }
    if (sublen == std::string::npos || sublen > str._size - subpos) {
        sublen = str._size - subpos;
    }

    // Вычисляем общую длину строк.
    size_t total_length = _size + sublen;

    // Если не хватает места в хранилище текущей строки, увеличиваем его.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // Сдвигаем часть строки, начиная с позиции вставки, на длину вставляемой подстроки.
    for (size_t i = _size; i >= pos; --i) {
        _data[i + sublen] = _data[i];
    }

    // Вставляем подстроку другой строки в текущую строку.
    for (size_t i = 0; i < sublen; ++i) {
        _data[pos + i] = str._data[subpos + i];
    }

    // Обновляем длину текущей строки.
    _size = total_length;
    // Добавляем завершающий нулевой символ.
    _data[_size] = '\0';

    return *this;
}

/// <summary>
/// Вставляет содержимое C-строки в текущую строку, начиная с указанной позиции.
/// </summary>
/// <param name="pos">Позиция в текущей строке, с которой начнется вставка.</param>
/// <param name="s">C-строка, содержимое которой будет вставлено.</param>
/// <returns>Ссылка на изменённую текущую строку после вставки содержимого.</returns>
CString& CString::insert(size_t pos, const char* s) {
    // Проверяем переданную C-строку на валидность.
    if (s == nullptr) {
        throw std::invalid_argument("Null pointer exception");
    }

    // Вставляем содержимое C-строки в текущую строку, начиная с указанной позиции.
    return insert(pos, s, strlen(s));
}

/// <summary>
/// Вставляет первые n символов C-строки в текущую строку, начиная с указанной позиции.
/// </summary>
/// <param name="pos">Позиция в текущей строке, с которой начнется вставка.</param>
/// <param name="s">C-строка, содержимое которой будет вставлено.</param>
/// <param name="n">Количество символов для вставки.</param>
/// <returns>Ссылка на изменённую текущую строку после вставки содержимого.</returns>
CString& CString::insert(size_t pos, const char* s, size_t n) {
    // Проверяем переданную C-строку на валидность.
    if (s == nullptr) {
        throw std::invalid_argument("Null pointer exception");
    }

    // Вычисляем общую длину строк.
    size_t total_length = _size + n;

    // Если не хватает места в хранилище текущей строки, увеличиваем его.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // Сдвигаем часть строки, начиная с позиции вставки, на длину вставляемой подстроки.
    for (size_t i = _size; i >= pos; --i) {
        _data[i + n] = _data[i];
    }

    // Вставляем первые n символов C-строки в текущую строку.
    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = s[i];
    }

    // Обновляем длину текущей строки.
    _size = total_length;
    // Добавляем завершающий нулевой символ.
    _data[_size] = '\0';

    return *this;
}

/// <summary>
/// Вставляет n символов, каждый равный символу c, в текущую строку, начиная с указанной позиции.
/// </summary>
/// <param name="pos">Позиция в текущей строке, с которой начнется вставка.</param>
/// <param name="n">Количество символов для вставки.</param>
/// <param name="c">Символ, который будет вставлен в текущую строку.</param>
/// <returns>Ссылка на изменённую текущую строку после вставки символов.</returns>
CString& CString::insert(size_t pos, size_t n, char c) {
    // Вычисляем общую длину строк.
    size_t total_length = _size + n;

    // Если не хватает места в хранилище текущей строки, увеличиваем его.
    if (total_length >= _capacity) {
        reserve(total_length);
    }

    // Сдвигаем часть строки, начиная с позиции вставки, на количество вставляемых символов.
    for (size_t i = _size; i >= pos; --i) {
        _data[i + n] = _data[i];
    }

    // Вставляем символ c в текущую строку n раз, начиная с указанной позиции.
    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = c;
    }

    // Обновляем длину текущей строки.
    _size = total_length;
    // Добавляем завершающий нулевой символ.
    _data[_size] = '\0';

    return *this;
}
/// <summary>
/// Заменяет участок строки, начиная с указанной позиции, строкой str.
/// </summary>
/// <param name="pos">Позиция в текущей строке, с которой начнется замена.</param>
/// <param name="len">Длина участка, который будет заменен.</param>
/// <param name="str">Строка, которая будет вставлена вместо указанного участка.</param>
/// <returns>Ссылка на изменённую текущую строку после замены.</returns>
CString& CString::replace(size_t pos, size_t len, const CString& str) {
    return replace(pos, len, str.data(), str.size());
}

/// <summary>
/// Заменяет участок строки, начиная с указанной позиции, подстрокой str.
/// </summary>
/// <param name="pos">Позиция в текущей строке, с которой начнется замена.</param>
/// <param name="len">Длина участка, который будет заменен.</param>
/// <param name="str">Строка, из которой будет взята подстрока для замены.</param>
/// <param name="subpos">Позиция начала подстроки в строке str.</param>
/// <param name="sublen">Длина подстроки.</param>
/// <returns>Ссылка на изменённую текущую строку после замены.</returns>
CString& CString::replace(size_t pos, size_t len, const CString& str, size_t subpos, size_t sublen) {
    // Проверяем переданные параметры на валидность.
    if (subpos > str.size()) {
        throw std::out_of_range("Invalid substring position");
    }
    if (sublen == CString::npos || sublen > str.size() - subpos) {
        sublen = str.size() - subpos;
    }
    return replace(pos, len, str.data() + subpos, sublen);
}

/// <summary>
/// Заменяет участок строки, начиная с указанной позиции, содержимым C-строки s.
/// </summary>
/// <param name="pos">Позиция в текущей строке, с которой начнется замена.</param>
/// <param name="len">Длина участка, который будет заменен.</param>
/// <param name="s">C-строка, содержимое которой заменит указанный участок.</param>
/// <param name="n">Количество символов C-строки, которые будут использованы для замены.</param>
/// <returns>Ссылка на изменённую текущую строку после замены.</returns>
CString& CString::replace(size_t pos, size_t len, const char* s, size_t n) {
    // Проверяем переданные параметры на валидность.
    if (s == nullptr) {
        throw std::invalid_argument("Null pointer exception");
    }
    return replace(pos, len, CString(s, n));
}

/// <summary>
/// Заменяет участок строки, начиная с указанной позиции, n символами c.
/// </summary>
/// <param name="pos">Позиция в текущей строке, с которой начнется замена.</param>
/// <param name="len">Длина участка, который будет заменен.</param>
/// <param name="n">Количество символов, которыми будет заменен указанный участок.</param>
/// <param name="c">Символ, которым будет заполнен указанный участок.</param>
/// <returns>Ссылка на изменённую текущую строку после замены.</returns>
CString& CString::replace(size_t pos, size_t len, size_t n, char c) {
    // Заменяем указанный участок n символами c путем удаления и последующей вставки.
    erase(pos, len);
    insert(pos, n, c);
    return *this;
}
/// <summary>
/// Находит первое вхождение строки str в текущую строку, начиная с позиции pos.
/// </summary>
/// <param name="str">Строка, которую нужно найти.</param>
/// <param name="pos">Позиция, с которой начнется поиск.</param>
/// <returns>Позиция первого символа найденной строки, если она найдена; CString::npos, если строка не найдена.</returns>
size_t CString::find(const CString& str, size_t pos) const {
    if (pos > _size) {
        return npos;
    }
    const char* found = std::strstr(_data + pos, str.data());
    return found ? found - _data : npos;
}

/// <summary>
/// Находит первое вхождение C-строки s в текущую строку, начиная с позиции pos.
/// </summary>
/// <param name="s">C-строка, которую нужно найти.</param>
/// <param name="pos">Позиция, с которой начнется поиск.</param>
/// <returns>Позиция первого символа найденной строки, если она найдена; CString::npos, если строка не найдена.</returns>
size_t CString::find(const char* s, size_t pos) const {
    if (s == nullptr || pos > _size) {
        return npos;
    }
    const char* found = std::strstr(_data + pos, s);
    return found ? found - _data : npos;
}

/// <summary>
/// Находит первое вхождение n символов C-строки s в текущую строку, начиная с позиции pos.
/// </summary>
/// <param name="s">C-строка, которую нужно найти.</param>
/// <param name="pos">Позиция, с которой начнется поиск.</param>
/// <param name="n">Количество символов для поиска.</param>
/// <returns>Позиция первого символа найденной строки, если она найдена; CString::npos, если строка не найдена.</returns>
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
/// Находит первое вхождение символа c в текущую строку, начиная с позиции pos.
/// </summary>
/// <param name="c">Символ, который нужно найти.</param>
/// <param name="pos">Позиция, с которой начнется поиск.</param>
/// <returns>Позиция найденного символа, если он найден; CString::npos, если символ не найден.</returns>
size_t CString::find(char c, size_t pos) const {
    if (pos >= _size) {
        return npos;
    }
    const char* found = std::find(_data + pos, _data + _size, c);
    return found != _data + _size ? found - _data : npos;
}

/// <summary>
/// Поиск первого совпадения в исходной строке с одним из символов заданной строки.
/// </summary>
/// <param name="str"> - набор символов для поиска</param>
/// <param name="pos"> - позиция, с которой следует начинать поиск</param>
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
/// Находит первое вхождение любого из символов C-строки s в текущую строку, начиная с позиции pos.
/// </summary>
/// <param name="s">C-строка, содержащая символы для поиска.</param>
/// <param name="pos">Позиция, с которой начнется поиск.</param>
/// <returns>Позиция первого найденного символа, если он найден; CString::npos, если символ не найден.</returns>
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
/// Находит первое вхождение любого из первых n символов C-строки s в текущую строку, начиная с позиции pos.
/// </summary>
/// <param name="s">C-строка, содержащая символы для поиска.</param>
/// <param name="pos">Позиция, с которой начнется поиск.</param>
/// <param name="n">Количество символов для поиска.</param>
/// <returns>Позиция первого найденного символа, если он найден; CString::npos, если символ не найден.</returns>
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
/// Находит первое вхождение символа c в текущую строку, начиная с позиции pos.
/// </summary>
/// <param name="c">Символ, который нужно найти.</param>
/// <param name="pos">Позиция, с которой начнется поиск.</param>
/// <returns>Позиция найденного символа, если он найден; CString::npos, если символ не найден.</returns>
size_t CString::find_first_of(char c, size_t pos) const {
    if (pos >= _size) {
        return npos;
    }
    const char* found = std::find(_data + pos, _data + _size, c);
    return found != _data + _size ? found - _data : npos;
}
/// <summary>
/// Находит первое вхождение любого символа, не принадлежащего строке str, в текущую строку, начиная с позиции pos.
/// </summary>
/// <param name="str">Строка, символы которой нужно исключить из поиска.</param>
/// <param name="pos">Позиция, с которой начнется поиск.</param>
/// <returns>Позиция первого найденного символа, не принадлежащего строке str, если найден; CString::npos, если такой символ не найден.</returns>
size_t CString::find_first_not_of(const CString& str, size_t pos) const {
    for (size_t i = pos; i < _size; ++i) {
        if (str.find(_data[i]) == CString::npos) {
            return i;
        }
    }
    return npos;
}

/// <summary>
/// Находит первое вхождение любого символа, не принадлежащего C-строке s, в текущую строку, начиная с позиции pos.
/// </summary>
/// <param name="s">C-строка, символы которой нужно исключить из поиска.</param>
/// <param name="pos">Позиция, с которой начнется поиск.</param>
/// <returns>Позиция первого найденного символа, не принадлежащего C-строке s, если найден; CString::npos, если такой символ не найден.</returns>
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
/// Находит первое вхождение любого символа, не принадлежащего первым n символам C-строки s, в текущую строку, начиная с позиции pos.
/// </summary>
/// <param name="s">C-строка, символы которой нужно исключить из поиска.</param>
/// <param name="pos">Позиция, с которой начнется поиск.</param>
/// <param name="n">Количество символов для исключения из поиска.</param>
/// <returns>Позиция первого найденного символа, не принадлежащего первым n символам C-строки s, если найден; CString::npos, если такой символ не найден.</returns>
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
/// Находит первое вхождение любого символа, отличного от символа c, в текущую строку, начиная с позиции pos.
/// </summary>
/// <param name="c">Символ, который нужно исключить из поиска.</param>
/// <param name="pos">Позиция, с которой начнется поиск.</param>
/// <returns>Позиция первого найденного символа, отличного от символа c, если найден; CString::npos, если такой символ не найден.</returns>
size_t CString::find_first_not_of(char c, size_t pos) const {
    for (size_t i = pos; i < _size; ++i) {
        if (_data[i] != c) {
            return i;
        }
    }
    return npos;
}