#include <memory>
#include <iostream>
#include <queue>
#include <functional>

template <class T>
struct Node{
	
private:
	T _value;
	Node* _parent = nullptr;
	Node* _l_child = nullptr;
	Node* _r_child = nullptr;
public:
	
	void value(const T& value);
	void value(const T&& value);
	T& value();
	const T& value()const;
	Node* parent();
	void parent(Node* parent);
	Node* l_child();
	Node** l_child_ptr();
	void l_child(Node* l_ch);
	Node* r_child();
	Node** r_child_ptr();
	void r_child(Node* r_ch);
	
};

template <class T>
inline
void Node<T>::value(const T& value){
	_value = value;
}

template <class T>
inline
void Node<T>::value(const T&& value){
	_value = std::move(value);
}

template <class T>
inline
T& Node<T>::value(){
	return _value;
}

template <class T>
inline
const T& Node<T>::value() const {
	return _value;
}

template <class T>
inline
Node<T>* Node<T>::parent(){
	return _parent;
	
}

template <class T>
inline
void Node<T>::parent(Node* parent){
	_parent = parent;
	
}

template <class T>
inline
Node<T>* Node<T>::l_child(){
	return _l_child;
	
}

template <class T>
inline
Node<T>** Node<T>::l_child_ptr(){
	return &_l_child;
	
}

template <class T>
inline
void Node<T>::l_child(Node* l_ch){
	_l_child = l_ch;
	
}

template <class T>
inline
Node<T>* Node<T>::r_child(){
	return _r_child;
	
}

template <class T>
inline
Node<T>** Node<T>::r_child_ptr(){
	return &_r_child;
	
}

template <class T>
inline
void Node<T>::r_child(Node* r_ch){
	_r_child = r_ch;
}

template <class T>
class BST{
public:
	BST(){};
	~BST();
	void insert(const T& value);
	Node<T>* max();
	Node<T>* min();
	void removeNode(const T& value);
	Node<T>* search(const T& value);
	
private:
	void _bfTraversal(std::function<void(Node<T>*)>);
	void _delLeafNode(Node<T>* node);
	void _delOneChildNode(Node<T>* node);
	void _delTwoChildNode(Node<T>* node);
	Node<T>* _root = nullptr;
	
};

template <class T>
inline
BST<T>::~BST() {
	if(_root != nullptr){
		_bfTraversal([](Node<T>* node){
			if(node != nullptr)
				delete node;
		});
	}
}

template <class T>
inline
void BST<T>::_bfTraversal(std::function<void(Node<T>*)> for_each) {
	if(_root == nullptr)
		return;
	std::queue<Node<T>*> nodes;
	nodes.push(_root);
	while(!nodes.empty()){
		Node<T>* currNode = nodes.front();
		nodes.pop();
		if(currNode->l_child() != nullptr)
			nodes.push(currNode->l_child());
		if(currNode->r_child() != nullptr)
			nodes.push(currNode->r_child());
		for_each(currNode);
	}
}


template <class T>
inline
void BST<T>::insert(const T& value){
	Node<T>* node = new Node<T>();
	node->value(value);
	Node<T>** currRoot = &_root;
	while(*currRoot != nullptr){
		node->parent(*currRoot);
		if(node->value() < (*currRoot)->value())
			currRoot = (*currRoot)->l_child_ptr();
		else 
			currRoot = (*currRoot)->r_child_ptr();
       }
	*currRoot = node;					
}

template <class T>
inline
Node<T>* BST<T>::max(){
	if(_root == nullptr)
		return nullptr;
	Node<T>* currRoot = _root;
	while(currRoot->r_child() != nullptr)
		currRoot = currRoot->r_child();	
   	return currRoot;				
}

template <class T>
inline
Node<T>* BST<T>::min(){
	if(_root == nullptr)
		return nullptr;
	Node<T>* currRoot = _root;
	while(currRoot->l_child() != nullptr)
		currRoot = currRoot->l_child();	
   	return currRoot;	
			
}

template <class T>
inline
void BST<T>::removeNode(const T& value){
	Node<T>* node = search(value);
	if(node == nullptr)
		return;
	if ((node->l_child() == nullptr) && (node->r_child() == nullptr))
		_delLeafNode(node);
	else if ((node->l_child() == nullptr) || (node->r_child() == nullptr))
		_delSingleChildNode(node);
	else
		_delTwoChildNode(node);
}

template <class T>
inline
void BST<T>::_delLeafNode(Node<T>* node){
	if(node->value() < node->parent()->value())
		node->parent()->l_child(nullptr);
	else
		node->parent()->r_child(nullptr);
	delete node;
}

template <class T>
inline
void BST<T>::_delOneChildNode(Node<T>* node){
	Node<T>* childNode = node->r_child() != nullptr ? node->r_child() : node->l_child();
	childNode->parent(node->parent());
	if(node->parent()->value() < node->value())
		node->parent()->r_child(childNode);
	else
		node->parent()->l_child(childNode);
	delete node;
}

template <class T>
inline
void BST<T>::_delTwoChildNode(Node<T>* node){
	Node<T>* childNode = node->r_child() != nullptr ? node->r_child() : node->l_child();
	childNode->parent(node->parent());
	if(node->parent()->value() < node->value())
		node->parent()->r_child(childNode);
	else
		node->parent()->l_child(childNode);
	delete node;
}

template <class T>
inline
Node<T>* BST<T>::search(const T& value){
	Node<T>* currNode = _root;
	while(currNode != nullptr){
		if(value < currNode->value())
			currNode = currNode->l_child();			
		else if(value > currNode->value())
			currNode = currNode->l_child();
		else
			return currNode;		
	}
	return nullptr;	
}








