#include <vector>
#include <iostream>

template<class TYPE>
int getLengthOfMissingArray(std::vector<std::vector<TYPE>> arrayOfArrays)
{
    int ret = 0;
    int maxLength = 0;
    int minLength = -1;
    int totalLength = 0;
    for(const auto& i : arrayOfArrays) {
    	if(i.size() == 0) return 0;
    	if(i.size() > maxLength) maxLength = i.size();
    	if(minLength == -1 || i.size() < minLength) minLength = i.size();
    	totalLength += i.size();
    }
    
    if(arrayOfArrays.size() > 0) {
    	ret = (minLength + maxLength) * (arrayOfArrays.size() + 1) / 2 - totalLength;
    }

    return ret;
}

int main()
{
	std::vector<std::vector<int>> v = { {1}, {1, 2, 1}, {2, 3}, {1, 1, 1, 1, 1 }};
	std::cout << getLengthOfMissingArray(v) << std::endl;
	return 0;
}