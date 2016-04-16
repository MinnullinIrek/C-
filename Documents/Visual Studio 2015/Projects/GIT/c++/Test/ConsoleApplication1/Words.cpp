#include "stdafx.h"
#include "Words.h"
using namespace std;

Words::Words(string fileName):stream(fileName)
{
	string sword;
	
	while (!stream.eof())
	{
		getline(stream, sword);
		Word word(sword);
		_words.push_back(word);		
	}
	list<Word>::iterator it = _words.begin();

	this->wordLast = it;
	it++;
	wordFirst = it;
	wordFirst->SetNum(0);
/*	if (wordFirst->GetWord().length() != wordLast->GetWord().length())
	{
		cout << "Слова имеют разную длину";
	}
	*/

}

Words::Words(list<Word> words):_words(words)
{
	list<Word>::iterator it = _words.begin();

	this->wordLast = it;
	it++;
	wordFirst = it;
	wordFirst->SetNum(0);
}

void Words::FindReferences(list<Word>::iterator word)
{
	for (list<Word>::iterator itWord = _words.begin(); itWord != _words.end(); itWord++)
	{
		if (word == itWord)
			continue;

		if (word->Sravnenie(&(*itWord)))
		{
			if (word->GetNum() < itWord->GetNum() || itWord->GetNum() == -1  )
			{
				itWord->SetNum(word->GetNum() + 1);
				itWord->SetReference(word);
			}
		}
	}
}

bool Words::FindAll()
{
	int curentNum = 0;
	bool isExist = false;
	while (wordLast->GetNum()==-1)
	{
		for (list<Word>::iterator itWord = _words.begin(); itWord != _words.end(); itWord++)
		{
			if (itWord->GetNum() == curentNum)
			{
				isExist = true;
				FindReferences(itWord);
			}
		}
		if (!isExist)
		{
			return false;
		}
		curentNum++;
		isExist = false;

	}
	return true;

}

list<Word> Words::GetWay(void)
{
	list<Word> way;
	if(!FindAll())
		return list<Word>();
	else
	{
		list<Word>::iterator itWord = wordLast;
		while (itWord!=this->wordFirst)
		{
			way.push_back(*itWord);
			itWord = itWord->GetReference();
		}
		
		way.push_back(*itWord);
		

	}
	return way;
}


Words::~Words()
{
}
