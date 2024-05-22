#include <iostream>
#include <cmath>

class Fraction {
private:
    int numerator;       // числитель
    int denominator;     // знаменатель

public:
    // Конструкторы
    Fraction() : numerator(0), denominator(1) {}
    Fraction(int num, int denom) : numerator(num), denominator(denom) {}
    Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}
    Fraction(const std::string& fractionStr);

    
    ~Fraction() {}

    
    Fraction& operator=(const Fraction& other);

    
    bool operator==(int value) const;
    bool operator!=(int value) const;
    bool operator>(int value) const;
    bool operator<(int value) const;
    bool operator>=(int value) const;
    bool operator<=(int value) const;

    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;

    
    Fraction operator+(int value) const;
    Fraction operator-(int value) const;
    Fraction operator*(int value) const;
    Fraction operator/(int value) const;

    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    Fraction& operator+=(int value);
    Fraction& operator-=(int value);
    Fraction& operator*=(int value);
    Fraction& operator/=(int value);

    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
    friend std::istream& operator>>(std::istream& is, Fraction& fraction);

    
    void simplify();

private:
    
    int gcd(int a, int b) const; 
};

Fraction::Fraction(const std::string& fractionStr) {
    // Реализация конструктора преобразования из строки
}

Fraction& Fraction::operator=(const Fraction& other) {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

bool Fraction::operator==(int value) const {
    return numerator == value * denominator;
}

bool Fraction::operator!=(int value) const {
    return !(*this == value);
}

bool Fraction::operator>(int value) const {
    return numerator > value * denominator;
}

bool Fraction::operator<(int value) const {
    return numerator < value * denominator;
}

bool Fraction::operator>=(int value) const {
    return numerator >= value * denominator;
}

bool Fraction::operator<=(int value) const {
    return numerator <= value * denominator;
}

bool Fraction::operator==(const Fraction& other) const {
    return numerator * other.denominator == other.numerator * denominator;
}

bool Fraction::operator!=(const Fraction& other) const {
    return !(*this == other);
}

bool Fraction::operator>(const Fraction& other) const {
    return numerator * other.denominator > other.numerator * denominator;
}

bool Fraction::operator<(const Fraction& other) const {
    return numerator * other.denominator < other.numerator * denominator;
}

bool Fraction::operator>=(const Fraction& other) const {
    return numerator * other.denominator >= other.numerator * denominator;
}

bool Fraction::operator<=(const Fraction& other) const {
    return numerator * other.denominator <= other.numerator * denominator;
}

Fraction Fraction::operator+(int value) const {
    return Fraction(numerator + value * denominator, denominator);
}

Fraction Fraction::operator-(int value) const {
    return Fraction(numerator - value * denominator, denominator);
}

Fraction Fraction::operator*(int value) const {
    return Fraction(numerator * value, denominator);
}

Fraction Fraction::operator/(int value) const {
    if (value == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return Fraction(numerator, denominator * value);
}

Fraction Fraction::operator+(const Fraction& other) const {
    return Fraction(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
}

Fraction Fraction::operator-(const Fraction& other) const {
    return Fraction(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
}

Fraction Fraction::operator*(const Fraction& other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

Fraction& Fraction::operator+=(int value) {
    *this = *this + value;
    return *this;
}

Fraction& Fraction::operator-=(int value) {
    *this = *this - value;
    return *this;
}

Fraction& Fraction::operator*=(int value) {
    *this = *this * value;
    return *this;
}

Fraction& Fraction::operator/=(int value) {
    *this = *this / value;
    return *this;
}

Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) {
    *this = *this - other;
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& other) {
    *this = *this * other;
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& other) {
    *this = *this / other;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
    os << fraction.numerator << "/" << fraction.denominator;
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& fraction) {
    is >> fraction.numerator;
    is.ignore(1); // Пропускаем символ "/"
    is >> fraction.denominator;
    return is;
}

void Fraction::simplify() {
    int divisor = gcd(abs(numerator), abs(denominator));
    numerator /= divisor;
    denominator /= divisor;
}

int Fraction::gcd(int a, int b) const {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    
    Fraction fraction1(3, 4);
    Fraction fraction2(1, 2);
    Fraction fraction3 = fraction1 + fraction2;
    Fraction fraction4 = fraction1 - fraction2;
    Fraction fraction5 = fraction1 * fraction2;
    Fraction fraction6 = fraction1 / fraction2;

    std::cout << "Fraction 1: " << fraction1 << std::endl;
    std::cout << "Fraction 2: " << fraction2 << std::endl;
    std::cout << "Fraction 1 + Fraction 2: " << fraction3 << std::endl;
    std::cout << "Fraction 1 - Fraction 2: " << fraction4 << std::endl;
    std::cout << "Fraction 1 * Fraction 2: " << fraction5 << std::endl;
    std::cout << "Fraction 1 / Fraction 2: " << fraction6 << std::endl;

    return 0;
}