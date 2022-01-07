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
	void insert(const T& value) override;
	void removeNode(const T& value) override;
	
  
private:
	void update_height(node_type* node);
	void right_rotate(node_type* node);
	void left_rotate(node_type* node);
	void rebalance(node_type* node);
	int height(node_type* node);
  
 
};

template<typename T>
inline
void AVL<T>::insert(const T& value){
	node_type* node = BST<Node, T, int>::insert(value);
	rebalance(node);
}

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
	if(node->l_child() == nullptr)
		return;
	node_type* temp_node = node->l_child();
	if (node->parent() == nullptr)
		_root = temp_node;
	else{
		if(node->parent()->l_child() == node)
			node->parent()->l_child() = temp_node;
		else
			node->parent()->r_child() = temp_node;
	}
	
	temp_node->parent() = node->parent();
	node->parent() = temp_node;
	node->l_child() = temp_node->r_child();
	if(node->l_child() != nullptr)
		node->l_child()->parent() = node;
	temp_node->r_child() = node;
	update_height(node);
	update_height(temp_node);	
}

template<typename T>
inline
void AVL<T>::left_rotate(node_type* node){
	if(node == nullptr)
		return;
	if(node->r_child() == nullptr)
		return;
	node_type* temp_node = node->r_child();
	if (node->parent() == nullptr)
		_root = temp_node;
	else{
		if(node->parent()->l_child() == node)
			node->parent()->l_child() = temp_node;
		else
			node->parent()->r_child() = temp_node;
	}
	
	temp_node->parent() = node->parent();
	node->parent() = temp_node;
	node->r_child() = temp_node->l_child();
	if(node->r_child() != nullptr)
		node->r_child()->parent() = node;
	temp_node->l_child() = node;
	update_height(node);
	update_height(temp_node);	
}


template<typename T>
inline
void AVL<T>::rebalance(node_type* node){
	while(node != nullptr){
		update_height(node);
		if (height(node->l_child()) > height(node->r_child()) + 1){
			if(height(node->l_child()->l_child()) >= height(node->l_child()->r_child()))
				right_rotate(node);
			else{
				left_rotate(node->l_child());
				right_rotate(node);
			}
		}

		else if (height(node->r_child()) > height(node->l_child()) + 1){
			if(height(node->r_child()->r_child()) >= height(node->r_child()->l_child()))
				left_rotate(node);
			else{
				right_rotate(node->r_child());
				left_rotate(node);
			}
		}			
		
		node = node->parent();
	}		
}



