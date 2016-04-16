#pragma once
#include <list>
#include <vector>
#include "Word.h"
#include <fstream>

using namespace std;

class Words
{
	ifstream stream;
	//список слов
	list<Word> _words;
	//первое слово в цепочке
	list<Word>::iterator wordFirst;
	//последнее слово в цепочке
	list<Word>::iterator wordLast;
	//поиск слов подходящих в качестве следующего звена
	void FindReferences(list<Word>::iterator word);
	//поиск слов в цепочке с присваением номера  в данной цепочке
	bool FindAll();

public:
	Words(string fileName);
	Words(list<Word> words);

	//возвращает список слов в цепочке от первого до последнего
	list<Word> GetWay(void);

	~Words();
};

