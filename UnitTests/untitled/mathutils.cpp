#include "math.h"
#include <cmath>

bool Math::isPrime(unsigned int n) const {
    if (n == 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    unsigned int root = (unsigned int)sqrt(n);
    for (unsigned int i = 3; i <= root; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

unsigned int Math::countDigits(unsigned int n) const {
    if (n == 0)
        return 1;
    unsigned int count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

bool Math::isArmstrong(unsigned int n) const {
    unsigned int original = n;
    unsigned int numDigits = countDigits(n);
    unsigned long long sum = 0;
    while (n != 0) {
        unsigned int digit = n % 10;
        unsigned long long power = 1;
        for (unsigned int i = 0; i < numDigits; i++) {
            power *= digit;
        }
        sum += power;
        n /= 10;
    }
    return sum == original;
}

void Math::SetA(unsigned int aa) { m_a = aa; }
void Math::SetB(unsigned int bb) { m_b = bb; }
unsigned int Math::GetA() { return m_a; }
unsigned int Math::GetB() { return m_b; }

Math::Math(unsigned int a, unsigned int b) : m_a(a), m_b(b) {}

unsigned int Math::nod() const {
    unsigned int a = m_a;
    unsigned int b = m_b;
    while (a != 0 && b != 0) {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a + b;
}

unsigned long long Math::nok() const {
    unsigned int p = nod();
    if (p == 0)
        return 0;
    unsigned long long q = (unsigned long long)(m_a)*m_b;
    return q / p;
}

bool Math::isPrimeA() const { return isPrime(m_a); }
bool Math::isPrimeB() const { return isPrime(m_b); }

unsigned int Math::countDigitsA() const { return countDigits(m_a); }
unsigned int Math::countDigitsB() const { return countDigits(m_b); }

bool Math::isArmstrongA() const { return isArmstrong(m_a); }
bool Math::isArmstrongB() const { return isArmstrong(m_b); }
