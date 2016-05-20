//
// Created by AdminPC on 14.05.2016.
//

#ifndef TASK3_RATIONAL_H
#define TASK3_RATIONAL_H


#include <algorithm>

class rational {

private:
    int num, denom;

public:
    int getNum() const;
    int getDenom() const;
    rational(int val);
    rational(int num, int denom);
    rational operator+(const rational&) const;
    rational operator-(const rational&) const;
    rational operator*(const rational&) const;
    rational operator/(const rational&) const;
};


#endif //TASK3_RATIONAL_H
