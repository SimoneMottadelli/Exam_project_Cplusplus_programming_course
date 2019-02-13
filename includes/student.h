#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <ostream>

/**
	@file student.h
	@brief Declaration of a custom class used for testing
*/

/**
	@brief Declaration of a custom class used for testing
	
	This struct represents an abstraction of a student.
	It is used for testing.

*/
struct student 
{

	unsigned int age; ///< age of the student
	std::string name; ///< name of the student

	/**
		@brief Default constructor

		It is used to create a new student that has an empty
		string as a name and 0 as age.
	*/
	student();

	/**
		@brief Secondary constructor

		It is used to create a student with an age and a name
		passed in input.

		@param a age of the student
		@param n name of the student
	*/
	student(unsigned int a, std::string n);

	/**
		@brief Copy constructor

		It is used to create a student based on another
		student passed in input.

		@param other the other student to copy
	*/
	student(const student& other);

	/**
		@brief Assignment operator
		
		A student is assigned to another student.

		@param other the student to copy
	*/
	student& operator=(const student& other);

	/**
		@brief Destructor
	*/
	~student();

	/**
		@brief Operator==

		Two students are equal if and only if their names and ages are equal

		@param other the other student to compare
		@return true if they are the same student, false otherwise
	*/
	bool operator==(const student& other) const;

};

/**
	@brief Stream operator<<

	@param os the output stream
	@param st the student to be sent to the output stream
	@return a reference to the output stream passed in input
*/
std::ostream &operator<<(std::ostream &os, const student st);

#endif
