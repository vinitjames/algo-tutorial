#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H


#include <cstdint>

namespace custom_hash{

	inline uint32_t divison_hash(const uint32_t& key, const uint32_t& divisor){
		return key%divisor;
	}

	inline uint64_t divison_hash(const uint64_t& key, const uint64_t& divisor){
		return key%divisor;
	}

	inline uint32_t knuth_hash(const uint32_t& key, const uint32_t& size_exp){
		uint64_t knuth_prod = (uint64_t)(key * 2654435769);
		return (knuth_prod & 0xFFFFFFFF) >> (32-size_exp);
	}
}
	

#endif /* HASH_FUNCTIONS_H */
