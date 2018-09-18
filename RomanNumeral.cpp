#include <string>
#include <map>
#include <functional>
#include <iostream>

class RomanNumeralHelper {
public:
	std::string toRoman(int value);
	int fromRoman(const std::string& str);
private:
	static std::map<int, std::string, std::greater<int>> toRomanMap;
};

std::map<int, std::string, std::greater<int>> RomanNumeralHelper::toRomanMap = {
	{ 1, "I" },
	{ 4, "IV" },
	{ 5, "V" },
	{ 9, "IX" },
	{ 10, "X" },
	{ 40, "XL" },
	{ 50, "L" },
	{ 90, "XC" },
	{ 100, "C" },
	{ 400, "CD" },
	{ 500, "D" },
	{ 900, "CM" },
	{ 1000, "M" }
};

std::string RomanNumeralHelper::toRoman(int value)
{
	std::string res;
	for(auto ite = toRomanMap.begin(); ite != toRomanMap.end(); ite++) {
		while(ite->first <= value) {
			res += ite->second;
			value -= ite->first;
		}
	}
	return res;
}

int RomanNumeralHelper::fromRoman(const std::string& str)
{
	std::string::size_type index = 0;
	int ret = 0;
	while(index < str.size()) {
		if(str[index] == 'M') {
			ret += 1000;
			index++;
		} else if(str[index] == 'D') {
			ret += 500;
			index++;
		} else if(str[index] == 'C') {
			if(str[index + 1] == 'D') {
				ret += 400;
				index += 2;
			} else if(str[index + 1] == 'M') {
				ret += 500;
				index += 2;
			} else {
				ret += 100;
				index++;
			}
		} else if(str[index] == 'L') {
			ret += 50;
			index++;
		} else if(str[index] == 'X') {
			if(str[index + 1] == 'C') {
				ret += 90;
				index += 2;
			} else if(str[index + 1] == 'L') {
				ret += 40;
				index += 2;
			} else {
				ret += 10;
				index++;
			}
		} else if(str[index] == 'V') {
			ret += 5;
			index++;
		} else if(str[index] == 'I') {
			if(str[index + 1] == 'V') {
				ret += 4;
				index += 2;
			} else if(str[index + 1] == 'X') {
				ret += 9;
				index += 2;
			} else {
				ret += 1;
				index++;
			}
		} 
	}
	return ret;
}

int main()
{
	RomanNumeralHelper r;
	std::cout << r.fromRoman(r.toRoman(1666)) << std::endl;
}
