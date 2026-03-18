#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <deque>
#include <string>
#include <algorithm>

class bigint {
	private:
		std::deque<int> _digits;
		void _removeLeadingZeros();

	public:
		bigint();
		bigint(unsigned int n);
		bigint(std::string s);
		bigint(const bigint &other);
		bigint& operator=(const bigint& other);
		~bigint();

		// Сравнение (Comparison)
		bool operator<(const bigint& other) const;
		bool operator==(const bigint& other) const;
		bool operator!=(const bigint& other) const;
		bool operator<=(const bigint& other) const;
		bool operator>(const bigint& other) const;
		bool operator>=(const bigint& other) const;

		// Сложение (Addition)
		bigint operator+(const bigint& other) const;
		bigint& operator+=(const bigint& other);

		// Сдвиги (Digitshift)
		bigint operator<<(size_t n) const;
		bigint &operator<<=(size_t n);
		bigint operator>>(size_t n) const;
		bigint &operator>>=(size_t n);

		friend std::ostream &operator<<(std::ostream& os, const bigint& obj);
};

#endif