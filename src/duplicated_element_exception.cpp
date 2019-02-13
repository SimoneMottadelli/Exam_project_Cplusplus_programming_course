#include "duplicated_element_exception.h"

duplicated_element_exception::duplicated_element_exception() 
	: std::runtime_error("") 
{}

duplicated_element_exception::duplicated_element_exception(const std::string &message) 
	: std::runtime_error(message) 
{}
