#include <string> // std::string
#include <stack>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>

std::string brainfuck_to_c(std::string source_code)
{
  std::string result;
  //std::stack<int> myStack;
  const int MAX_SIZE = 10000;
  int myStack[MAX_SIZE] = { 0 };
  int top = 0;
  std::string to;
  std::copy_if(source_code.begin(), source_code.end(), std::back_inserter(to),
  							[](char i){ return i == '+' || i == '-' || i == '<' || i == '>' ||
  											   i == ',' || i == '.' || i == '[' || i == ']';});
  std::string::size_type begin = 0;
  std::istringstream is(to);
  char work;
  int indent = 0; // 2 shifts
  bool tag = false;
  while((work = is.get()) && is) {
  	int X = 0; // ++ --
  	int Y = 0; // << >>
  	int C = 0; // [C]
  	if(work == '+') {
  		X = 1;
  		while((work = is.get()) == '+' || work == '-') X += work == '+' ? 1 : -1;
  		is.unget();
		if(!result.empty()) {
			std::string::size_type lastInstIndex = result.rfind('\n', result.size() - 2);
			if(lastInstIndex != std::string::npos || 
			   lastInstIndex == std::string::npos && result.find('\n') == result.size() - 1) {
				std::string lastInst = result.substr(lastInstIndex + 1);
				// MAX_SIZE + 1 == 0
				if(lastInst.find("*p += ") != std::string::npos) {
					std::string dummy;
					int xi;
					std::istringstream istr(lastInst);
					istr >> dummy >> dummy >> xi;
					X += xi; // (+)
					result.erase(lastInstIndex + 1);
					if(top > 0) myStack[top - 1]--;
				} else if(lastInst.find("*p -= ") != std::string::npos) {
					std::string dummy;
					int xi;
					std::istringstream istr(lastInst);
					istr >> dummy >> dummy >> xi;
					X -= xi; // (-)
					result.erase(lastInstIndex + 1);
					if(top > 0) myStack[top - 1]--;
				}
			}
		}
  		if(X > 0) {
  			result += std::string(indent, ' ') + "*p += " + std::to_string(X) + ";\n";
  			if(top > 0) myStack[top - 1]++;
  		} else if(X < 0) {
  			result += std::string(indent, ' ') + "*p -= " + std::to_string(-X) + ";\n";
  			if(top > 0) myStack[top - 1]++;
  		}
  	} else if(work == '-') {
  		X = -1;
  		while((work = is.get()) == '-' || work == '+') X += work == '-' ? -1 : 1;
  		is.unget();
		if(!result.empty()) {
			std::string::size_type lastInstIndex = result.rfind('\n', result.size() - 2);
			if(lastInstIndex != std::string::npos ||
			   lastInstIndex == std::string::npos && result.find('\n') == result.size() - 1) {
				std::string lastInst = result.substr(lastInstIndex + 1);
				if(lastInst.find("*p += ") != std::string::npos) {
					std::string dummy;
					int xi;
					std::istringstream istr(lastInst);
					istr >> dummy >> dummy >> xi;
					X += xi; // (+)
					result.erase(lastInstIndex + 1);
					if(top > 0) myStack[top - 1]--;
				} else if(lastInst.find("*p -= ") != std::string::npos) {
					std::string dummy;
					int xi;
					std::istringstream istr(lastInst);
					istr >> dummy >> dummy >> xi;
					X -= xi; // (-)
					result.erase(lastInstIndex + 1);
					if(top > 0) myStack[top - 1]--;
				}
			}
		}
  		if(X < 0) {
  			result += std::string(indent, ' ') + "*p -= " + std::to_string(-X) + ";\n";
  			if(top > 0) myStack[top - 1]++;
  		} else if(X > 0) {
  			result += std::string(indent, ' ') + "*p += " + std::to_string(X) + ";\n";
  			if(top > 0) myStack[top - 1]++;
  		}  		
  	} else if(work == '<') {
  		Y = -1;
  		while((work = is.get()) == '<' || work == '>') Y += work == '<' ? -1 : 1;
  		is.unget();
		if(!result.empty()) {
			std::string::size_type lastInstIndex = result.rfind('\n', result.size() - 2);
			if(lastInstIndex != std::string::npos ||
			   lastInstIndex == std::string::npos && result.find('\n') == result.size() - 1) {
				std::string lastInst = result.substr(lastInstIndex + 1);
				if(lastInst.find("p += ") != std::string::npos && 
				   lastInst.find("*p += ") == std::string::npos) {
					std::string dummy;
					int yi;
					std::istringstream istr(lastInst);
					istr >> dummy >> dummy >> yi;
					Y += yi; // (+)
					result.erase(lastInstIndex + 1);
					if(top > 0) myStack[top - 1]--;
				} else if(lastInst.find("p -= ") != std::string::npos &&
					      lastInst.find("*p -= ") == std::string::npos) {
					std::string dummy;
					int yi;
					std::istringstream istr(lastInst);
					istr >> dummy >> dummy >> yi;
					Y -= yi; // (-)
					result.erase(lastInstIndex + 1);
					if(top > 0) myStack[top - 1]--;
				}
			}
		}
  		if(Y < 0) {
			result += std::string(indent, ' ') + "p -= " + std::to_string(-Y) + ";\n";
			if(top > 0) myStack[top - 1]++;
  		} else if(Y > 0) {
  			result += std::string(indent, ' ') + "p += " + std::to_string(Y) + ";\n";
  			if(top > 0) myStack[top - 1]++;
  		}
  	} else if(work == '>') {
		Y = 1;
  		while((work = is.get()) == '>' || work == '<') Y += work == '>' ? 1 : -1;
  		is.unget();
		if(!result.empty()) {
			std::string::size_type lastInstIndex = result.rfind('\n', result.size() - 2);
			if(lastInstIndex != std::string::npos ||
			   lastInstIndex == std::string::npos && result.find('\n') == result.size() - 1) {
				std::string lastInst = result.substr(lastInstIndex + 1);
				if(lastInst.find("p += ") != std::string::npos &&
				   lastInst.find("*p += ") == std::string::npos) {
					std::string dummy;
					int yi;
					std::istringstream istr(lastInst);
					istr >> dummy >> dummy >> yi;
					Y += yi; // (+)
					result.erase(lastInstIndex + 1);
					if(top > 0) myStack[top - 1]--;
				} else if(lastInst.find("p -= ") != std::string::npos &&
					      lastInst.find("*p -= ") == std::string::npos) {
					std::string dummy;
					int yi;
					std::istringstream istr(lastInst);
					istr >> dummy >> dummy >> yi;
					Y -= yi; // (-)
					result.erase(lastInstIndex + 1);
					if(top > 0) myStack[top - 1]--;
				}
			}
		}
  		if(Y > 0) {
  			result += std::string(indent, ' ') + "p += " + std::to_string(Y) + ";\n";
  			if(top > 0) myStack[top - 1]++;
  		} else if(Y < 0) {
  			result += std::string(indent, ' ') + "p -= " + std::to_string(-Y) + ";\n";
  			if(top > 0) myStack[top - 1]++;
  		}
  	} else if(work == '.') {
  		result += std::string(indent, ' ') + "putchar(*p);\n";
  		if(top > 0) myStack[top - 1]++;
  	} else if(work == ',') {
  		result += std::string(indent, ' ') + "*p = getchar();\n";
  		if(top > 0) myStack[top - 1]++;
  	} else if(work == '[') {
  		if(top > 0) myStack[top - 1]++;
  		myStack[top++] = 0;
  		result += std::string(indent, ' ') + "if (*p) do {\n";
  		indent += 2;
  	} else if(work == ']') {
  		if(top == 0) {
  		 	result = "Error!";
  		 	break;
  		}
  		int count = myStack[--top];
  		indent -= 2;
  		if(count > 0) {
  			result += std::string(indent, ' ') + "} while (*p);\n";	
  		} else {
  			// == 0 ;just [
  			if(top > 0) myStack[top - 1]--;
  			result.erase(result.rfind('\n', result.size() - 2) + 1);
  		}
  	}
  }
  if(top) result = "Error!";
  return result;
}

int main()
{
	std::cout << brainfuck_to_c("[[[[[+<<]]]]]") << std::endl;
	return 0;
}
