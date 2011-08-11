#ifndef POOL_HPP_
#define POOL_HPP_
#include <exception>
using std::exception;
#include <string>
using std::string;
#include <set>
using std::multiset;
#include <vector>
using std::vector;
#include <iostream>
using std::ostream;
using std::istream;


/**
 * Pool Class
 * copyright 2011 Zachary Hoekstra (zhoekstra@gmail.com)
 *
 * The pool class is used in Bones, a dice language, and is used to represent all sorts of data types
 * Specifically, a pool is a set of integers that can hold multiple integers with the same values.
 * For the purposes of explanation, pools are described using the following notation
 *
 * a pool can represent the following data types:
 * === Integer ===
 * A pool of exactly one value is an integer. Certain operations can only work on pools of size 1, and check for the size of the pool
 * upon executing the operation.
 *
 * === Boolean ===
 * The empty pool [] is false. All other pools are true.
 *
 * ===Die Type===
 * Pools can represent types of dice by including one number for every face on the die.
 * For example, a 6-sided die is represented by the pool [1,2,3,4,5,6], while an averaging die is represented by [2,3,3,4,4,5].
 *
 * == Roll Results ===
 * When dice are rolled, they form a pool.
 *
 * For example, rolling 5d6 might create the pool [2,3,3,4,6]
 */
class pool{
public:
	pool();
	pool(int i);
	pool(const pool& p);
	pool(const vector<pool>& pool_list);
	pool(const pool& low, const pool& high);
	static pool roll(const pool& numdice, const pool& dietype);

	static pool TRUE;
	static pool FALSE;

	typedef multiset<int>::iterator iterator;
	typedef multiset<int>::const_iterator const_iterator;
	typedef multiset<int>::reverse_iterator reverse_iterator;
	typedef multiset<int>::const_reverse_iterator const_reverse_iterator;
	inline iterator begin() {return value_pool.begin();}
	inline reverse_iterator rbegin() {return value_pool.rbegin();}
	inline const_iterator begin() const {return value_pool.begin();}
	inline const_reverse_iterator rbegin() const {return value_pool.rbegin();}
	inline const_iterator end() const {return value_pool.end();}
	inline const_reverse_iterator rend() const {return value_pool.rend();}
	inline int size() const {return value_pool.size();}

	/**
	 * Mathematical operators. These only work on pools of size 1, and return a
	 * pool of size 1 with the result in it.
	 */
	pool operator+(const pool& p) const;
	pool operator-(const pool& p) const;
	pool operator*(const pool& p) const;
	pool operator/(const pool& p) const;
	pool operator%(const pool& p) const;

	/**
	 * Set operators. These work on pools of any size, and can return pools of any size
	 */
	/// returns a pool that contains all values from both pools. (ex: [1,3,7,8] union [1,2,7] creates [1,1,2,3,7,7,8] )
	pool expr_union(const pool& p) const;
	/// returns all values in the first pool that are not in the second pool. (ex: [1,1,1,2,3] complement [1,1,2] creates [1,3] )
	pool expr_complement(const pool& p) const;
	/// returns all values that are in both pools. (ex: [1,1,1,2,2,3] intersect [1,1,2,4] creates [1,1,2] )
	pool expr_intersect(const pool& p) const;

	/// boolean unary operators. Only takes pools of size one
	pool operator>(const pool& p) const;
	pool operator>=(const pool& p) const;
	pool operator<(const pool& p) const;
	pool operator<=(const pool& p) const;
	pool operator==(const pool& p) const;
	pool operator!=(const pool& p) const;

	/// boolean logical operators
	pool operator&&(const pool& p) const;
	pool operator||(const pool& p) const;
	pool operator!() const;

	/**
	 * General operations. These are predefined function in the Bones grammer
	 *
	 */
	/// return the number of values in this pool greater than the integer passed in.
	pool expr_gt(const pool& i) const;
	/// return the number of values in this pool greater than or equal to the integer passed in.
	pool expr_ge(const pool& i) const;
	/// return the number of values in this pool less than the integer passed in.
	pool expr_lt(const pool& i) const;
	/// return the number of values in this pool less than or equal the integer passed in.
	pool expr_le(const pool& i) const;
	/// return the number of values in this pool equal the integer passed in.
	pool expr_eq(const pool& i) const;
	/// return the number of values in this pool not equal to the integer passed in.
	pool expr_neq(const pool& i) const;
	/// return the highest N values as a new pool
	pool expr_highest(const pool& i) const;
	/// return the lowest N values as a new pool/
	pool expr_lowest(const pool& i) const;
	/// remove and return N values from this pool
	pool expr_pick(const pool& i);
	/// return the size of this pool.
	inline pool expr_sizeof() const { return pool(value_pool.size()); }

	///roll modifiers. These modify the pool they are called upon.
	void explode(const pool& dietype,const pool& p);
	void desplode(const pool& dietype,const pool& p);
	void rollagain(const pool& dietype,const pool& p);

	/* Various functions used in the interpreter. NOT part of the grammar */
	/// Add a value to the pool
	inline void add(int i) {value_pool.insert(i);}
	/// remove one instance of a value from the pool
	inline void remove(int i) {
		const iterator iter = value_pool.find(i);
		if (iter != end()) value_pool.erase(iter);
	}
	/// return whether the pool can be considered an integer
	inline bool is_int() const {return value_pool.size() == 1;}
	/// return the boolean value of the pool
	inline bool boolean() const {return value_pool.size() > 0;}
	/// return the pool as an integer
	inline int as_int() const {return *value_pool.begin();}
	/// return whether the value can be found in this pool
	inline bool exists(int i) const {return value_pool.find(i) != end();}
	/// return the number of values that exists in this pool
	inline int count(int i) const {return value_pool.count(i);}
protected:
	/// A pool is really just a multiset of integers. But people don't need to know that, do they?
	multiset<int> value_pool;
};

ostream& operator <<(ostream& ostr, const pool& p);
istream& operator >>(istream& istr, pool& p);

class poolOperationException : public exception{
public:
	poolOperationException(string s) : error(s) {}
	poolOperationException(const char* s) : error(s) {}
	inline const char* what() const throw() {return error.c_str();}
	virtual ~poolOperationException() throw() {}
protected:
	string error;
};

#endif /* POOL_HPP_ */
