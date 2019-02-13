#include "set.h"
#include <string>
#include <iostream>
#include <list>
#include "duplicated_element_exception.h"
#include "non_existent_element_exception.h"
#include "student.h"

// == FUNCTORS USED FOR TESTING ==

/**
	@brief A functor for testing

	It returns true if and only if two integers are equal.
*/
struct equal_int 
{
	bool operator()(int a, int b) const 
	{
		return a == b;
	}
};


/**
	@brief A functor for testing

	It returns true if and only if two std::string are equal.
*/
struct equal_string 
{
	bool operator()(std::string a, std::string b) const 
	{
		return a == b;
	}
};

/**
	@brief A functor for testing

	It returns true if and only if two students are equal.
*/
struct equal_student 
{
	bool operator()(student a, student b) const 
	{
		return a == b;
	}
};


// == PREDICATES USED FOR TESTING ==

/**
	@brief A predicate for testing

	It returns true if and only if a std::string has a length different from 6.
*/
struct hasnt_six_characters 
{
	bool operator()(std::string a) const 
	{
		return a.size() != 6;
	}
};

/**
	@brief A predicate for testing

	It returns true if and only if a student is eighteen years old or older.
*/
struct over_18 
{
	bool operator()(student a) const 
	{
		return a.age >= 18;
	}
};

/**
	@brief A predicate for testing

	It returns true if and only if an integer is even.
*/
struct is_even 
{
	bool operator()(int a) const 
	{
		return a % 2 == 0;
	}
};

/**
	@brief A predicate for testing

	It returns true if and only if an integer is odd.
*/
struct is_odd 
{
	bool operator()(int a) const 
	{
		return a % 2 != 0;
	}
};


// == TYPE DEFINITIONS ==
typedef set<int, equal_int> set_int_type;
typedef set<std::string, equal_string> set_string_type;
typedef set<student, equal_student> set_student_type;


// == TEST FUNCTIONS ==
void testClassFunctionsWithIntegers() 
{

	// test default constructor
	set_int_type firstSet;
	assert(0 == firstSet.size());

	//test add and cardinality
	try 
	{
		firstSet.add(5);
		firstSet.add(3);
		firstSet.add(42);
		firstSet.add(1);
		firstSet.add(8);
		firstSet.add(6);	
	} 
	catch(duplicated_element_exception e) 
	{
		assert(false); // there shouldn't be any exception thrown
	}
	assert(6 == firstSet.size());
	assert(5 == firstSet[0]);
	assert(3 == firstSet[1]);
	assert(42 == firstSet[2]);
	assert(1 == firstSet[3]);
	assert(8 == firstSet[4]);
	assert(6 == firstSet[5]);

	//test add with exceptions
	try 
	{
		firstSet.add(5);
		assert(false); //an exception should be thrown
	}
	catch(duplicated_element_exception e) 
	{
		assert(6 == firstSet.size());
	}

	try 
	{
		firstSet.add(6);
		assert(false); //an exception should be thrown
	}
	catch(duplicated_element_exception e) 
	{
		assert(6 == firstSet.size());
	}

	try 
	{
		firstSet.add(1);
		assert(false); //an exception should be thrown
	}
	catch(duplicated_element_exception e) 
	{
		assert(6 == firstSet.size());
	}

	//test copy constructor
	set_int_type secondSet(firstSet);
	assert(6 == secondSet.size());
	assert(5 == secondSet[0]);
	assert(3 == secondSet[1]);
	assert(42 == secondSet[2]);
	assert(1 == secondSet[3]);
	assert(8 == secondSet[4]);
	assert(6 == secondSet[5]);

	//test remove
	try 
	{
		secondSet.remove(3);
		secondSet.remove(5);
		secondSet.remove(6);
		secondSet.remove(1);
		secondSet.add(820786);
	}
	catch (...) 
	{
		assert(false); //no exceptions should be thrown
	}
	assert(3 == secondSet.size());
	assert(42 == secondSet[0]);
	assert(8 == secondSet[1]);
	assert(820786 == secondSet[2]);

	//test remove with exceptions
	try 
	{
		secondSet.remove(6);
		assert(false); //an exception should be thrown
	}
	catch(non_existent_element_exception e) 
	{
 		assert(3 == secondSet.size());
	}

	// test assignment
	firstSet = secondSet;
	assert(3 == firstSet.size());
	assert(42 == firstSet[0]);
	assert(8 == firstSet[1]);
	assert(820786 == firstSet[2]);


	// constructor with iterators
	std::list<int> listIntegers;
	listIntegers.push_back(5);
	listIntegers.push_back(4);
	listIntegers.push_back(3);
	listIntegers.push_back(6);
	try 
	{
		set_int_type thirdSet(listIntegers.begin(), listIntegers.end());
		assert(4 == thirdSet.size());
		assert(5 == thirdSet[0]);
		assert(4 == thirdSet[1]);
		assert(3 == thirdSet[2]);
		assert(6 == thirdSet[3]);
	}
	catch(duplicated_element_exception e) 
	{
		assert(false); //no exceptions should be thrown
	}

	listIntegers.push_back(4);
	try 
	{
		set_int_type thirdSet(listIntegers.begin(), listIntegers.end());
		assert(false); //an exception should be thrown
	}
	catch(duplicated_element_exception e) 
	{ 
		/* okay */
	}
}

void testClassFunctionsWithStrings() 
{

	// test default constructor
	set_string_type firstSet;
	assert(0 == firstSet.size());

	//test add and cardinality
	try 
	{
		firstSet.add("5");
		firstSet.add("3");
		firstSet.add("42");
		firstSet.add("1");
		firstSet.add("8");
		firstSet.add("6");	
	} 
	catch(duplicated_element_exception e) 
	{
		assert(false); // there shouldn't be any exception thrown
	}
	assert(6 == firstSet.size());
	assert("5" == firstSet[0]);
	assert("3" == firstSet[1]);
	assert("42" == firstSet[2]);
	assert("1" == firstSet[3]);
	assert("8" == firstSet[4]);
	assert("6" == firstSet[5]);

	//test add with exceptions
	try 
	{
		firstSet.add("5");
		assert(false); //an exception should be thrown
	}
	catch(duplicated_element_exception e) 
	{
		assert(6 == firstSet.size());
	}

	try 
	{
		firstSet.add("6");
		assert(false); //an exception should be thrown
	}
	catch(duplicated_element_exception e) 
	{
		assert(6 == firstSet.size());
	}

	try 
	{
		firstSet.add("1");
		assert(false); //an exception should be thrown
	}
	catch(duplicated_element_exception e) 
	{
		assert(6 == firstSet.size());
	}

	//test copy constructor
	set_string_type secondSet(firstSet);
	assert(6 == secondSet.size());
	assert("5" == secondSet[0]);
	assert("3" == secondSet[1]);
	assert("42" == secondSet[2]);
	assert("1" == secondSet[3]);
	assert("8" == secondSet[4]);
	assert("6" == secondSet[5]);

	//test remove
	try 
	{
		secondSet.remove("3");
		secondSet.remove("5");
		secondSet.remove("6");
		secondSet.remove("1");
		secondSet.add("820786");
	}
	catch (...) 
	{
		assert(false); //no exceptions should be thrown
	}
	assert(3 == secondSet.size());
	assert("42" == secondSet[0]);
	assert("8" == secondSet[1]);
	assert("820786" == secondSet[2]);

	//test remove with exceptions
	try 
	{
		secondSet.remove("6");
		assert(false); //an exception should be thrown
	}
	catch(non_existent_element_exception e) 
	{
 		assert(3 == secondSet.size());
	}

	// test assignment
	firstSet = secondSet;
	assert(3 == firstSet.size());
	assert("42" == firstSet[0]);
	assert("8" == firstSet[1]);
	assert("820786" == firstSet[2]);


	// constructor with iterators
	std::list<std::string> listStrings;
	listStrings.push_back("5");
	listStrings.push_back("4");
	listStrings.push_back("3");
	listStrings.push_back("6");
	try 
	{
		set_string_type thirdSet(listStrings.begin(), listStrings.end());	
		assert(4 == thirdSet.size());
		assert("5" == thirdSet[0]);
		assert("4" == thirdSet[1]);
		assert("3" == thirdSet[2]);
		assert("6" == thirdSet[3]);
	} 
	catch(duplicated_element_exception e) 
	{
		assert(false);
	}

	listStrings.push_back("6");
	try 
	{
		set_string_type thirdSet(listStrings.begin(), listStrings.end());
		assert(false); //an exception should be thrown	
	} 
	catch(duplicated_element_exception e) 
	{
		// okay
	}
}

void testStreamOperatorStrings() 
{

	std::cout << std::endl << "== BEGIN test stream operator<< strings ==" << std::endl;

	set_string_type mySet;

	try 
	{
		mySet.add("Simone");
		mySet.add("Giovanni");
		mySet.add("Francesco");
		mySet.add("Carlo");
		mySet.add("Paolo");
	}
	catch (duplicated_element_exception e) 
	{
		assert(false); // no exceptions should be thrown
	}
	

	std::cout << mySet;

	std::cout << "== END test stream operator<< strings ==" << std::endl;
}

void testStreamOperatorIntegers() 
{

	std::cout << std::endl << "== BEGIN test stream operator<< integers ==" << std::endl;

	set_int_type mySet;

	try 
	{
		mySet.add(1);
		mySet.add(2);
		mySet.add(3);
		mySet.add(4);
		mySet.add(5);
	}
	catch (duplicated_element_exception e) 
	{
		assert(false); //no exceptions should be thrown
	}

	std::cout << mySet;

	std::cout << "== END test stream operator<< integers ==" << std::endl;
}

void test_filter_out_integers() 
{
	set_int_type mySet;
	try {
		mySet.add(88);
		mySet.add(77);
		mySet.add(11);
		mySet.add(7);
		mySet.add(6);
		mySet.add(4);
		mySet.add(5);
		mySet.add(8);
	}
	catch(duplicated_element_exception e) 
	{
		assert(false); //no exceptions should be thrown
	}

	is_even pred;

	set_int_type filteredSetOdd = filter_out(mySet, pred);

	assert(77 == filteredSetOdd[0]);
	assert(11 == filteredSetOdd[1]);
	assert(7 == filteredSetOdd[2]);
	assert(5 == filteredSetOdd[3]);

	is_odd pred2;

	set_int_type filteredSetEven = filter_out(mySet, pred2);
	assert(88 == filteredSetEven[0]);
	assert(6 == filteredSetEven[1]);
	assert(4 == filteredSetEven[2]);
	assert(8 == filteredSetEven[3]);

	
}

void test_filter_out_strings() 
{
	set_string_type mySet;

	try 
	{
		mySet.add("aaaaaa");
		mySet.add("bbbbbb");
		mySet.add("Hellooooo");
		mySet.add("ciao");
		mySet.add("cccccc");
	}
	catch(duplicated_element_exception e) 
	{
		assert(false); //no exceptions should be thrown
	}

	hasnt_six_characters pred;

	set_string_type filteredSet = filter_out(mySet, pred);

	assert(filteredSet.size() == 3);
	assert(filteredSet[0] == "aaaaaa");
	assert(filteredSet[1] == "bbbbbb");
	assert(filteredSet[2] == "cccccc");
}

void test_operatorPlus_integers() 
{
	set_int_type mySet1, mySet2;
	try 
	{
		mySet1.add(77);
		mySet1.add(7);
		mySet1.add(6);
		mySet2.add(88);
		mySet2.add(76);
		mySet2.add(11);
		set_int_type mySetUnion = mySet1 + mySet2;
		assert(77 == mySetUnion[0]);
		assert(7 == mySetUnion[1]);
		assert(6 == mySetUnion[2]);
		assert(88 == mySetUnion[3]);
		assert(76 == mySetUnion[4]);
		assert(11 == mySetUnion[5]);
		try 
		{
			mySetUnion = mySetUnion + mySet2;
			assert(false); //an exception should be thrown
		} 
		catch(duplicated_element_exception e) 
		{ 
			/* okay */ 
		}
	}
	catch (duplicated_element_exception e) 
	{
		assert(false); //no exceptions should be thrown
	}
}

void test_operatorPlus_strings() 
{
	set_string_type mySet1, mySet2;
	try 
	{
		mySet1.add("77");
		mySet1.add("7");
		mySet1.add("6");
		mySet2.add("88");
		mySet2.add("76");
		mySet2.add("11");
		set_string_type mySetUnion = mySet1 + mySet2;
		assert("77" == mySetUnion[0]);
		assert("7" == mySetUnion[1]);
		assert("6" == mySetUnion[2]);
		assert("88" == mySetUnion[3]);
		assert("76" == mySetUnion[4]);
		assert("11" == mySetUnion[5]);	
		try 
		{
			mySetUnion = mySetUnion + mySet2;
			assert(false); //an exception should be thrown
		} 
		catch(duplicated_element_exception e) 
		{ 
			/* okay */ 
		}
	}
	catch(duplicated_element_exception e) 
	{
		assert(false); //no exceptions should be thrown
	}
}

void testClassFunctionsWithStudentType() 
{
	// test default constructor
	set_student_type firstSet;
	assert(0 == firstSet.size());

	//test add and cardinality
	try 
	{
		firstSet.add(student(21, "Simone"));
		firstSet.add(student(20, "Francesco"));
		firstSet.add(student(15, "Ambrosio"));
		firstSet.add(student(13, "Carlo"));
		firstSet.add(student(20, "Yosef"));
		firstSet.add(student(23, "Yan"));	
	} 
	catch(duplicated_element_exception e) 
	{
		assert(false); // there shouldn't be any exception thrown
	}
	assert(6 == firstSet.size());
	assert(student(21, "Simone") == firstSet[0]);
	assert(student(20, "Francesco") == firstSet[1]);
	assert(student(15, "Ambrosio") == firstSet[2]);
	assert(student(13, "Carlo") == firstSet[3]);
	assert(student(20, "Yosef") == firstSet[4]);
	assert(student(23, "Yan") == firstSet[5]);

	//test add with exceptions
	try 
	{
		firstSet.add(student(23, "Yan"));
		assert(false); //an exception should be thrown
	}
	catch(duplicated_element_exception e) 
	{
		assert(6 == firstSet.size());
	}

	try 
	{
		firstSet.add(student(21, "Simone"));
		assert(false); //an exception should be thrown
	}
	catch(duplicated_element_exception e) 
	{
		assert(6 == firstSet.size());
	}

	try 
	{
		firstSet.add(student(13, "Carlo"));
		assert(false); //an exception should be thrown
	}
	catch(duplicated_element_exception e) 
	{
		assert(6 == firstSet.size());
	}

	//test copy constructor
	set_student_type secondSet(firstSet);
	assert(6 == secondSet.size());
	assert(student(21, "Simone") == secondSet[0]);
	assert(student(20, "Francesco") == secondSet[1]);
	assert(student(15, "Ambrosio") == secondSet[2]);
	assert(student(13, "Carlo") == secondSet[3]);
	assert(student(20, "Yosef") == secondSet[4]);
	assert(student(23, "Yan") == secondSet[5]);

	//test remove
	try 
	{
		secondSet.remove(student(20, "Francesco"));
		secondSet.remove(student(21, "Simone"));
		secondSet.remove(student(20, "Yosef"));
		secondSet.remove(student(23, "Yan"));
		secondSet.add(student(26, "Luca"));
	}
	catch (...) 
	{
		assert(false); //no exceptions should be thrown
	}
	assert(3 == secondSet.size());
	assert(student(15, "Ambrosio") == secondSet[0]);
	assert(student(13, "Carlo") == secondSet[1]);
	assert(student(26, "Luca") == secondSet[2]);

	//test remove with exceptions
	try 
	{
		secondSet.remove(student(13, "Carlo2"));
		assert(false); //an exception should be thrown
	}
	catch(non_existent_element_exception e) 
	{
 		assert(3 == secondSet.size());
	}

	// test assignment
	firstSet = secondSet;
	assert(3 == firstSet.size());
	assert(student(15, "Ambrosio") == firstSet[0]);
	assert(student(13, "Carlo") == firstSet[1]);
	assert(student(26, "Luca") == firstSet[2]);


	// constructor with iterators
	std::list<student> listStudents;
	listStudents.push_back(student(22, "Luca"));
	listStudents.push_back(student(26, "Marco"));
	listStudents.push_back(student(25, "Giovanni"));
	listStudents.push_back(student(24, "Antonio"));
	set_student_type thirdSet(listStudents.begin(), listStudents.end());
	assert(4 == thirdSet.size());
	assert(student(22, "Luca") == thirdSet[0]);
	assert(student(26, "Marco") == thirdSet[1]);
	assert(student(25, "Giovanni") == thirdSet[2]);
	assert(student(24, "Antonio") == thirdSet[3]);
}

void test_filter_out_studentType() 
{
	set_student_type mySet;
	try {
		mySet.add(student(13, "Carlo"));
		mySet.add(student(6, "Franceschino"));
		mySet.add(student(23, "Paolo"));
		mySet.add(student(21, "Genoveffo"));
		mySet.add(student(18, "Osvaldo"));
		mySet.add(student(17, "Carim"));
		mySet.add(student(19, "Lorenzo"));
		mySet.add(student(26, "Silvio"));
	}
	catch(duplicated_element_exception e) 
	{
		assert(false); //no exceptions should be thrown
	}


	over_18 pred;

	set_student_type filteredSetOver18 = filter_out(mySet, pred);

	assert(student(13, "Carlo") == filteredSetOver18[0]);
	assert(student(6, "Franceschino") == filteredSetOver18[1]);
	assert(student(17, "Carim") == filteredSetOver18[2]);
}

void test_operatorPlus_studentType() 
{
	set_student_type mySet1, mySet2;
	try 
	{
		mySet1.add(student(13, "Carlo"));
		mySet1.add(student(6, "Franceschino"));
		mySet2.add(student(14, "Carlo"));
		mySet2.add(student(7, "Franceschino"));
		set_student_type setUnion = mySet1 + mySet2;
		assert(student(13, "Carlo") == setUnion[0]);
		assert(student(6, "Franceschino") == setUnion[1]);
		assert(student(14, "Carlo") == setUnion[2]);
		assert(student(7, "Franceschino") == setUnion[3]);
		try 
		{
			setUnion = setUnion + mySet2;
			assert(false); //an exception should be thrown
		}
		catch(duplicated_element_exception e) 
		{ 
			/* okay */
		}
	}
	catch (duplicated_element_exception e) 
	{
		assert(false); // no exceptions should be thrown
	}
}

void testStreamOperatorStudentType() 
{

	std::cout << std::endl << "== BEGIN test stream operator<< students ==" << std::endl;

	set_student_type mySet;

	try 
	{
		mySet.add(student(13, "Simone"));
		mySet.add(student(14, "Giovanni"));
		mySet.add(student(15, "Ludovico"));
	}
	catch(duplicated_element_exception e) 
	{
		assert(false); //no exceptions should be thrown
	}

	std::cout << mySet;

	std::cout << "== END test stream operator<< students ==" << std::endl;
}


// == MAIN FUNCTION ==

int main(int argc, char *argv[]) 
{

	//test integers
	testClassFunctionsWithIntegers();
	test_filter_out_integers();
	test_operatorPlus_integers();
	testStreamOperatorIntegers();

	//test strings
	testClassFunctionsWithStrings();
	test_filter_out_strings();
	test_operatorPlus_strings();
	testStreamOperatorStrings();

	//test custom types
	testClassFunctionsWithStudentType();
	test_filter_out_studentType();
	test_operatorPlus_studentType();
	testStreamOperatorStudentType();

	return 0;
}
