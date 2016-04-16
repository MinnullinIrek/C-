// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "Words.h"
#include <list>

void PrintWay(list<Word> words);
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	if (argc < 2)
	{
		printf("нужно имя файла");
	}
	string fileName = argv[1];
	Words words(fileName);
	
	PrintWay(words.GetWay());
	getchar();
    return 0;
}

void PrintWay(list<Word> words)
{
	if (words.size() == 0)
	{
		cout << "Не удалось построить цепочку";
	}
	for (list<Word>::iterator itWord = words.begin(); itWord != words.end(); itWord++)
	{
		cout << itWord->GetWord() << "\n";
	}
}