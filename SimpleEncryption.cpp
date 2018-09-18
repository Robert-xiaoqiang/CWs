#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>
#include <exception>

class Kata {
public:
    std::string encrypt(std::string text);  
    std::string decrypt(std::string encryptedText);
private:
	const static int a = 0;
	const static std::string code;
};

const std::string Kata::code = 
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ" 
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789"
	".,:;-?! '()$%&\""; // space know a little => bitch


std::string Kata::encrypt(std::string text)
{
	std::string ret = text;
	// std::transform(text.begin(), text.end(), 
	// 	[=](char ch){  })
	for(std::string::size_type i = 0; i < ret.size(); i += 1) {
		if(i % 2 && isupper(ret[i])) {
			text[i] = ret[i] = tolower(ret[i]);
		} else if(i % 2 && islower(ret[i])) {
			text[i] = ret[i] = toupper(ret[i]);
		} else if(code.find(ret[i]) == std::string::npos) {
			throw std::exception();
		}
		// find throw?
	}

	for(std::string::size_type i = 1; i < ret.size(); i++) {
		int difference = int(code.find(text[i - 1])) - int(code.find(text[i]));
		if(difference < 0) difference += 77;
		//std::cout << "ret[i] = " << ret[i] << ", code[d] = " << code[difference] << std::endl;
		ret[i] = code[difference];
	}

	ret[0] = code[76 - code.find(ret[0])];

	return ret;
}

std::string Kata::decrypt(std::string encryptedText)
{
	std::string ret = encryptedText;
	if(ret.size() && code.find(ret[0]) == std::string::npos) throw std::exception();
	ret[0] = code[76 - code.find(ret[0])];
	// std::accumulate(ret.begin(), ret.end(),
	// 	[](char before, char cur)->char{  })
	for(std::string::size_type i = 1; i < ret.size(); i++) {
		if(code.find(ret[i]) == std::string::npos) throw std::exception();
		int difference = int(code.find(ret[i - 1])) - int(code.find(ret[i]));
		if(difference < 0) difference += 77;
		ret[i] = code[difference];
	}

	for(std::string::size_type i = 1; i < ret.size(); i += 2) {
		if(isupper(ret[i])) {
			ret[i] = tolower(ret[i]);
		} else if(islower(ret[i])) {
			ret[i] = toupper(ret[i]);
		}
	}
	return ret;
}

int main()
{
	Kata k;
	std::cout << k.decrypt(k.encrypt("Business")) << std::endl; 
	return 0;
}