#ifndef DUPLICATED_ELEMENT_EXCEPTION_H
#define DUPLICATED_ELEMENT_EXCEPTION_H

#include <stdexcept>
#include <string>

/**
	@file duplicated_element_exception.h
	@brief Declaration of a custom exception
**/

/**
	@brief Declaration of a custom exception

	Custom exception which represents the event of a duplicated element
	in a set. 
*/
class duplicated_element_exception : public std::runtime_error 
{

public:
	/**	
		@bried Default constructor
		
		Constructor without error messages in input.
	*/
	duplicated_element_exception();

	/**	@brief Secondary constructor

		Constructor with an error message in input.

		@param message an error message
	*/
	duplicated_element_exception(const std::string &message);
};

#endif
