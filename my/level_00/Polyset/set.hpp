#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set : public searchable_bag {
	private:
		searchable_bag* _bag;

	public:
		// Orthodox Canonical Form
		set();
		set(const set& other);
		set& operator=(const set& other);
		virtual ~set();

		// Дополнительные конструкторы из main
		set(searchable_bag& backend);        // Reference ctor
		set(searchable_bag* backend);        // Pointer ctor

		// Реализация интерфейса searchable_bag
		virtual bool has(int x) const;
		virtual void insert(int x);
		virtual void insert(int* array, int n);
		virtual void print() const;
		virtual void clear();
};

#endif