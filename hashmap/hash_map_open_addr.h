#ifndef HASH_MAP_OPEN_ADDR_H
#define HASH_MAP_OPEN_ADDR_H


#include <cstdint>
#include <memory>

template <typename T>
class HashMapOpenAddr{

public:
	HashMapOpenAddr()
		:_hash_table{std::unique_ptr<Node*[]>(new Node*[_capacity])}{}
	HashMapOpenAddr(std::size_t capacity)
		:_capacity{capacity},_hash_table{std::unique_ptr<Node*[]>(new Node*[_capacity])}{}
	
	bool insert(std::uint32_t key, const T& value);
	T& search(std::uint32_t key){}
	bool remove(std::uint32_t key){}
private:
	struct Node
	{   Node() = delete;
		Node(std::uint32_t key, const T& value)
			:_key{key}, _data{std::unique_ptr<T>(new T(value))}{}
		std::uint32_t _key = 0 ;
		std::unique_ptr<T> _data = nullptr;
		bool _delete = false;
	};

	std::size_t _probe(std::uint32_t);
	std::size_t _get_hash(std::uint32_t key, std::size_t inc);
	void _double_table();
	bool _insert(std::size_t index, Node* node);
	std::unique_ptr<Node*[]> _hash_table = nullptr;
	std::size_t _size = 0;
	std::size_t _capacity = 8;
	double _target_load = 0.5;
};



template<typename T>
bool HashMapOpenAddr<T>::insert(std::uint32_t key, const T& value){
	if ((double)(_size)/(double)(_capacity) > _target_load)
		_double_table();

	std::size_t index = _probe(key);
	Node* node = new Node(key, value);
	return _insert(index, node);
}

template<typename T>
bool HashMapOpenAddr<T>::_insert(std::size_t index, Node* node){
	if (_hash_table[index] != nullptr) {
		Node* temp_node = _hash_table[index];
		_hash_table[index] = nullptr;
		delete temp_node;
		_size--;
	}
	_hash_table[index] = node;
	_size++;
	return true;
}

template<typename T>
std::size_t HashMapOpenAddr<T>::_probe(std::uint32_t key){
	std::size_t i = 0;
	std::size_t index;
	do{
		index = _get_hash(key, i++);
		if ((_hash_table[index]->_key == key)||(_hash_table[index]->_delete==true))
			return index;
		
	}while(_hash_table[index] != nullptr);
	return index;
}

template<typename T>
std::size_t HashMapOpenAddr<T>::_get_hash(std::uint32_t key, std::size_t inc){
	return ((key%_capacity) + (inc * (5-(key%5)))) % _capacity;
}

template<typename T>
void HashMapOpenAddr<T>::_double_table(){
	std::unique_ptr<Node*[]> temp_table{new Node*[_capacity*2]};
	std::swap(_hash_table, temp_table);
	_capacity *= 2;
	_size = 0;
	for (std::size_t i = 0; i < _capacity/2; ++i) {
		if (temp_table[i] == nullptr)
			continue;
		if (temp_table[i]->_delete == true)
			continue;
		std::size_t index = _probe(temp_table[i]->_key);
		_insert(index, temp_table[i]);
		temp_table[i]=nullptr;					
	}
}

#endif /* HASH_MAP_OPEN_ADDR_H */
