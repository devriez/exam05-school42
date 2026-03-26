#include "vect2.hpp"

vect2::vect2() : _x(0), _y(0) {
}

vect2::vect2(int x, int y) : _x(x), _y(y) {
}

vect2::vect2(const vect2 &copy) : _x(copy._x), _y(copy._y) {
}

vect2::~vect2() {
}

vect2 &vect2::operator=(const vect2 &other) {
	if (this != &other) {
		_x = other._x;
		_y = other._y;
	}
	return *this;
}

vect2 vect2::operator+(const vect2 &other) const {
	return vect2(_x + other._x, _y + other._y);
}

vect2 &vect2::operator+=(const vect2 &other) {
	_x += other._x;
	_y += other._y;
	return *this;
}

vect2 vect2::operator-(const vect2 &other) const {
	return vect2(_x - other._x, _y - other._y);
}

vect2 &vect2::operator-=(const vect2 &other) {
	_x -= other._x;
	_y -= other._y;
	return *this;
}

vect2 vect2::operator*(const int scalar) const {
	return vect2(_x * scalar, _y * scalar);
}

vect2 &vect2::operator*=(const int scalar) {
	_x *= scalar;
	_y *= scalar;
	return *this;
}

vect2 vect2::operator+() const {
	return *this;
}

vect2 vect2::operator-() const {
	return vect2(-_x, -_y);
}

vect2 &vect2::operator++() {
	++_x;
	++_y;
	return *this;
}

vect2 vect2::operator++(int) {
	vect2 tmp(*this);
	operator++();
	return tmp;
}

vect2 &vect2::operator--() {
	--_x;
	--_y;
	return *this;
}

vect2 vect2::operator--(int) {
	vect2 tmp(*this);
	operator--();
	return tmp;
}

bool vect2::operator==(const vect2 &other) const {
	return (_x == other._x && _y == other._y);
}

bool vect2::operator!=(const vect2 &other) const {
	return !(*this == other);
}

int &vect2::operator[](int i) {
	if (i == 0) {
		return _x;
	}
	return _y;
}

const int &vect2::operator[](int i) const {
	if (i == 0) {
		return _x;
	}
	return _y;
}

vect2 vect2::operator+(const vect2 &other) const {
	return vect2(_x + other._x, _y + other._y);
}

vect2 vect2::operator-(const vect2 &other) const {
	return vect2(_x - other._x, _y - other._y);
}

vect2 vect2::operator*(const int scalar) const {
	return vect2(_x * scalar, _y * scalar);
}

std::ostream &operator<<(std::ostream &os, const vect2 &v) {
	os << "{" << v[0] << ", " << v[1] << "}";
	return os;
}

vect2 operator*(const int scalar, const vect2 &other) {
	return other * scalar;
}