#ifndef TRAIN_HPP
# define TRAAIN_HPP

# include <deque>
# include <string>
# include <algorithm>
# include <cctype>
# include <iostream>

class begint {
	private:
		std::deque<int> _digits;
		void _removeLeadZeroes();

	public:
		begint();
		begint(unsigned int n);
		begint(std::string s);
		begint(const begint& copy);
		~begint();
		begint& operator=(const begint& other);

		begint operator+(const begint& other) const;
		begint& operator+=(const begint& other);

		bool operator==(const begint& other) const;
		bool operator!=(const begint& other) const;
		bool operator<(const begint& other) const;
		bool operator<=(const begint& other) const;
		bool operator>(const begint& other) const;
		bool operator>=(const begint& other) const;

		begint& operator<<=(size_t n);
		begint operator<<(size_t n) const;
		begint& operator>>=(size_t n);
		begint operator>>(size_t n) const;

		friend std::ostream& operator<<(std::ostream& s, const begint& obj);
};

#endif