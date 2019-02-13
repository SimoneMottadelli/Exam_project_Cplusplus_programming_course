#include "non_existent_element_exception.h"

non_existent_element_exception::non_existent_element_exception() 
	: std::runtime_error("") 
{}

non_existent_element_exception::non_existent_element_exception(const std::string &message) 
	: std::runtime_error(message) 
{}
