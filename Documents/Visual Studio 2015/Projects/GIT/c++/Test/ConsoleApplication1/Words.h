#pragma once
#include <list>
#include <vector>
#include "Word.h"
#include <fstream>

using namespace std;

class Words
{
	ifstream stream;
	//������ ����
	list<Word> _words;
	//������ ����� � �������
	list<Word>::iterator wordFirst;
	//��������� ����� � �������
	list<Word>::iterator wordLast;
	//����� ���� ���������� � �������� ���������� �����
	void FindReferences(list<Word>::iterator word);
	//����� ���� � ������� � ����������� ������  � ������ �������
	bool FindAll();

public:
	Words(string fileName);
	Words(list<Word> words);

	//���������� ������ ���� � ������� �� ������� �� ����������
	list<Word> GetWay(void);

	~Words();
};

