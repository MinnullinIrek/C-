// xORCpp.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>


using namespace std;

//выдает минимальное из 2х значений
size_t Min(size_t val1, size_t val2);
//зашифровывает(разшивровыает) buffer длиной bufferLength
//ключом key длиной keyLength
int XorShifr(char* buffer, const char* key, size_t bufferLength, size_t keyLength);

//сообщение об ешибке на консоль
void ErrorString(const char* serror);

//отладочные сообщения
void TraceMessage(const char* smessage);
//зашивровывает файл originFileName 
//в файл shifrFileName 
//ключом key длиной length
int ShifrFile(const char* originFileName, const char* shifrFileName, const char* key, size_t length);

size_t MyStrStr(char* pos, const char* searchingWord, size_t posLength );

//возвращает количество повторений searchingWord в originString длиной originLength
//зашифрованного ключом key длиной keyLength
int GetRepeatsInString(char * originString, size_t originLength, const char* key, size_t keyLength, const string& searchingWord)
{
	int repeat = 0;
	static string staticBuf;
	size_t bufferLength = staticBuf.length() + originLength + 1;
	char* localBuffer = new char[bufferLength];

	memset(localBuffer, 0, bufferLength);
	memcpy(localBuffer, staticBuf.c_str(), staticBuf.length());
	memcpy(localBuffer + staticBuf.length(), originString, originLength);

	char* pos = localBuffer;
	int posLength = bufferLength;
	repeat = MyStrStr(pos, searchingWord.c_str(), bufferLength);
	
	/*while (( posLength = MyStrStr(pos, searchingWord.c_str(),posLength ) != -1))
	{
		repeat++;
		pos += searchingWord.length();
	}*/
	pos = localBuffer + bufferLength  - searchingWord.length();

	if (originLength > searchingWord.length()&& !strstr(pos, searchingWord.c_str()))
	{
		staticBuf = localBuffer + bufferLength - searchingWord.length();
	}
	delete[] localBuffer;
	return repeat;
}
//все заглавные буквы в строчные
//void WordToDown(char* word, size_t length);
//количество повторений слова searchingWord
//в файле fileName 
//зашифрованного ключом key длиной keyLength
int FindRepeatsInFile(const char* fileName, const char* key, size_t keyLength, const string& searchingWord);



int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	const size_t length = 32;
	const char *xorKey = "0123456789ABCDEF0123456789ABCDEF";

	if (argc < 3)
	{
		ErrorString("Введите параметры имя файла и словдля поиска");
		return -1;
	}

	string fileName = argv[1];
	
	//WordToDown(argv[2], strlen(argv[2]));

	string searchingWord = argv[2];
	//ShifrFile("../xORCpp/crypted.xor", "../xORCpp/shifrMeCrypted.txt", xorKey, length);
	unsigned int repeat = FindRepeatsInFile(fileName.c_str(), xorKey, length, searchingWord);
	printf("слово '%s' встречается %d раз(а)", searchingWord.c_str(), repeat);
    return 0;
}

size_t MyStrStr(char* pos, const char* searchingWord, size_t posLength)
{
	int repeat = 0;
	for (size_t i = 0; i < posLength; i++)
	{
		if (pos[i] == searchingWord[0])
		{
			for (size_t j = 1; j < strlen(searchingWord); j++)
			{

				if (pos[i + j] != searchingWord[j])
					break;
				if (j + 1 == strlen(searchingWord))
				{
					i += j;
					repeat++;
				}
			}
		}
	}
	return repeat;
}

int FindRepeatsInFile(const char* fileName, const char* key, size_t keyLength, const string& searchingWord)
{
	FILE *file;
	errno_t er = fopen_s(&file, fileName, "rb");
	if (er != 0)
	{
		ErrorString("ошибка при открытии файла");
		return er;
	}

	char* buffer = new char[keyLength];
	size_t rwCount = 0;
	int repeat = 0;
	while ((rwCount = fread_s(buffer, keyLength, 1, keyLength, file)) > 0)
	{
		if (0 != (er = XorShifr(buffer, key, rwCount, keyLength)))
		{
			ErrorString("Ошибка при расшивровке");
			return -1;
		}
		//WordToDown(buffer, rwCount);

		repeat += GetRepeatsInString(buffer, rwCount, key, keyLength, searchingWord);
	}
	fclose(file);
	return repeat;
}
/*
void WordToDown(char* word, size_t length)
{
	for (size_t pos = 0; pos < length; pos++)
	{
		if (word[pos] >= 'A' && word[pos] <= 'Z')
		{
			word[pos] += 'a' - 'A';
		}
		if (word[pos] >= 'А' && word[pos] <= 'Я')
		{
			word[pos] += 'а' - 'А';
		}
	}

}
*/
int ShifrFile(const char* originFileName, const char* shifrFileName, const char* key, size_t length)
{
	FILE *originFile;
	errno_t er = fopen_s(&originFile, originFileName, "rb");

	if (er != 0)
	{
		return er;
	}

	FILE * shifrFile;
	er = fopen_s(&shifrFile, shifrFileName, "wb");

	if (er != 0)
	{
		return er;
	}
	char *buffer = new char[length];
	size_t rwCount = 0;
	while ((rwCount = fread_s(buffer, length, 1, length, originFile)) > 0)
	{
		XorShifr(buffer, key, rwCount, length);
		size_t wCount = fwrite(buffer, 1, rwCount, shifrFile);
		if (wCount < rwCount)
		{
			ErrorString("ошибка при записи");
		}

	}

	fclose(originFile);
	fclose(shifrFile);
	delete[] buffer;
	TraceMessage("файл зашифрован");
	return 0;
}
void TraceMessage(const char* smessage)
{
	printf("{%s}\n", smessage);
}
void ErrorString(const char* serror)
{
	printf("{Ошибка: %s}\n", serror);
}
int XorShifr(char* buffer, const char* key, size_t bufferLength, size_t keyLength)
{
	for (size_t i = 0; i < Min(bufferLength, keyLength); i++)
	{
		buffer[i] = buffer[i] ^ key[i];
	}

	return 0;
}
size_t Min(size_t val1, size_t val2)
{
	return (val1 < val2) ? val1 : val2;
}