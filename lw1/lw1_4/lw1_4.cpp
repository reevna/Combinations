#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>
#include <boost/timer.hpp>

void PrintVector(const std::vector<int>& v, const unsigned int offset = 0)
{
	copy(v.begin() + offset, v.end(), std::ostream_iterator<int>(std::cout, ""));
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid count  of arguments";
		return 1;
	}

	const size_t k = std::stoi(argv[1]);
	const size_t n = std::stoi(argv[2]);
	if (k > n)
	{
		std::cout << "Invalid args" << std::endl;
		return 1;
	}

	std::vector<int> combination(k + 1);
	char m = 1;
	combination[0] = -1;
	iota(combination.begin() + 1, combination.end(), 1);

	boost::timer time;
	time.restart();
	while (m != 0)
	{
		//PrintVector(combination, 1);
		m = k;

		while (combination[m] == n - k + m)
		{
			--m;
		}
		++combination[m];
		for (int i = m + 1; i <= k; ++i)
		{
			combination[i] = combination[i - 1] + 1;
		}
	}
	printf("Time: %.3f \n", time.elapsed());
}

// k=5
// n 10 = 0, 00
// n 20 = 0, 00
// n 50 =  0.007
//n 100 = 0.186
