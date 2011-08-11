/*
 * pool.cpp
 *
 *  Created on: Jul 22, 2011
 *      Author: zach
 */
#include "./pool.hpp"

#include <ctime>
using std::time;
#include <set>
using std::set;
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>

#include <iostream>
using std::cerr;
using std::endl;

pool pool::TRUE = pool::pool(1);
pool pool::FALSE = pool::pool();

// random number generator used by roll and pick.
boost::mt19937 gen;
bool seeded = false;

/**
 * Create an empty pool
 */
pool::pool() {
}
/**
 * Create an integer
 */
pool::pool(int i) {
	value_pool.insert(i);
}
/**
 * Copy Constructor
 */
pool::pool(const pool& p) {
	value_pool.insert(p.value_pool.begin(), p.value_pool.end());
}
/**
 * Create a pool from multiple other pools
 */
pool::pool(const vector<pool>& pool_list) {
	for (vector<pool>::const_iterator i = pool_list.begin(); i
			< pool_list.end(); ++i)
		value_pool.insert(i->begin(), i->end());
}
/**
 * create a range from low to high inclusive
 * ex: [1->8] creates [1,2,3,4,5,6,7,8]
 */
pool::pool(const pool& low, const pool& high) {
	if (low.is_int() && high.is_int())
		for (int i = low.as_int(); i <= high.as_int(); ++i)
			add(i);
	else {
		throw poolOperationException(
				"Pool Creation Exception: value passed was not an integer");
	}
}
/**
 * Roll numdice dice, and return the result
 */
pool pool::roll(const pool& numdice, const pool& dietype) {
	// Seed our generator if it hasn't been seeded yet
	if (!seeded) {
		gen.seed(static_cast<unsigned int> (std::time(0)));
		seeded = true;
	}
	if (numdice.is_int()) {
		pool toreturn;
		// create our die: There's probably a better way to randomly access elements in a multiset, but this was as first pass.
		vector<int> die;
		for (const_iterator i = dietype.begin(); i != dietype.end(); ++i) {
			die.push_back(*i);
		}
		boost::uniform_int<> dist(0, die.size() - 1);
		// roll each die and append the result
		for (int i = 0; i < numdice.as_int(); ++i) {
			int randnum = dist(gen);
			int roll = die[randnum];
			toreturn.add(roll);
		}
		return toreturn;
	} else {
		throw poolOperationException(
				"Pool Creation Exception: value passed was not an integer");
	}
}
/**
 * Addition operator
 */
pool pool::operator+(const pool& p) const {
	if (is_int() && p.is_int())
		return pool(as_int() + p.as_int());
	else {
		throw poolOperationException(
				"Pool Addition Exception: value passed was not an integer");
	}
}
/**
 * Subtraction operator
 */
pool pool::operator-(const pool& p) const {
	if (is_int() && p.is_int())
		return pool(as_int() - p.as_int());
	else {
		throw poolOperationException(
				"Pool Subtraction Exception: value passed was not an integer");
	}
}
/**
 * Multiplication operator
 */
pool pool::operator*(const pool& p) const {
	if (is_int() && p.is_int())
		return pool(as_int() * p.as_int());
	else {
		throw poolOperationException(
				"Pool Multiplication Exception: value passed was not an integer");
	}
}
/**
 * Division operator
 */
pool pool::operator/(const pool& p) const {
	if (is_int() && p.is_int())
		return pool(as_int() / p.as_int());
	else {
		throw poolOperationException(
				"Pool Division Exception: value passed was not an integer");
	}
}
/**
 * Mod operator
 */
pool pool::operator%(const pool& p) const {
	if (is_int() && p.is_int())
		return pool(as_int() % p.as_int());
	else {
		throw poolOperationException(
				"Pool Mod Exception: value passed was not an integer");
	}
}
/**
 * > operator
 */
pool pool::operator>(const pool& p) const {
	if (is_int() && p.is_int())
		return (as_int() > p.as_int()) ? TRUE : FALSE;
	else {
		throw poolOperationException(
				"Pool Greater Than Exception: value passed was not an integer");
	}
}
/**
 * >= operator
 */
pool pool::operator>=(const pool& p) const {
	if (is_int() && p.is_int())
		return (as_int() >= p.as_int()) ? TRUE : FALSE;
	else {
		throw poolOperationException(
				"Pool Greater Than Or Equal Exception: value passed was not an integer");
	}
}
/**
 * < operator
 */
pool pool::operator<(const pool& p) const {
	if (is_int() && p.is_int())
		return (as_int() < p.as_int()) ? TRUE : FALSE;
	else {
		throw poolOperationException(
				"Pool Less Than Exception: value passed was not an integer");
	}
}
/**
 * <= operator
 */
pool pool::operator<=(const pool& p) const {
	if (is_int() && p.is_int())
		return (as_int() <= p.as_int()) ? TRUE : FALSE;
	else {
		throw poolOperationException(
				"Pool Less Than Or Equal Exception: value passed was not an integer");
	}
}
/**
 * Integer Equality operator
 */
pool pool::operator==(const pool& p) const {
	if (is_int() && p.is_int())
		return (as_int() == p.as_int()) ? TRUE : FALSE;
	else {
		throw poolOperationException(
				"Pool Equals Exception: value passed was not an integer");
	}
}
/**
 * Integer Not Equal operator
 */
pool pool::operator!=(const pool& p) const {
	if (is_int() && p.is_int())
		return (as_int() != p.as_int()) ? TRUE : FALSE;
	else {
		throw poolOperationException(
				"Pool Not Equals Exception: value passed was not an integer");
	}
}
/**
 * Boolean and operator
 */
pool pool::operator&&(const pool& p) const {
	return (boolean() && p.boolean()) ? TRUE : FALSE;
}
/**
 * Boolean Or operator
 */
pool pool::operator||(const pool& p) const {
	return (boolean() || p.boolean()) ? TRUE : FALSE;
}
/**
 * Boolean Not operator
 */
pool pool::operator!() const {
	return (value_pool.size() > 0) ? FALSE : TRUE;
}
/**
 * Return the number of elements Greater than the passed in value
 */
pool pool::expr_gt(const pool& i) const {
	if (i.is_int()) {
		const int val = i.as_int();
		int count = 0;
		for(const_reverse_iterator i = rbegin(); i != rend() && *i > val; ++i)
			count++;
		return pool(count);
	} else {
		throw poolOperationException(
				"gt() Exception: value passed was not an integer");
	}
}
/**
 * Return the number of elements Greater than or equal the passed in value
 */
pool pool::expr_ge(const pool& i) const {
	if (i.is_int()) {
		const int val = i.as_int();
		int count = 0;
		for(const_reverse_iterator i = rbegin(); i != rend() && *i >= val; ++i)
			count++;
		return pool(count);
	} else {
		throw poolOperationException(
				"ge() Exception: value passed was not an integer");
	}
}
/**
 * Return the number of elements less than the passed in value
 */
pool pool::expr_lt(const pool& i) const {
	if (i.is_int()) {
		const int val = i.as_int();
		int count = 0;
		for(const_iterator i = begin(); i!=end() && *i < val; ++i)
			count++;
		return pool(count);
	} else {
		throw poolOperationException(
				"lt() Exception: value passed was not an integer");
	}
}
/**
 * Return the number of elements Less than or equal to the passed in value
 */
pool pool::expr_le(const pool& i) const {
	if (i.is_int()) {
		const int val = i.as_int();
		int count = 0;
		for(const_iterator i = begin(); i!=end() && *i <= val; ++i)
			count++;
		return pool(count);
	} else {
		throw poolOperationException(
				"le() Exception: value passed was not an integer");
	}
}
/**
 * Return the number of elements equal to the passed in value
 */
pool pool::expr_eq(const pool& i) const {
	if (i.is_int()) {
		return pool(value_pool.count(i.as_int()));
	} else {
		throw poolOperationException(
				"eq() Exception: value passed was not an integer");
	}
}
/**
 * Return the number of elements not equal to the passed in value
 */
pool pool::expr_neq(const pool& i) const {
	if (i.is_int()) {
		return pool(value_pool.size() - value_pool.count(i.as_int()));
	} else {
		throw poolOperationException(
				"neq() Exception: value passed was not an integer");
	}
}
/**
 * Return the highest N elements as a new pool
 */
pool pool::expr_highest(const pool& i) const {
	if (i.is_int()) {
		int val = i.as_int();
		pool toreturn;
		for(const_reverse_iterator i = rbegin(); i !=rend() && val > 0; i++,val-- )
			toreturn.add(*i);
		return toreturn;
	} else {
		throw poolOperationException(
				"highest() Exception: value passed was not an integer");
	}
}
/**
 * Return the lowest N values as a new pool
 */
pool pool::expr_lowest(const pool& i) const {
	if (i.is_int()) {
		int val = i.as_int();
		pool toreturn;
		for(const_iterator i = begin(); i !=end() && val > 0; i++,val-- )
			toreturn.add(*i);
		return toreturn;
	} else {
		throw poolOperationException(
				"lowest() Exception: value passed was not an integer");
	}
}
/**
 * Remove and return N random values. Used mainly for cards
 */
pool pool::expr_pick(const pool& i) {
	// seed our roll if we havnt yet
	if (!seeded) {
		gen.seed(static_cast<unsigned int> (std::time(0)));
		seeded = true;
	}
	if (i.is_int()) {
		int val = i.as_int();
		pool toreturn;
		// while we still have a pool to pick from and we need more values...
		while (value_pool.size() > 0 && val > 0) {
			// pick a random value, remove it from the pool and add it to our return pool.
			val--;
			boost::uniform_int<> dist(1, value_pool.size());
			int randnum = dist(gen) - 1;
			iterator picked = begin();
			for (int j = 0; j < randnum; ++j)
				picked++;
			toreturn.add(*picked);
			value_pool.erase(picked);
		}
		return toreturn;
	} else {
		throw poolOperationException(
				"pick() Exception: value passed was not an integer");
	}
}
/**
 *
 */
pool pool::expr_union(const pool& p) const {
	pool toreturn(*this);
	for (const_iterator i = p.begin(); i != p.end(); ++i)
		toreturn.add(*i);
	return toreturn;
}

pool pool::expr_complement(const pool& p) const {
	pool toreturn(*this);
	for (const_iterator i = p.begin(); i != p.end(); ++i)
		toreturn.remove(*i);
	return toreturn;
}

pool pool::expr_intersect(const pool& p) const {
	pool toreturn;
	iterator mine = begin();
	iterator his = p.begin();
	while(mine != end() && his != p.end()){
		if(*mine == *his){
			toreturn.add(*mine);
			mine++; his++;
		}
		else if(*mine < *his) mine++;
		else his++;
	}
	return toreturn;
}

void pool::explode(const pool& dietype, const pool& explode_on) {
	if (!seeded) {
		gen.seed(static_cast<unsigned int> (std::time(0)));
		seeded = true;
	}
	vector<int> toadd;
	boost::uniform_int<> dist(1, dietype.size());
	for (const_iterator i = begin(); i != end(); ++i) {
		if (explode_on.exists(*i)) {
			int total = 0;
			int randnum;
			do {
				randnum = dist(gen);
				total += randnum;
			} while (explode_on.exists(randnum));
			int value = *i + total;
			value_pool.erase(i);
			toadd.push_back(value);
			i = begin();
		}
	}
	value_pool.insert(toadd.begin(), toadd.end());
}

void pool::desplode(const pool& dietype, const pool& desplode_on) {
	if (!seeded) {
		gen.seed(static_cast<unsigned int> (std::time(0)));
		seeded = true;
	}
	vector<int> toadd;
	boost::uniform_int<> dist(1, dietype.size());
	for (const_iterator i = begin(); i != end(); ++i) {
		if (desplode_on.exists(*i)) {
			int total = 0;
			int randnum;
			do {
				randnum = dist(gen);
				total += randnum;
			} while (desplode_on.exists(randnum));
			int value = *i - total;
			value_pool.erase(i);
			toadd.push_back(value);
			i = begin();
		}
	}
	value_pool.insert(toadd.begin(), toadd.end());
}

void pool::rollagain(const pool& dietype, const pool& rollagain_on) {
	if (!seeded) {
		gen.seed(static_cast<unsigned int> (std::time(0)));
		seeded = true;
	}
	vector<int> toadd;
	boost::uniform_int<> dist(1, dietype.size());
	for (const_iterator i = begin(); i != end(); ++i) {
		if (rollagain_on.exists(*i)) {
			int randnum;
			do {
				randnum = dist(gen);
				toadd.push_back(randnum);
			} while (rollagain_on.exists(randnum));
		}
	}
	value_pool.insert(toadd.begin(), toadd.end());
}

ostream& operator <<(ostream& ostr, const pool& p) {
	if (p.size() == 0) {
		ostr << "[]";
	} else {
		ostr << '[';
		pool::const_iterator this_end = p.end();
		this_end--;
		for (pool::const_iterator i = p.begin(); i != this_end; ++i)
			ostr << *i << ',';
		if (p.size() > 0)
			ostr << *(this_end);
		ostr << ']';
	}
	return ostr;
}

istream& operator >>(istream& istr, pool& p) {

}
