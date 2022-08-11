#include "rolling_hash.h"

RollingHash::RollingHash(std::uint64_t base, std::uint64_t prime_mod)
	:_base{base}, _prime_mod{prime_mod}{}

bool RollingHash::string_match(const std::string& needle, const std::string& haystack){
	if (needle.size() == 0) return false;
	if (haystack.size() == 0) return false;
	if (needle.size() > haystack.size()) return false;
	
	std::uint64_t nd_hash = 0;
	std::uint64_t hy_hash = 0;
	_cal_power(needle.size());
	

	for (std::size_t i=0; i < needle.size(); ++i) {
		nd_hash = (nd_hash * _base + (int)needle[i]) % _prime_mod;
		hy_hash = (hy_hash * _base + (int)haystack[i]) % _prime_mod;
	}
    if ((hy_hash == nd_hash) && (_check_string(needle, haystack, 0)))
		return true;
	
	for (std::size_t i=needle.size(); i< haystack.size(); ++i){
		hy_hash = (hy_hash * _base + (int)haystack[i]) % _prime_mod;
		std::uint64_t to_remove = _power * haystack[i - needle.size()] % _prime_mod;
		hy_hash = to_remove < hy_hash ? hy_hash - to_remove : hy_hash - to_remove + _prime_mod;
		if ((hy_hash == nd_hash) && (_check_string(needle, haystack, i-needle.size()+1)))
			return true;
	}
	return false;
}

bool RollingHash::_check_string(const std::string& needle,
								const std::string& haystack,
								std::size_t start_pos) const {

	for (std::size_t i=0; i < needle.size(); ++i) {
 		if (needle[i]!= haystack[start_pos+i])
			return false;
	}
	return true;	
}

void RollingHash::_cal_power(std::size_t len){
	for (std::size_t i = 0; i < len; ++i) {
		_power = (_power * _base)%_prime_mod;
	}	
}
