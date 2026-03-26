#include "train.hpp"

void begint::_removeLeadZeroes() {
	if(_digits.size() == 1)
		return;

	while(_digits.size() > 1 && _digits.back() == 0)
		_digits.pop_back();
}

begint::begint(): _digits(0) {};

begint::begint(unsigned int n) {
	_digits.clear();
	if (n < 10)
		_digits.push_back(n);
	while(n != 0) {
		_digits.push_back(n % 10);
		n = n / 10;
	}
}

begint::begint(std::string s) {
	_digits.clear();
	if (s.length() == 0)
		_digits.push_back(0);
	for (int i = s.length() - 1; i >= 0; --i) {
		if (isdigit(s[i])) 
			_digits.push_back(s[i] - '0');
	}
	_removeLeadZeroes();
}

begint::~begint() {};

begint& begint::operator=(const begint& other) {
	if(this != &other)
		_digits = other._digits;
	return *this;
}

begint begint::operator+(const begint& other) const {
	int	sum;
	int	movable = 0;
	begint res(0);
	res._digits.clear();
	for (int i = 0; i < _digits.size() || i < other._digits.size() || movable; ++i) {
		sum = movable + (i < _digits.size() ? _digits[i] : 0) +
						(i < other._digits.size() ? other._digits[i] : 0);
		res._digits.push_back(sum % 10);
		movable = sum / 10;
	}
	return res;
}

begint& begint::operator+=(const begint& other) {
	*this = *this + other;
	return *this;
}

bool begint::operator==(const begint& other) const {
	if (_digits.size() != other._digits.size())
		return false;
	for (int i = _digits.size() - 1; i >= 0; --i) {
		if (_digits[i] != other._digits[i])
			return false;
	}
	return true;
}

bool begint::operator!=(const begint& other) const {
	return !(*this == other);
}

bool begint::operator<(const begint& other) const {
	if (_digits.size() != other._digits.size())
		return _digits.size() < other._digits.size();
	for (int i = _digits.size() - 1; i >= 0; --i) {
		if (_digits[i] >= other._digits[i])
			return false;
	}
	return true;
}

bool begint::operator<=(const begint& other) const {
	return (*this < other || *this == other);
}

bool begint::operator>(const begint& other) const {
	return !(*this <= other);
}

bool begint::operator>=(const begint& other) const {
	return (*this > other || *this == other);
}

begint& begint::operator<<=(size_t n) {
	_digits.insert(_digits.begin(), n, 0);
	return *this;
}

begint begint::operator<<(size_t n) const{
	begint res(*this);
	res <<= n; 
	return res;
}

begint& begint::operator>>=(size_t n) {
	if (n >= _digits.size()) {
		_digits.clear();
		_digits.push_back(0);
	} else {
		_digits.erase(_digits.begin(), _digits.begin() + n);
	}
	_removeLeadZeroes(); // На случай, если после удаления остались нули
	return *this;
}

begint& begint::operator>>=(size_t n) {
	_digits.erase(_digits.begin(), _digits.begin() + n);
	return *this;
}

begint begint::operator>>(size_t n) const {
	begint res(*this);
	res >>= n;
	return res;
}

std::ostream& operator<<(std::ostream& s, const begint& obj) {
	for (int i = obj._digits.size() - 1; i >= 0; --i) {
		s << obj._digits[i];
	}
	return s;
}