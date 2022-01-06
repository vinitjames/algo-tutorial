#ifndef BST_H
#define BST_H


#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include "../node/node.h"


template <template <typename, typename> class TNode, typename TData, typename TMeta>
class BST {

		
public:
	using node_type = TNode<TData, TMeta>;
	
	BST(){};
	
	~BST(){
		if (_root != nullptr) {
			_bfTraversal([](node_type * _node) {
				if (_node != nullptr)
					delete _node;
			});
		}
	}
	
	void insert(const TData &value){
		node_type *new_node = new node_type();
		new_node->value(value);
		node_type **currRoot = &_root;
		while (*currRoot != nullptr) {
			new_node->parent(*currRoot);
			if (new_node->value() < (*currRoot)->value())
				currRoot = (*currRoot)->l_child_ptr();
			else
				currRoot = (*currRoot)->r_child_ptr();
		}
		*currRoot = new_node;
	}
	
	node_type *max(){
		if (_root == nullptr)
			return nullptr;
		return _max(_root);
	}
	
	node_type *min(){
		if (_root == nullptr)
			return nullptr;
		return _min(_root);
	}
	
	void removeNode(const TData &value){
		node_type *node = search(value);
		if (node == nullptr) {
			std::cout << "node not found " << std::endl;
			return;
		}
		std::cout << "found node with value " << node->value() << std::endl;
		if ((node->l_child() == nullptr) && (node->r_child() == nullptr))
			_delLeafNode(node);
		else if ((node->l_child() == nullptr) || (node->r_child() == nullptr))
			_delOneChildNode(node);
		else
			_delTwoChildNode(node);
	}
	
	node_type *search(const TData &value){
		node_type *currNode = _root;
		while (currNode != nullptr) {
			if (value == currNode->value())
				return currNode;
			if (value < currNode->value())
				currNode = currNode->l_child();
			else
				currNode = currNode->r_child();
		}
		return nullptr;
	}
	
	void forEach(std::function<void(node_type *)> for_each){
		_bfTraversal(for_each);
	}	
	
	const node_type* root() const {return _root;}

private:
	
	node_type *_max(node_type *root){
		node_type *currRoot = root;
		while (currRoot->r_child() != nullptr)
			currRoot = currRoot->r_child();
		return currRoot; 
	}
	
	node_type *_min(node_type *root){
		node_type *currRoot = root;
		while (currRoot->l_child() != nullptr)
			currRoot = currRoot->l_child();
		return currRoot;
	}
	
	void _bfTraversal(std::function<void(node_type *)> for_each){
		
		if (_root == nullptr)
			return;
		std::queue<node_type *> nodes;
		nodes.push(_root);
		while (!nodes.empty()) {
			node_type *currNode = nodes.front();
			nodes.pop();
			if (currNode->l_child() != nullptr)
				nodes.push(currNode->l_child());
			if (currNode->r_child() != nullptr)
				nodes.push(currNode->r_child());
			for_each(currNode);
		}
	}
	
	void _delLeafNode(node_type *node){
		if (node->value() < node->parent()->value())
			node->parent()->l_child(nullptr);
		else
			node->parent()->r_child(nullptr);
		delete node;
	}
	
	void _delOneChildNode(node_type *node){
	 node_type* childNode =
		 node->r_child() != nullptr ? node->r_child() : node->l_child();
	 childNode->parent(node->parent());
	 if (node->parent()->value() < node->value())
		 node->parent()->r_child(childNode);
	 else
		 node->parent()->l_child(childNode);
	 delete node;
	}
	
	void _delTwoChildNode(node_type *node){
		node_type *inorderSucc = _min(node->r_child());
		if (inorderSucc->parent() == node)
			inorderSucc->parent()->r_child(inorderSucc->r_child());
		else
			inorderSucc->parent()->l_child(inorderSucc->r_child());
		/*inorderSucc->parent(node->parent());
		  inorderSucc->l_child(node->l_child());
		  inorderSucc->r_child(node->r_child());
		  if (node->parent() != nullptr) {
		  if (node->parent()->l_child() == node)
		  node->parent()->l_child(inorderSucc);
		  else
		  node->parent()->r_child(inorderSucc);
		  }

		  if (node->l_child() != nullptr)
		  node->l_child()->parent(inorderSucc);
		  if (node->r_child() != nullptr)
		  node->r_child()->parent(inorderSucc);*/
		node->value(std::move(inorderSucc->value()));
		delete inorderSucc;
	}

	node_type *_root = nullptr;
};

#endif /* BST_H */

