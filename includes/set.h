#ifndef SET_H
#define SET_H

#include <algorithm> // std::swap
#include <cassert>   // assert()
#include <ostream>   // std::ostream
#include <iterator>  // std::bidirectional_iterator_tag
#include <cstddef>   // std::ptrdiff_t
#include "non_existent_element_exception.h"
#include "duplicated_element_exception.h"

/**
	@file set.h
	@brief Declaration of set class
**/

/**
	@brief A dynamic set of elements.
	
	Sets are containers that store unique elements, so no duplicated elements are allowed.
	The value of an element is also the key used to identify it.
	Internally, the elements in a set are compared using an equality functor (of type Eql).
	forward const_iterators can be used to iterate over the elements in a set.

	@tparam T the type of the element stored.
	@tparam Eql functor used to check whether two elements are equal or not.
*/
template <typename T, typename Eql>
class set 
{

	/**	
		@brief An element in the set		

		Inner class used to represent a generic element of the set with a certain value. 
		It has a pointer to the next element of the set.
		If not specified, this pointer is null by default.
	*/
	struct element 
	{	
		T value;	///< the value of the element
		element* next;  ///< the next element in the set
		
		/** @brief Default constructor */
		element() : value(0), next(0) 
		{}
		
		/** @brief Secondary constructor */
		element(const T& val, element* nextEle = 0) 
			: value(val), next(nextEle) 
		{}
	};

	element* _head;				///< The first element of the set
	unsigned int _size;  ///< Size of the set

	Eql _equal;                 ///< Functor used to check whether two elements are equal or not


	/**
		Helper function used to add an element to the set. Its functioning is
		recursive. 
		Note that if there's already an element in the set with the same value
		as newValue, an exception will be thrown.
		 
		@param newValue a reference to the value of the new element to be inserted
		@param ele a reference to an element of the set
	*/
	void add(const T& newValue, element& ele) 
	{
		if (_equal(newValue, ele.value))
			throw duplicated_element_exception();
		else if (ele.next == 0) 
			ele.next = new element(newValue);
		else  
			add(newValue, *ele.next);
	}


	/**
		Helper function used to remove an element to the set. Its functioning is
		recursive. 
		Note that if there's no elements in the list with the same value of
		toDelete, an exception will be thrown.
		
		@param toDelete a reference to the value of the element to be deleted
		@param ele a reference to an element of the set
	*/
	void remove(const T& toDelete, element &ele) 
	{
		if (ele.next == 0)
			throw non_existent_element_exception();
		else if (_equal(toDelete, ele.next->value)) 
		{
			element* tmp = ele.next;
			ele.next = ele.next->next;
			delete tmp;
		}
		else
			remove(toDelete, *ele.next);
	}


	/**
		Helper function used to get an element of the set.
		Its functioning is recursive.
		
		@param ele a reference to an element
		@param index the current index
	*/
	const T& getElement(element& ele, unsigned int index) const 
	{
		if (index == 0)
			return ele.value;
		else
			return getElement(*ele.next, index - 1);
	}

	/**
		Helper function used to remove all elements in the set, leaving the set
		with a size of 0.
		
		@param ele a pointer to an element in the set
	*/
	void clear(element* ele) 
	{
		if (ele != 0) {
			clear(ele->next);
			delete ele;
		}
	}

public:

	/** 
		@brief Default constructor

		It is used to create a new empty set.
	*/
	set() : _head(0), _size(0) 
	{}


	/** 
		@brief Copy constructor 

		It is used to create a new set with the same elements 
		of another set in input.

		@param other A set used to create the new one
		@throw std::exception
	*/
	set(const set &other) : _head(0), _size(0) 
	{
		element *tmp = other._head;
		try 
		{
			while (tmp != 0) 
			{
				add(tmp->value);
				tmp = tmp->next;
			}	
		}
		catch (...) 
		{
			clear(_head);
			throw;
		}
	}


	/**	
		@brief Secondary constructor

		It creates a set using a data sequence defined by a generic 
		pair of iterators.
		
		@tparam Q the type of the iterator
		@param b begin iterator
		@param e end iterator
		@throw duplicated_element_exception
		@throw std::exception
	*/
	template <typename Q>
	set(Q b, Q e) : _head(0), _size(0) 
	{ 
		try 
		{
			while (b != e) 
			{
				add(static_cast<T>(*b));
				++b;
			}
		}
		catch (...) 
		{
			clear(_head);
			throw;
		}
	}


	/**
		@brief Assignment operator
		
		It copies all the elements from other into the set, changing its size accordingly.

		@param other the set used to fill the current set
		@return the current set whose elements have been modified
	*/
	set& operator=(const set& other) 
	{
		if (this != &other) 
		{
			set tmp(other);
			std::swap(_head, tmp._head);
			std::swap(_size, tmp._size);
		}
		return *this;
	}


	/**
		@brief Destructor

		It destroys all the elements in the set and deallocates all the storage capacity allocated.
	*/
	~set() 
	{
		clear(_head);
		_head = 0;
		_size = 0;
	}


	/**	
		@brief Add an element to the set

		It adds a new element to the current set with the
		value in input.

		@param val value of the new element
		@throw duplicated_element_exception
	*/
	void add(const T& val) 
	{
		if (_head == 0) 
			_head = new element(val);
		else
			add(val, *_head);
		++_size;
	}


	/**
		@brief Delete an element from the set

		It removes from the set the element whose
		value corresponds to the value toDelete in input.

		@param toDelete value of the element that has to be deleted
		@throw non_existent_element_exception
	*/
	void remove(const T& toDelete) 
	{
		if (_head == 0)
			throw non_existent_element_exception();
		else if (_equal(toDelete, _head->value)) 
		{
			element* tmp = _head;
			_head = _head->next;
			delete tmp;
		}
		else
			remove(toDelete, *_head);
		--_size;
	}


	/**
		@brief Get an element from the set

		It gets the i-th element of the set.
		The first element is at position 0. 
		The last element  is at position size − 1.
		
		@pre it is necessary that i < size
		@param i index of the element in the set
		@return the value of the element in i-th position 
	*/
	const T& operator[](unsigned int i) const 
	{
		assert(i < _size);
		return getElement(*_head, i);
	}


	/**
		@brief Get the number of elements in the set

		It returns the size of the set.

		@return the size of the set
	*/
	unsigned int size() const 
	{ 
		return _size; 
	}


	/**	
		@brief Forward const_iterator of the class

		It is used to iterate over the elements of the set.
	*/
	class const_iterator 
	{

		const element *ele;	

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                               value_type;
		typedef ptrdiff_t                       difference_type;
		typedef const T*                        pointer;
		typedef const T&                        reference;

		/** @brief Default constructor */
		const_iterator() : ele(0) 
		{}
		
		/** @brief Copy constructor */
		const_iterator(const const_iterator &other) : ele(other.ele) 
		{}

		/** @brief Assignment operator */
		const_iterator& operator=(const const_iterator &other) 
		{
			ele = other.ele;
			return *this;
		}

		/** @brief Destructor */
		~const_iterator() 
		{}

		/** @brief It returns the data pointed by the iterator */
		reference operator*() const 
		{
			return ele->value;
		}

		/** @brief It returns the pointer held by the iterator */
		pointer operator->() const 
		{
			return &(ele->value);
		}
		
		/** @brief Post-increment operation */
		const_iterator operator++(int) 
		{
			const_iterator tmp(*this);
			ele = ele->next;
			return tmp;
		}

		/** @brief Pre-increment operation */
		const_iterator &operator++() 
		{
			ele = ele->next;
			return *this;
		}

		/** @brief Equality */
		bool operator==(const const_iterator &other) const 
		{
			return ele == other.ele;
		}
		
		/** @brief Inequality */
		bool operator!=(const const_iterator &other) const 
		{
			return ele != other.ele;
		}

	private:

		// The container class must be friend of the iterator to allow the container class
		// to use the private constructor
		friend class set;

		// private default constructor used by the container class in begin() and end()
		// methods
		const_iterator(const element* e) : ele(e)
		{}
		
	}; // const_iterator class
	

	/**	
		@brief Get the forward const_iterator at the beginning of the data sequence

		It returns the forward const_iterator at the beginning of the data sequence.

		@return const_iterator at the beginning of the data sequence
	*/
	const_iterator begin() const 
	{
		return const_iterator(_head);
	}
	

	/**
		@brief Get the forward const_iterator at the end of the data sequence

		It returns the forward const_iterator at the end of the data sequence.

		@return const_iterator at the end of the data sequence
	*/
	const_iterator end() const 
	{
		return const_iterator(0);
	}

};

/**	
	@brief Stream operator <<

	Overriding of operator<< to write the elements of a set on a stream.
	
	@tparam T the type of elements stored in the set setToPrint
	@tparam Eql functor used to check whether two elements are equal or not
	@param os output stream on which an element is sent
	@param setToPrint the set to be sent on the output stream
	@return the reference of the output stream
*/
template<typename T, typename Eql>
std::ostream &operator<<(std::ostream &os, const set<T, Eql> &setToPrint) 
{
	typename set<T, Eql>::const_iterator ib, ie;
	for (ib = setToPrint.begin(), ie = setToPrint.end(); ib!=ie; ++ib) 
	{
		os << *ib << std::endl;
	}
	return os;
}


/**	
	@brief Filter out the elements of a set

	This function creates and returns a new set, whose elements come from
	a set in input that do NOT satisfy a certain predicate.
	
	@tparam T the type of elements stored in the set s
	@tparam Eql functor used to check whether two elements are equal or not
	@tparam Pred the predicate that musn't be satisfied
	@param s the set whose elements will be analyzed and saved if they do NOT satisfy the predicate Pred
	@return a new set containing the elements of s filtered out
*/
template<typename T, typename Eql, typename Pred>
set<T, Eql> filter_out(const set<T, Eql> &s, Pred pred) 
{
	set<T, Eql> resultSet;
	typename set<T, Eql>::const_iterator ib, ie;
	ib = s.begin();
	ie = s.end();
	while (ib != ie) 
	{
		if (!pred(*ib))
			resultSet.add(*ib);
		++ib;
	}
	return resultSet;
}


/**
	@brief Create a new set with the elements of two other sets	

	This function creates and returns a new set, whose elements come from
	the union of two sets in input.

	@tparam T the type of elements stored in the sets
	@tparam Eql functor used to check whether two elements are equal or not
	@param s1 the first set
	@param s2 the second set
	@return a new set of elements of s1 and s2
	@throw duplicated_element_exception if an element appears more than once in the sets
*/
template<typename T, typename Eql>
set<T, Eql> operator+(const set<T, Eql> &s1, const set<T, Eql> &s2) 
{

	// add the elements of s1
	set<T, Eql> resultSet(s1);

	// add the elements of s2
	typename set<T, Eql>::const_iterator ib, ie;
	ib = s2.begin();
	ie = s2.end();
	while (ib != ie) 
	{
		resultSet.add(*ib);
		++ib;
	}
	return resultSet;
}

#endif
