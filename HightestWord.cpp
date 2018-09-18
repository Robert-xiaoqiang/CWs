#include <string>
#include <iostream>
#include <sstream>

int getScore(const std::string& str)
{
	int ret = 0;
	for(auto i : str) {
		ret += i - 'a' + 1;
	}

	return ret;
}

std::string highestScoringWord(const std::string &str)
{
	std::string ret;
	int maxScore = 0;

	std::istringstream is(str);
	std::string work;
	while(is >> work) {
		int score = getScore(work);
		//std::cout << score << std::endl;
		if(score > maxScore || 
		   score == maxScore && work < ret) {
			maxScore = score;
			ret = work;
		}
	}

	return ret;
}

int main()
{
	std::cout << highestScoringWord("man i need a taxi up to ubud") << std::endl;
	return 0;
}