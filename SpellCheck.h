#ifndef SPELL_CHECK
#define SPELL_CHECK
#include<unordered_set>
#include<string>

class SpellCheck {
public:
	void read_dictionary(std::string file_text);//reads the dictionary file
	bool is_valid(std::string checkWord);//checks to see if the word if valid
	void process_file(std::string file_name);//processes any file
private:
	std::unordered_set<std::string> dictionarySet;//stores the dictionary words in an unordered set
};

//non member function
bool final_punctuation(std::string word);//checks if the word has final punctuation
void depunctuate(std::string& input);//makes the first letter lower case if it is uppper case and removes the last punctuation
bool is_white_space(char mark);//checks if there is white space, a tab or a new line

#endif