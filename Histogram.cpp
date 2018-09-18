#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <iomanip>

void rstrip(std::string& line)
{
	if(!line.empty()) {
		auto i = std::find_if(line.rbegin(), line.rend(),
			[](char ch) {return !isspace(ch); });
		if(isspace(line.back())) {
			line.erase(std::find_if(line.rbegin(), line.rend(),
				[](char ch) {return !isspace(ch); }).base(), line.end());
		}
	}
}

std::string histogram(std::vector<int> results)
{
    std::string ret;
    std::vector<std::string> vecstr;
    std::vector<int> dummy(results);
    if(results.size()) {
		auto max = *std::max_element(results.begin(), results.end());
		if(max) {
			for(int i = 0; i < max + 1; i++) {
				std::ostringstream os;
				for(int j = 0; j < results.size(); j++) {
					if(results[j] > 0) {
						os << std::setw(2) << std::setfill(' ') << std::left << "#";
						results[j]--;
					} else if(results[j] == 0) {
						if(dummy[j] > 0)
							os << std::setw(2) << std::setfill(' ') << std::left << dummy[j];
						else
							os << std::setw(2) << std::setfill(' ') << std::left << " ";
						results[j]--;
					} else {
						os << std::setw(2) << std::setfill(' ') << std::left << " ";
					}
				}
				std::string temp = os.str();
				rstrip(temp);
				temp += "\n";
				vecstr.push_back(temp);
			}
		}
    }
    std::reverse(vecstr.begin(), vecstr.end());
    ret = std::accumulate(vecstr.begin(), vecstr.end(), ret); // default +
    ret += std::string(11, '-') + "\n";
    for(int i = 0; i < 6; i++) {
    	ret += std::to_string(i + 1);
    	ret += i == 5 ? "\n" : " ";
    }
    return ret;
}

int main()
{
	std::cout << histogram(std::vector<int>());
	return 0;
}