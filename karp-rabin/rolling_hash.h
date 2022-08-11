#ifndef ROLLING_HASH_H
#define ROLLING_HASH_H

#include <string>
#include <cstdint>

class RollingHash{
public:
	RollingHash() = default;
	RollingHash(std::uint64_t base, std::uint64_t prime);
	bool string_match(const std::string& needle, const std::string& haystack);

private:
	bool _check_string(const std::string& neddle,
					   const std::string& haystack,
					   std::size_t start_pos) const;
	void _cal_power(std::size_t len);
	std::uint64_t _base = 257;
	std::uint64_t _prime_mod = 1000000007;
	std::uint64_t _power = 1;
	
};

#endif /* ROLLING_HASH_H */
