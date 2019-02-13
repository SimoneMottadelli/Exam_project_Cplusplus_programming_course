GXX = g++
OPTIONS = -Wall -pedantic
MODE = 
INCLUDES = -I./includes
SRC = ./src/

main.exe: main.o duplicated_element_exception.o non_existent_element_exception.o student.o
	$(GXX) main.o duplicated_element_exception.o non_existent_element_exception.o student.o -o main.exe
	-rm *.o
	
main.o: main.cpp 
	$(GXX) -c $(OPTIONS) $(INCLUDES) main.cpp -o main.o

duplicated_element_exception.o: $(SRC)duplicated_element_exception.cpp
	$(GXX) -c $(OPTIONS) $(INCLUDES) $(SRC)duplicated_element_exception.cpp -o duplicated_element_exception.o

non_existent_element_exception.o: $(SRC)non_existent_element_exception.cpp
	$(GXX) -c $(OPTIONS) $(INCLUDES) $(SRC)non_existent_element_exception.cpp -o non_existent_element_exception.o

student.o: $(SRC)student.cpp
	$(GXX) -c $(OPTIONS) $(INCLUDES) $(SRC)student.cpp -o student.o

clearAll:
	-rm *.o *.exe