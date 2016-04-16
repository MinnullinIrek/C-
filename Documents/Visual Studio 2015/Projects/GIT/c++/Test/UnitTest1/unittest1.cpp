#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "Word.h"
#include "Words.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	struct Token {};
	typedef std::vector<Token> Tokens;
	inline Tokens Tokenize(std::string expr) 
	{
		throw std::exception(); 
	}

	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethodWord)
		{
			Word word1("qwerty");
			Word word2("qwertw");
			Assert::IsTrue(word1.Sravnenie(&word2));
			Word wordWrong("aaaaaa");
			Assert::IsFalse(word1.Sravnenie(&wordWrong));

		}

		TEST_METHOD(TestMethodWord2)
		{
			Word wordFirst("qwerty");
			Word wordLast("qxeatw");
			Word word3("qwertw");
			Word word4("qxertw");
			list<Word> controlWords;
			controlWords.push_back(wordFirst);
			controlWords.push_back(word3);
			controlWords.push_back(word4);
			controlWords.push_back(wordLast);

			list<Word> lwords;
			
			lwords.push_back(wordFirst);
			lwords.push_back(wordLast);
			lwords.push_back(word3);
			lwords.push_back(word4);

			Words words(lwords);

			list<Word> finalWords = words.GetWay();

			list<Word>::iterator itControl = controlWords.begin();
			for (list<Word>::iterator it = finalWords.begin(); it != finalWords.end(); ++it, ++itControl)
			{
				Assert::AreEqual(it->GetWord(), itControl->GetWord());
				//Assert::AreEqual("oo", "oo");
			}
			

			//Assert::IsFalse(word1.Sravnenie(&wordWrong));

		}


	};
}