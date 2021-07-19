#include <iostream>
#include <algorithm>

#include "patr.hpp"

using namespace NPatr;

std::string GetBin(int num){
	std::string res = "";
	for(int i = 0; i < 5; ++i){
		res += '0' + num % 2;
		num /= 2;
	}
	std::reverse(res.begin(), res.end());
	return res;
}

int main(){
	for(char i = 'a'; i <= 'z'; ++i){
		std::cout << i << " - ";
		int cur = (int)i - 96;
		if(cur < 10){
			std::cout << ' ';
		}
		std::cout << cur << ' ' << GetBin((int)i - 96) << '\n';
	}
}