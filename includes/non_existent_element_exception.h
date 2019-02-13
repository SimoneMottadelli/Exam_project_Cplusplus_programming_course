#ifndef NON_EXISTENT_ELEMENT_EXCEPTION_H
#define NON_EXISTENT_ELEMENT_EXCEPTION_H

#include <stdexcept>
#include <string>

/**
	@file non_existent_element_exception.h
	@brief Declaration of a custom exception
**/

/**	
	@brief Declaration of a custom exception

	Custom exception which represents the event of a non existent element
	in a set. 
*/
class non_existent_element_exception : public std::runtime_error 
{

public:
	/**	@brief Default constructor

		Constructor without error messages in input.
	*/
	non_existent_element_exception();

	/**
		@brief Secondary constructor

		Constructor with an error message in input.
		
		@param message an error message
	*/
	non_existent_element_exception(const std::string &message);
};

#endif
