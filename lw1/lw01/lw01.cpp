#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/timer.hpp>



int main()
{
	std::vector<size_t> v = { 1,2,3,4,5,6,7,8,9,10,11};

	// 10 - 0.045
	// 11 - 0.383


	boost::timer t;
	t.restart();
	std::sort(v.begin(), v.end());
	do
	{
		//copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
		//std::cout << std::endl;
	} while (std::next_permutation(v.begin(), v.end()));
	double duration = t.elapsed();

	std::cout << duration << std::endl;
}
