//
// Created by AdminPC on 14.05.2016.
//
#include "rational.h"

rational::rational(int val) {
    num = val;
    denom = 1;
}
rational::rational(int n, int d) {
    int gcd = std::__gcd(n, d);
    num = n / gcd;
    denom = d / gcd;
}
int rational::getNum() const {
    return num;
}
int rational::getDenom() const {
    return denom;
}
rational rational::operator+(const rational  &a) const {
    return rational(this->num * a.denom + a.num * this->denom, this->denom * a.denom);
}
rational rational::operator-(const rational  &a) const {
    return ((*this) + rational(-a.num, a.denom));
}
rational rational::operator*(const rational  &a) const {
    return rational(this->num * a.num, this->denom * a.denom);
}
rational rational::operator/(const rational  &a) const {
    return (*this) * rational(a.denom, a.num);
}