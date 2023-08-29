#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;
constexpr int length = 28;

void initSetOfNumbers(vector<int>& SetOfNumbers, int length)
{
	for (int i = 0; i < length; i++)
	{
		SetOfNumbers.push_back(i + 1);
	}
}

void shuffleTheDeck(vector<int>& SetOfNumbers)
{
	int cardPosition;
	for (size_t i = 0; i < SetOfNumbers.size(); i++)
	{
		cardPosition = rand() % SetOfNumbers.size();
		if (i != cardPosition)
		{
			swap(SetOfNumbers.at(i), SetOfNumbers.at(cardPosition));
		}
	}
}

void showDeck(vector<int>& SetOfNumbers)
{
	for (size_t i = 0; i < SetOfNumbers.size(); i++)
	{
		cout << SetOfNumbers.at(i) << ", ";
	}
	cout << endl;
}

int main()
{
	srand(time(0));
	vector<int> SetOfNumbers;
	initSetOfNumbers(SetOfNumbers, length);

	cout << "Initiall set of numbers:" << endl;
	showDeck(SetOfNumbers);
	shuffleTheDeck(SetOfNumbers);
	cout << endl
		<< "Shuffled set of numbers: " << endl;
	showDeck(SetOfNumbers);

	return 0;
}