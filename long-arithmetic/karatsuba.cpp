#include <cstdint>
#include<string>
#include<algorithm>
#include <iostream>

std::string add(std::string& a, std::string& b){
	
	return std::string();
}
std::string k_mul(std::string& a, std::string& b){
	if ((a.size() == 0)||(b.size() == 0))
		return {};
	if (a.size()< b.size())
		std::swap(a,b);
	if((a.size() + b.size()) < SIZE_MAX){
		return std::to_string(std::stoi(a) * std::stoi(b));
	}
	  
	std::string ah = a.substr(0, a.size()/2);
	std::string al = a.substr(a.size()/2, a.size());
	std::string bh = b.substr(0, a.size()/2);
	std::string bl = b.substr(a.size()/2, b.size());
	std::string ah_bh = k_mul(ah,bh);
	std::string al_bl = k_mul(al,bl);
	std::string result = ah_bh+al_bl;
	std::string dec = sub(sub(add(add(ah, al), add(bh, bl)), ah_bh), al_bl);	
	return  {};
	
}

int main(int argc, char *argv[])
{
	std::cout<<"size max" <<SIZE_MAX;
    return 0;
}


