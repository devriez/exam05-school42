#include "bigint.hpp"

void bigint::_removeLeadingZeros() {
	while (_digits.size() > 1 && _digits.back() == 0) {
		_digits.pop_back();
	}
}

bigint::bigint() {
	_digits.push_back(0);
}

bigint::bigint(unsigned int n) {
	if (n == 0)
		_digits.push_back(0);
	while (n > 0) {
		_digits.push_back(n % 10);
		n /= 10;
	}
}

bigint::bigint(std::string s) {
	if (s.empty()) {
		_digits.push_back(0);
		return;
	}
	// Заполняем с конца строки
	for (int i = s.length() - 1; i >= 0; --i) {
		if (isdigit(s[i])) {
			_digits.push_back(s[i] - '0');
		}
	}
	_removeLeadingZeros();
	if (_digits.empty())
		_digits.push_back(0);
}

bigint::bigint(const bigint &other) : _digits(other._digits) {}

bigint& bigint::operator=(const bigint &other) {
	if (this != &other) {
		_digits = other._digits;
	}
	return *this;
}

bigint::~bigint() {}

// --- Сравнения ---
bool bigint::operator<(const bigint &other) const {
	if (_digits.size() != other._digits.size())
		return _digits.size() < other._digits.size();
	for (int i = _digits.size() - 1; i >= 0; --i) {
		if (_digits[i] != other._digits[i])
			return _digits[i] < other._digits[i];
	}
	return false;
}

bool bigint::operator==(const bigint &other) const { return _digits == other._digits; }
bool bigint::operator!=(const bigint &other) const { return !(*this == other); }
bool bigint::operator<=(const bigint &other) const { return (*this < other) || (*this == other); }
bool bigint::operator>(const bigint &other) const { return !(*this <= other); }
bool bigint::operator>=(const bigint &other) const { return !(*this < other); }

// --- Сложение ---
bigint bigint::operator+(const bigint &other) const {
	bigint res;
	res._digits.clear();
	int carry = 0;
	size_t n = std::max(_digits.size(), other._digits.size());
	for (size_t i = 0; i < n || carry; ++i) {
		int sum = carry + (i < _digits.size() ? _digits[i] : 0)
		                + (i < other._digits.size() ? other._digits[i] : 0);
		res._digits.push_back(sum % 10);
		carry = sum / 10;
	}
	return res;
}

bigint &bigint::operator+=(const bigint &other) {
	*this = *this + other;
	return *this;
}

// --- Сдвиги ---
bigint bigint::operator<<(size_t n) const {
	if (n == 0 || (_digits.size() == 1 && _digits[0] == 0)) return *this;
	bigint res = *this;
	res._digits.insert(res._digits.begin(), n, 0);
	return res;
}

bigint &bigint::operator<<=(size_t n) {
	*this = *this << n;
	return *this;
}

bigint bigint::operator>>(size_t n) const {
	if (n >= _digits.size()) return bigint(0);
	bigint res = *this;
	res._digits.erase(res._digits.begin(), res._digits.begin() + n);
	if (res._digits.empty()) res._digits.push_back(0);
	return res;
}

bigint &bigint::operator>>=(size_t n) {
	*this = *this >> n;
	return *this;
}

std::ostream &operator<<(std::ostream &os, const bigint &obj) {
	for (int i = obj._digits.size() - 1; i >= 0; --i) {
		os << obj._digits[i];
	}
	return os;
}