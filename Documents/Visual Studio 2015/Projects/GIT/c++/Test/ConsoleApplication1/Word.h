#pragma once
#include <string>
#include <list>
using namespace std;
class Word
{
	//слово
	string _word;
	//номер в цепочке
	int _num;
	//ссылка на предыдущий элемент в цепочке
	list<Word>::iterator reference;

public:
	Word(string word);

	//удовлетворяет ли слово условию(отличается не более одного символа)
	bool Sravnenie(Word* otherWord);

	string GetWord(void);
	
	int GetNum(void);
	void SetNum(int num);

	void SetReference(list<Word>::iterator ref);
	list<Word>::iterator GetReference(void);


	~Word();
};

