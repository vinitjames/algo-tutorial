#include "rolling_hash.h"

RollingHash::RollingHash(std::uint64_t base, std::uint64_t prime_mod)
	:_base{base}, _prime_mod{prime_mod}{}

bool RollingHash::string_match(const std::string& neddle, const std::string& haystack){
	if (neddle.size() == 0) return false;
	if (haystack.size() == 0) return false;
	if (neddle.size() > haystack.size()) return false;
	
	std::uint64_t nd_hash = 0;
	std::uint64_t hy_hash = 0;
	_cal_power(neddle.size());

	for (std::size_t i=0; i < neddle.size(); ++i) {
		nd_hash = (nd_hash * _base + (int)neddle[i]) % _prime_mod; 		
	}

	for (std::size_t i=0; i< haystack.size(); ++i){
		hy_hash = (hy_hash * _base + (int)haystack[i]) % _prime_mod;

		if(i < neddle.size() - 1) continue;

		hy_hash -= _power * haystack[i - neddle.size()] % _prime_mod;
		if ((hy_hash == nd_hash) && (_check_string(neddle, haystack, i-neddle.size())))
				return true;		
	}
	return false;
}

bool RollingHash::_check_string(const std::string& neddle,
								const std::string& haystack,
								std::size_t start_pos) const {

	for (std::size_t i=0; i < neddle.size(); ++i) {
		if (neddle[i]!= haystack[start_pos+i])
			return false;
	}
	return true;	
}

void RollingHash::_cal_power(std::size_t len){
	for (std::size_t i = 0; i < len; ++i) {
		_power = (_power * _base)%_prime_mod;
	}	
}
