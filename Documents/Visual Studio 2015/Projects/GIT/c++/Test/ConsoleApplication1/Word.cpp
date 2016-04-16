#include "stdafx.h"
#include "Word.h"


Word::Word(string word):_word(word), _num(-1)
{

}

bool Word::Sravnenie(Word* otherWord)
{
	if (otherWord->_word.length() != _word.length())
	{
		return false;
	}
	short int difers = 0;
	for (short int i = 0; i < otherWord->_word.length(); i++)
	{
		if (otherWord->_word[i] != _word[i])
		{
			difers++;
		}
	}

	if (difers == 1)
	{
		return true;
	}

	return false;
}

string Word::GetWord(void)
{
	return _word;
}



int Word::GetNum(void)
{
	return _num;
}

void Word::SetNum(int num)
{
	_num = num;
}

void Word::SetReference(list<Word>::iterator ref)
{
	reference = ref;
}

list<Word>::iterator Word::GetReference(void)
{
	return reference;
}

Word::~Word()
{
}
