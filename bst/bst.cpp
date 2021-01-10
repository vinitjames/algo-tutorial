#include <memory>
#include <iostream>

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
	void insert(const T& value);
	Node<T>* max();
	Node<T>* min();
	void removeNode(T value);

private:
	Node<T>* _root = nullptr;
	
};

template <class T>
inline
void BST<T>::insert(const T& value){
	Node<T>* node = new Node<T>();
	node->value(value);
	Node<T>** currRoot = &_root;
	while(*currRoot != nullptr){
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

int main(int argc, char *argv[])
{
    BST<float> testbst;
	testbst.insert(5.1);
	testbst.insert(5.23);
	testbst.insert(6.1);
	testbst.insert(6.2);
	
	
	std::cout<<testbst.max()->value()<<'\n';
	std::cout<<testbst.min()->value()<<'\n';
    return 0;
}






