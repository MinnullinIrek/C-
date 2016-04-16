#pragma once
#include <string>
#include <list>
using namespace std;
class Word
{
	//�����
	string _word;
	//����� � �������
	int _num;
	//������ �� ���������� ������� � �������
	list<Word>::iterator reference;

public:
	Word(string word);

	//������������� �� ����� �������(���������� �� ����� ������ �������)
	bool Sravnenie(Word* otherWord);

	string GetWord(void);
	
	int GetNum(void);
	void SetNum(int num);

	void SetReference(list<Word>::iterator ref);
	list<Word>::iterator GetReference(void);


	~Word();
};

