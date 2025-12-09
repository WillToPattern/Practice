#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstdlib>

typedef std::string str;

class bigint {
private:
    str value;

public:
    const str getVal() const { return value; }

    bigint() : value("0") {}

    // unsigned int constructor
    bigint(unsigned int num) {
        std::ostringstream ss;
        ss << num;
        value = ss.str();
    }

    // string constructor
    bigint(const str& val) : value(val) {
        size_t pos = value.find_first_not_of('0');
        if (pos == str::npos)
            value = "0";
        else
            value = value.substr(pos);
    }

    // copy assignment
    bigint& operator=(const bigint& other) {
        if (this != &other)
            value = other.value;
        return *this;
    }

    // addition
    bigint operator+(const bigint& other) const {
        str s1 = value;
        str s2 = other.value;
        str result;

        int i = int(s1.size()) - 1;
        int j = int(s2.size()) - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry) {
            int a = (i >= 0) ? s1[i] - '0' : 0;
            int b = (j >= 0) ? s2[j] - '0' : 0;

            int sum = a + b + carry;
            result.push_back(char(sum % 10 + '0'));
            carry = sum / 10;

            i--;
            j--;
        }

        std::reverse(result.begin(), result.end());

        size_t pos = result.find_first_not_of('0');
        if (pos == str::npos)
            return bigint("0");

        return bigint(result.substr(pos));
    }

    // postfix ++
    bigint operator++(int) {
        bigint tmp(*this);
        *this += bigint(1);
        return tmp;
    }

    // prefix ++
    bigint& operator++() {
        *this += bigint(1);
        return *this;
    }

    // +=
    bigint& operator+=(const bigint& oth) {
        *this = *this + oth;
        return *this;
    }

    // <<= integer
    bigint& operator<<=(unsigned int shift) {
        if (!shift)
            return *this;
        value.append(shift, '0');
        return *this;
    }

    // >>= integer
    bigint& operator>>=(unsigned int shift) {
        if (!shift)
            return *this;

        if (shift >= value.size()) {
            value = "0";
            return *this;
        }

        value = value.substr(0, value.size() - shift);
        return *this;
    }

    // <<= bigint
    bigint operator<< (const bigint& shift) const {
        unsigned int n = (unsigned int)std::atoi(shift.value.c_str());
        bigint tmp(*this);
        tmp <<= n;
        return tmp;
    }

    // >>= bigint
    bigint operator>> (const bigint& shift) const {
        unsigned int n = (unsigned int)std::atoi(shift.value.c_str());
        bigint tmp(*this);
        tmp >>= n;
        return tmp;
    }

    // comparisons
    bool operator==(const bigint& ob) const {
        return value == ob.value;
    }

    bool operator!=(const bigint& ob) const {
        return !(*this == ob);
    }

    bool operator>(const bigint& ob) const {
        if (value.size() != ob.value.size())
            return value.size() > ob.value.size();
        return value > ob.value;
    }

    bool operator<(const bigint& ob) const {
        if (value.size() != ob.value.size())
            return value.size() < ob.value.size();
        return value < ob.value;
    }

    bool operator<=(const bigint& ob) const {
        return !(*this > ob);
    }

    bool operator>=(const bigint& ob) const {
        return !(*this < ob);
    }
};

// stream output
inline std::ostream& operator<<(std::ostream& out, const bigint& ob) {
    out << ob.getVal();
    return out;
}