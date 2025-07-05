#ifndef MATHH_H
#define MATHH_H

class Math {
private:
    unsigned int m_a;
    unsigned int m_b;

    bool isPrime(unsigned int n) const;
    unsigned int countDigits(unsigned int n) const;
    bool isArmstrong(unsigned int n) const;

public:
    void SetA(unsigned int aa);
    void SetB(unsigned int bb);
    unsigned int GetA();
    unsigned int GetB();

    Math(unsigned int a = 0, unsigned int b = 0);

    unsigned int nod() const;
    unsigned long long nok() const;

    bool isPrimeA() const;
    bool isPrimeB() const;

    unsigned int countDigitsA() const;
    unsigned int countDigitsB() const;

    bool isArmstrongA() const;
    bool isArmstrongB() const;
};

#endif // MATHH_H
