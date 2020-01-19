#include"SpellCheck.h"
#include<fstream>
#include<iostream>

/**
this function checks if there is a white space, a tab, or a new line in the file
@param mark takes in a a character and checks if its a white space, tab, or new line
@returns true if it is a white space, tab, or new line character
@returns false if its not
*/
bool is_white_space(char mark)
{
	//checks if the mark is a space, tab, or new line
	if (mark == ' ' || mark == '\t' || mark == '\n')
	{
		return true;//if it is return true
	}
	else
	{
		return false;//if it isn't return false
	}
}

/**
this function takes in a word and checks if it has a final punctuation or not
@param word is the first parmeter 
@returns true if the last character is a puncutation and false if its not
*/
bool final_punctuation(std::string word)
{
	//checks if it does have final punctuation at the end
	if (word.back() == '.' || word.back() == ',' || word.back() == '?' || word.back() == '!' || word.back() == ';' || word.back() == ':')
	{
		return true;//if it does return true
	}
	else
	{
		return false;//if it doesn't return false
	}
}

/**
this function checks is the first character of the word is a capital letter and changes is to a lower case if it is and if the last character is a punctuation then it removes it
@param input is passed by reference
*/
void depunctuate(std::string& input)
{
	char c = input.front();//sets c equal to the first character in the word
	if (('A' <= c) && (c <= 'Z'))//if it is uppercase
	{
		c += ('a' - 'A');//makes it lower case
		input.front() = c;
		
		//checks if the word has final punctuation at the end
		//final_punctuation(input);
	}
	//checks if the word has final punctuation at the end
	if (final_punctuation(input) == true)
	{
		input.pop_back();//if true erase it
	}
}

/**
this function takes in the dictionary file and reads the words and stores them in an unordered set
@param file name is the first variable
*/
void SpellCheck::read_dictionary(std::string file_name)
{
	std::ifstream fin;
	fin.open(file_name);//opens file

	if (fin.fail())//checks if it did open
	{
		std::cout << "Failed to open file.\n";//if it didn't display this
	}
	else
	{
		std::string temp;
		while (!fin.eof())//while it doesn't reach the end of the file
		{
			fin >> temp;//reads the word in the file
			dictionarySet.insert(temp);//inserts those words into the unordered set
		}
	}
	fin.close();//closes the file once its done reading it
}

/**
this function takes in a word, depunctuates it, checks if it has a punctuation and then tries to find the word in the dictionary set to determine if its valid
@param checkWord is the first value
@returns true if it was found in the dictionary and returns false if it wasn't
*/
bool SpellCheck::is_valid(std::string checkWord)
{
	depunctuate(checkWord);//depunctuates the word first because all word in the dictionary are lower case and don't have punctuation

	if (dictionarySet.find(checkWord) != dictionarySet.end())//looks for the word in the unordered set
	{
		return true;//if the word was found
	}
	else
	{
		return false;//if the word wasn't found 
	}
}

/**
This function takes in a file name and opens it. 
Once its open it first calls the white spaces function and adds them to the empty string called text.
Then it takes in a word and checks if its valid or not and if its not it adds stars to both sides of the word and adds it to the string.
If it is valid it just adds the word to the string.
@param file_name is the first value
*/
void SpellCheck::process_file(std::string file_name)
{
	std::string text = " ";//the initial text string that gets modified throughout the program

	std::ifstream text_file;
	text_file.open(file_name);//opens the file

	if (text_file.fail())//ifthe file failed to open then display the message below
	{
		std::cout << "Failed to open file.\n";
	}
	else
	{
		//while it doesn't reach the end of the file
		while (!text_file.eof())
		{
			char x = text_file.peek();//peeks into the text file character by character to see if its a white space
			while (text_file && is_white_space(x) == true)
			{
				text.push_back(x);//adds the white space to the string
				text_file.get();//removes the white space
				x = text_file.peek();//and looks at the next character to see if its a white space 
			}
			if (!text_file)
			{
				break;
			}
			
			std::string word;//stores a string with a variable name word
			text_file >> word;//takes the word from the file

			//if the word from the file is found in the dictionary than execute this if statement
			if (is_valid(word) == true)
			{
				text.append(word);//adds the word to the string text
			}
			else if (is_valid(word) == false)//and if its not execute the code below
			{
				if (final_punctuation(word) == true)//of there is final punctuation in the word then execute this code
				{
					char z = word.back();//stroes the punctuation in the varaible z
					word.pop_back();//erases the punctuation

					text.push_back('*');//adds the star to the text string
					text.append(word);//then adds the word without the punctuation to the text string
					text.push_back('*');//then adds the other star to the end of the word before the punctuation to the text string
					text.push_back(z);//then adds the punctuation to the text string
				}
				else//if it doesn't have a final punctuation then execute the code below
				{
					text.append("*");//adds a star to the text string 
					text.append(word);//then adds the word to the text string
					text.append("*");//then adds the second star to the text string
				}
			}
		}
		std::cout << text;//after reading the whole file it will display the text string to the console
	}
	text_file.close();//and then it closes the file
}