#ifndef HASH_MAP_H
#define HASH_MAP_H


#include <memory>
#include <cstdint>
#include <cmath>
#include "hash_functions.h"
#include <iostream>

template< typename T>
class HashNode {
	
public:
	HashNode() = default;

	HashNode(const uint32_t& key, const T& value)
		: _key{key}, _data_ptr{std::unique_ptr<T>(new T(value))}{}
	
	void key(const uint32_t& key){_key = key;}
	const uint32_t& key() const {return _key;}
	void  data(const T& value){
		_data_ptr = std::unique_ptr<T>(new T(value));
	}

	T* data(){return _data_ptr.get();}
	HashNode* next(){ return _next.get();}
	void next(std::shared_ptr<HashNode<T>> node){
		std::cout<<"this function is reached"<<std::endl;
		if(_next == nullptr){
			_next = node;
			return;
		}
		_next->next(node);
	}
	
private:
	uint32_t _key;
	std::unique_ptr<T> _data_ptr = nullptr;
	std::shared_ptr<HashNode<T>> _next = nullptr;
	
};

template <typename T>
class HashMap{
public:
	bool insert(const std::uint32_t& key, const T& value);
	
private:
	bool double_table();
	uint32_t get_hash(const std::uint32_t& key);
	std::unique_ptr<HashNode<T>*[]> _hash_table = nullptr;
	std::size_t _size = 0;
	uint32_t _capacity = 0;	
};

template <typename T>
bool HashMap<T>::insert(const std::uint32_t& key, const T& value){
	//hash first and then check if key exists and then do table double
	if(_size == _capacity)
		double_table();
	if(_hash_table[get_hash(key)] == nullptr){
		_hash_table[get_hash(key)] = new HashNode<T>(key, value);
		_size++;
		return true;
	}
	if(_hash_table[get_hash(key)]->key() == key){
		HashNode<T>* temp_node = _hash_table[get_hash(key)];
		_hash_table[get_hash(key)] = new HashNode<T>(key, value);
		delete temp_node;
		return true;
	}
	std::shared_ptr<HashNode<T>> next_node(new HashNode<T>(key, value));
	uint32_t hash = get_hash(key);
	_hash_table[hash]->next(next_node);
	_size++;
	return true;
}

template <typename T>
uint32_t HashMap<T>::get_hash(const uint32_t& key){
	std::cout<< custom_hash::knuth_hash(key, log2(_capacity));
	return custom_hash::knuth_hash(key, log2(_capacity));

}

template <typename T>
bool HashMap<T>::double_table(){
	if(_capacity == 0){
		_hash_table = std::unique_ptr<HashNode<T>*[]>(new HashNode<T>*[1]);
		_capacity++;
		return true;
	}

	std::unique_ptr<HashNode<T>*[]> _new_hash_table =
		std::unique_ptr<HashNode<T>*[]>(new HashNode<T>*[2*_capacity]);
	_capacity *= 2;
	for(std::size_t i = 0; i< _capacity/2; i++){
		if(_new_hash_table[get_hash(_hash_table[i]->key())] == nullptr){
		   _new_hash_table[get_hash(_hash_table[i]->key())] = _hash_table[i];
		   continue;
		}
		std::shared_ptr<HashNode<T>> next_node = std::shared_ptr<HashNode<T>>(_hash_table[i]);
		_new_hash_table[get_hash(_hash_table[i]->key())]->next(next_node);
	}
	std::swap(_hash_table, _new_hash_table);
	return true;
}


#endif /* HASH_MAP_H */
