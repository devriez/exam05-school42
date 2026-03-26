#include "set.hpp"

set::set() : _bag(0) {}

set::set(searchable_bag& backend) : _bag(&backend) {}

set::set(searchable_bag* backend) : _bag(backend) {}

set::set(const set& other) : _bag(other._bag) {}

set& set::operator=(const set& other) {
	if (this != &other) {
		_bag = other._bag;
	}
	return *this;
}

set::~set() {}

bool set::has(int x) const {
	if (!_bag) return false;
	return _bag->has(x);
}

void set::insert(int x) {
	if (!_bag) return;
	
	if (!this->has(x)) {
		_bag->insert(x);
	}
}

void set::insert(int* array, int n) {
	if (!_bag || !array || n <= 0) return;

	for (int i = 0; i < n; ++i) {
		this->insert(array[i]);
	}
}

void set::print() const {
	if (_bag) {
		_bag->print();
	}
}

void set::clear() {
	if (_bag) {
		_bag->clear();
	}
}