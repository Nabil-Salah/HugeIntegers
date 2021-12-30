// Fig. 10.18: Hugeinteger.cpp 
// HugeInteger member-function and friend-function definitions.
#include <cctype> // isdigit function prototype
#include "Hugeinteger.h" // HugeInteger class definition
#include <algorithm>
using namespace std;

HugeInteger::HugeInteger(long value) {
    if (value < 0) {
        sign = '-';
        value *= -1;
    }
    // place digits of argument into array 
    int j;
    for (j = digits - 1 ; value != 0 && j >= 0; j--) {
        integer[j] = value % 10;
        value /= 10;
    }
    actualSize = digits - j - 1;
}

HugeInteger::HugeInteger(const string& number) {
    // place digits of argument into array
    int length{ static_cast<int>(number.size()) };
    if (number.find('-') != string::npos) {
        sign = '-';
    }

    for (int j{ digits - length }, k{ 0 }; j < digits; ++j, ++k) {
        if (isdigit(number[k])) { // ensure that character is a digit
            integer[j] = number[k] - '0';
        }
    }
    actualSize = number.size();
}

HugeInteger HugeInteger::operator+(const HugeInteger& op2) const {
    HugeInteger temp; // temporary result
    int carry = 0;

    for (int i{ digits - 1 }; i >= 0; i--) {
        temp.integer[i] = integer[i] + op2.integer[i] + carry;

        // determine whether to carry a 1
        if (temp.integer[i] > 9) {
            temp.integer[i] %= 10;  // reduce to 0-9
            carry = 1;
        }
        else { // no carry 
            carry = 0;
        }
    }

    return temp; // return copy of temporary object
}

HugeInteger HugeInteger::operator+(int op2) const {
    // convert op2 to a HugeInteger, then invoke 
    // operator+ for two HugeInteger objects
    return *this + HugeInteger(op2);
}

HugeInteger HugeInteger::operator+(const string& op2) const {
    // convert op2 to a HugeInteger, then invoke 
    // operator+ for two HugeInteger objects
    return *this + HugeInteger(op2);
}

// overloaded output operator
ostream& operator<<(ostream& output, const HugeInteger& num) {
    int i;
    if(num.sign == '-')
        output << num.sign;
    // skip leading zeros
    for (i = 0; (i < HugeInteger::digits) && (0 == num.integer[i]); ++i) {}

    if (i == HugeInteger::digits) {
        output << 0;
    }
    else {
        for (; i < HugeInteger::digits; ++i) {
            output << num.integer[i];
        }
    }
    return output;
}
HugeInteger HugeInteger::multi10(HugeInteger op,int times) const{
    for (int i = 0; i < times; i++) {
        rotate(op.integer.begin(), op.integer.begin() + 1, op.integer.end());
        op.integer[digits - 1] = 0;
    }
    return op;
}
HugeInteger HugeInteger::operator*(const HugeInteger& op2) const {
    HugeInteger temp; // temporary result
    array<HugeInteger, 40> arr{};
    unsigned int i{ 0 };
    int k2{ 0 };
    for (unsigned int j{ digits - 1 }; j >= digits - op2.actualSize; j--, k2++) {
        int carry = 0;
        HugeInteger ans{ 0 };
        int k3 = 1;
        for (i = digits - 1; i >= digits-actualSize ; i--) {
            int temprory = (integer[i] * op2.integer[j] + carry);
            if (i == digits - actualSize) {
                ans.integer[i] =temprory % 10;
                ans.integer[i-1] =temprory / 10;
                break;
            }
            if (temprory > 9) {
                /*if (temprory % 10 == 0) {
                    k3 *= 10;
                }*/
                 carry = temprory / 10;
                 temprory %= 10;
                
            }
            else {
                carry = 0;
            }
            ans.integer[i] = temprory;
        }
        arr[j] = multi10(ans,k2);
    }
    for (int i = 0; i < arr.size(); i++) {
        temp = temp + arr[i];
    }
    if ((sign == '-' && op2.sign == '+') || (sign == '+' && op2.sign == '-'))
        temp.sign = '-';
    return temp; // return copy of temporary object
}

HugeInteger HugeInteger::operator*(int op2) const {
    // convert op2 to a HugeInteger, then invoke 
    // operator* for two HugeInteger objects
    return *this * HugeInteger(op2);
}

HugeInteger HugeInteger::operator*(const string& op2) const {
    // convert op2 to a HugeInteger, then invoke 
    // operator* for two HugeInteger objects
    return *this * HugeInteger(op2);
}
bool HugeInteger::operator==(const HugeInteger& right) const
{
    for (size_t i = 0; i < digits; i++)
    {
        if (integer[i] != right.integer[i])
            return false;
    }
    return true;
}
bool HugeInteger::operator>(const HugeInteger& right) const
{
    for (size_t i = 0; i < digits; i++)
    {
        if (integer[i] > right.integer[i])
            return true;
        else if (integer[i] < right.integer[i])
            return false;
    }
    return false;
}
bool HugeInteger::operator<(const HugeInteger& right) const
{
    for (size_t i = 0; i < digits; i++)
    {
        if (integer[i] > right.integer[i])
            return false;
        else if (integer[i] < right.integer[i])
            return true;
    }
    return false;
}
