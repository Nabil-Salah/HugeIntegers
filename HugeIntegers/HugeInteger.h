#ifndef HugeInteger_H
#define HugeInteger_H

#include <array>
#include <iostream>
#include <string>

class HugeInteger {
	friend std::ostream& operator<<(std::ostream&, const HugeInteger&);
public:
	static const int digits{ 40 }; //caution: maximum digits in a HugeInteger you can icrease it

	HugeInteger(long = 0);
	HugeInteger(const std::string&); // conversion constructor from string to hugeinteger

	// addition+ operator for HugeInteger + HugeInteger
	HugeInteger operator+(const HugeInteger&) const;

	// addition+ operator for HugeInteger + int
	HugeInteger operator+(int) const;

	// adition+ operator HugeInteger + string that represents large integer value
	HugeInteger operator+(const std::string&) const;

	HugeInteger multi10(HugeInteger op, int times) const;

	// multiply operator* HugeInteger * HugeInteger
	HugeInteger operator*(const HugeInteger&) const;

	// multiply operator* HugeInteger * int
	HugeInteger operator*(int) const;

	// multiply operator* HugeInteger * string that represents large integer value
	HugeInteger operator*(const std::string&) const;

	bool operator==(const HugeInteger&)const;
	bool operator!=(const HugeInteger& Right)const {
		return !(*this == Right);
	}
	bool operator>(const HugeInteger&) const;
	bool operator<=(const HugeInteger& right) const {
		return !(*this > right);
	}
	bool operator<(const HugeInteger&) const;
	bool operator>=(const HugeInteger& right) const {
		return !(*this < right);
	}

private:
	std::array<short, digits> integer{}; // default init to 0s
	size_t actualSize{ 0 };
	char sign{ '+' };
};

#endif //HugeInteger_H