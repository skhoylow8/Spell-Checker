/*
Setareh Khoylow 
Section 1A
Homework 2
ID: 305114410

I Setareh Khoylow declare that this work is my own. I did this work honestly and can fully stand behind everything I 
have written.
I did not copy from any other student or otherwise.
I collaborated with Francisco Borja and I affirm that we all econtributed equally to the code.
*/

#include <iostream>
#include<fstream>
#include "SpellCheck.h"

int main()
{
	std::cout << "Enter file to spell check: ";
	std::string fileName;
	std::cin >> fileName;


	SpellCheck file;

	file.read_dictionary("dictionary.txt");//reads the dictionary file

	file.process_file(fileName);//processes whatever file the user enters

	std::cin.get();

	return 0;
}