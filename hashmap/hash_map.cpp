#include "hash_map.h"
#include <iostream>

int main(int argc, char *argv[])
{

	HashNode<int> node = HashNode<int>();
	node.key(25);
	node.data(235);
	std::cout<<"key:"<<node.key()<<" data"<<*node.data()<<std::endl;
	HashNode<int> node1 = HashNode<int>(235, 26678);
	std::cout<<"key:"<<node1.key()<<" data"<<*node1.data()<<std::endl;

	HashMap<int> hash_map;
	hash_map.insert(234, 234234);
	hash_map.insert(2345, 23423455);
	hash_map.insert(2, 23423);
	hash_map.insert(20, 234232);
	hash_map.insert(20, 155);
	hash_map.insert(21, 23422);
	hash_map.insert(2283, 23422);
	std::cout<<"value at key 20"<<hash_map[20]<<std::endl;
	hash_map.remove(20);
	std::cout<<"value at key 20"<<hash_map[20]<<std::endl;
    return 0;
}

