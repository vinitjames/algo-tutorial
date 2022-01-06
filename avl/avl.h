#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include "../bst/bst.h"


template <typename T>
class AVL : public BST<Node, T, int>{
public:
	using typename BST<Node, T, int>::node_type;
   AVL(){};
  ~AVL();
  

private:
	void update_height(node_type* node);
	void right_rotate(node_type* node);
	void left_rotate(node_type* node);
	void rebalance(){};
	int height(node_type* node);
  
 
};

template<typename T>
inline
void AVL<T>::update_height(node_type* node){
	node->meta_data() = std::max<int>(height(node->l_child()),
									  height(node->r_child())) + 1;
}

template<typename T>
inline
int AVL<T>::height(node_type* node){
	return node != nullptr ? node->meta_data() : -1 ;
}

template<typename T>
inline
void AVL<T>::right_rotate(node_type* node){
	if(node == nullptr)
		return;
	if(node->parent() == nullptr)
		return;
	if(node != node->parent()->l_child())
		return;
	node_type* temp_node = node->parent();

	node->parent() = temp_node->parent();
	temp_node->parent() = node;
	temp_node->l_child() = node->r_child();
	node->r_child() = temp_node;
	update_height(temp_node);
	update_height(node);
	
}

template<typename T>
inline
void AVL<T>::left_rotate(node_type* node){
	if(node == nullptr)
		return;
	if(node->parent() == nullptr)
		return;
	if(node != node->parent()->r_child())
		return;
	node_type* temp_node = node->parent();

	node->parent() = temp_node->parent();
	temp_node->parent() = node;
	temp_node->r_child() = node->l_child();
	node->l_child() = temp_node;
	update_height(temp_node);
	update_height(node);
	
}







