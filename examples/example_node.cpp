#include "../node/node.h"
#include <iostream>
#include <string>



int main(int argc, char *argv[])
{
    Node<float> node1;
	node1.value(5.5);
	node1.meta_data(233);
	std::cout<< "node with float data and int meta data "
			 << node1.value() << " " << node1.meta_data() <<std::endl;
	
	Node<float, float> node2;
	node2.value(0.55);
	node2.meta_data(155.4);
	std::cout<< "node with float data and float meta data "
			 << node2.value() << " " << node2.meta_data() <<std::endl;

	Node<float, std::string> node3;
	node3.value(0.55);
	node3.meta_data("this is a node");
	std::cout<< "node with float data and string meta data "
			 << node3.value() << " " << node3.meta_data() <<std::endl;

	Node<float, int*> node4;
	node4.value(0.55);
	int int_meta{5};
	node4.meta_data(&int_meta);
	std::cout<< "node with float data and string meta data "
			 << node4.value() << " " << *node4.meta_data() <<std::endl;
    return 0;

	
	
}

