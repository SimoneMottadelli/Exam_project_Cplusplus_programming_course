#include "student.h"

student::student() : age(0), name("") 
{}

student::student(unsigned int a, std::string n) : age(a), name(n) 
{}

student::student(const student& other) : age(other.age), name(other.name) 
{}

student& student::operator=(const student& other) 
{
	if (this != &other) {
			student tmp(other);
			std::swap(age, tmp.age);
			std::swap(name, tmp.name);
		}
	return *this;
}

student::~student() {}

bool student::operator==(const student& other) const 
{
	return name == other.name && age == other.age;
}

std::ostream &operator<<(std::ostream &os, const student st) 
{
	os << st.name << " " << st.age;
	return os;
}
