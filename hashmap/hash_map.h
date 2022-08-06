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
	HashNode* next(){ return _next;}
	void next(HashNode<T>* node){
		if(_next == nullptr){
			_next = node;
			return;
		}
		_next->next(node);
	}
	void clear_next(){
		_next = nullptr;
	}
	
private:
	uint32_t _key;
	std::unique_ptr<T> _data_ptr = nullptr;
	HashNode<T>* _next = nullptr;
};

template <typename T>
class HashMap{
public:
	HashMap(){
		_hash_table = std::unique_ptr<HashNode<T>*[]>(new HashNode<T>*[1]);
		_capacity++;
	}
		
	bool insert(const std::uint32_t& key, const T& value);
	bool remove(const std::uint32_t& key);
	T& operator[](const std::uint32_t& key);
	
private:
	bool double_table();
	bool halve_table();
	uint32_t get_hash(const std::uint32_t& key);
	std::unique_ptr<HashNode<T>*[]> _hash_table = nullptr;
	std::size_t _size = 0;
	uint32_t _capacity = 0;	
};

template <typename T>
bool HashMap<T>::insert(const std::uint32_t& key, const T& value){
	std::cout<<"inserting key"<<key<<std::endl; 
	uint32_t key_hash = get_hash(key);
	HashNode<T>* new_node = new HashNode<T>(key,value); 
	if(_hash_table[key_hash] == nullptr){
		_hash_table[key_hash] = new_node;
		
	}
	else{
		HashNode<T>* hash_node = _hash_table[key_hash];
		HashNode<T>* parent_node = nullptr;
		while(hash_node != nullptr){
			if(hash_node->key() == key){
				std::cout<<"key already exists overwriting key:"<<key<<std::endl;
				new_node->next(hash_node->next());
				if(parent_node == nullptr)
					_hash_table[key_hash] = new_node;
				else{
					parent_node->clear_next();
					parent_node->next(new_node);
				}
				delete hash_node;
				return true;
			}
			parent_node = hash_node;
			hash_node = hash_node->next();
		}
		parent_node->next(new_node);
	}
	++_size;	
	if(_size == _capacity)
		double_table();
	return true;
}

template<typename T>
bool HashMap<T>::remove(const std::uint32_t& key){
	uint32_t key_hash = get_hash(key);
	if(_hash_table[key_hash] == nullptr){
		return false;
	}
	HashNode<T>* hash_node = _hash_table[key_hash];
	HashNode<T>* parent_node = nullptr;
	while(hash_node != nullptr){
		if (hash_node->key() == key)			
			break;
		parent_node = hash_node;
		hash_node = hash_node->next();
	}
	if(hash_node == nullptr){
		return false;
	}
	if(parent_node == nullptr){
		_hash_table[key_hash] = hash_node->next();
	}
    else{
		parent_node->clear_next();
		parent_node->next(hash_node->next());
	}
	delete hash_node;
	--_size;
	if(_size == _capacity/4){
		halve_table();
	}
	return true;
	
}

template<typename T>
T& HashMap<T>::operator[](const std::uint32_t& key){
	uint32_t key_hash = get_hash(key);
	if(_hash_table[key_hash] == nullptr){
		throw std::invalid_argument("key does not exist");
	}
	
	HashNode<T>* iter_node = _hash_table[key_hash];
	HashNode<T>* node = nullptr;  
	while(iter_node != nullptr){
		if (iter_node->key() == key)			
			node = iter_node;
		iter_node = iter_node->next();
	}
	if(node == nullptr){
		throw std::invalid_argument("key does not exist here");
	}
	return *node->data();	
}

template <typename T>
uint32_t HashMap<T>::get_hash(const uint32_t& key){
	std::cout<< "hash of"<<key<<" "<<custom_hash::knuth_hash(key, log2(_capacity))<<std::endl;
	return custom_hash::knuth_hash(key, log2(_capacity));

}

template <typename T>
bool HashMap<T>::double_table(){
	std::cout<<"table is being doubled size:"<<_size<<" capacity"<<_capacity<<std::endl;
	std::unique_ptr<HashNode<T>*[]> _new_hash_table(new HashNode<T>*[2*_capacity]);
	_capacity *= 2;
	for(std::size_t i = 0; i< _capacity/2; i++){
		HashNode<T>* hash_node = _hash_table[i];
		while (hash_node != nullptr) {
			HashNode<T>* new_node = hash_node;
			hash_node = hash_node->next();
			new_node->clear_next();
			uint32_t key_hash = get_hash(new_node->key());
			if(_new_hash_table[key_hash] == nullptr){
				_new_hash_table[key_hash] = new_node;
			}
			else{
				_new_hash_table[key_hash]->next(new_node);
			}
			
		}
	}
	std::swap(_hash_table, _new_hash_table);
	return true;
}

template <typename T>
bool HashMap<T>::halve_table(){
	std::cout<<"table is being halved in  size:"<<_size<<" capacity"<<_capacity<<std::endl;
	std::unique_ptr<HashNode<T>*[]> _new_hash_table(new HashNode<T>*[_capacity/2]);
	_capacity /= 2;
	for(std::size_t i = 0; i< _capacity*2; i++){
		HashNode<T>* hash_node = _hash_table[i];
		while (hash_node != nullptr) {
			HashNode<T>* new_node = hash_node;
			hash_node = hash_node->next();
			new_node->clear_next();
			uint32_t key_hash = get_hash(new_node->key());
			if(_new_hash_table[key_hash] == nullptr){
				_new_hash_table[key_hash] = new_node;
			}
			else{
				_new_hash_table[key_hash]->next(new_node);
			}
		}
	}
	std::swap(_hash_table, _new_hash_table);
	return true;
}


#endif /* HASH_MAP_H */
