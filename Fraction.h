#ifndef FRACTION_H
#define FRACTION_H

#include "base.h"
#include <iostream>
#include <cryptopp/integer.h>

namespace AlgebraTAU{
class Fraction{
    CryptoPP::Integer a,b;

    void fix(){
        if(b.IsNegative()) {
            a.Negate();
            b.Negate();
        }
        CryptoPP::Integer d = CryptoPP::Integer::Gcd(a.AbsoluteValue(),b);
        a /= d;
        b /= d;
    }

public:

    Fraction(const CryptoPP::Integer& a = 0, const CryptoPP::Integer& b = 1) : a(a), b(b){
        fix();
    }

    Fraction(const Fraction& o) : a(o.a), b(o.b){
        fix();
    }
    
    Fraction& operator=(const Fraction& o){
        a = o.a;
        b = o.b;
        fix();
        return *this;
    }

    Fraction& operator*=(const Fraction& o){
        a *= o.a;
        b *= o.b;
        fix();
        return *this;
    }

    Fraction& operator/=(const Fraction& o){
        a *= o.b;
        b *= o.a;
        fix();
        return *this;
    }

    Fraction& operator+=(const Fraction& o){
        a *= o.b;
        a += o.a * b;
        b *= o.b;
        fix();
        return *this;
    }
    
    Fraction& operator-=(const Fraction& o){
        a *= o.b;
        b *= o.b;
        a -= o.a * b;
        fix();
        return *this;
    }

    Fraction& Negate(){
        a.Negate();
        fix();
        return *this;
    }

    Fraction operator*(const Fraction& o) const {
        Fraction res = *this;
        res *= o;
        return res;
    }

    Fraction operator/(const Fraction& o) const {
        Fraction res = *this;
        res /= o;
        return res;
    }

    Fraction operator+(const Fraction& o) const {
        Fraction res = *this;
        res += o;
        return res;
    }

    Fraction operator-(const Fraction& o) const {
        Fraction res = *this;
        res -= o;
        return res;
    }

    Fraction operator-() const {
        Fraction res = *this;
        res.Negate();
        return res;
    }

    bool IsNegative() const {
        return a.IsNegative();
    }

    bool IsZero() const {
        return a.IsZero();
    }

    bool IsPositive() const {
        return a.IsPositive();
    }

    bool operator<(const Fraction& o) const {
        return (*this - o).IsNegative();
    }

    bool operator>(const Fraction& o) const {
        return (o - *this).IsNegative();
    }

    bool operator<=(const Fraction& o) const {
        return !(*this > o);
    }
    
    bool operator>=(const Fraction& o) const {
        return !(*this < o);
    }   

    bool operator==(const Fraction& o) const {
        return a == o.a && b == o.b;
    }

    bool operator!=(const Fraction& o) const {
        return a != o.a || b != o.b;
    }

    void print(std::ostream& os) const {
        os << a << "/" << b;
    }
};
};

std::ostream& operator<<(std::ostream& os, const AlgebraTAU::Fraction& f){
    f.print(os);
    return os;
}

#endif