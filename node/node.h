#ifndef NODE_H
#define NODE_H

#include <memory>

template <class TData, typename TMeta = int>
struct Node {

private:
  TData _value;
  Node *_parent = nullptr;
  Node *_l_child = nullptr;
  Node *_r_child = nullptr;
  TMeta _meta_data; 

public:
	Node() = default;
	
	Node(const TData& value)
		:_value{value}{}
	
	Node(TData&& value)
		:_value{std::move(value)}{}
	
  void value(const TData& value);
  void value(TData&& value);
  TData&value();
  const TData&value() const;
  void meta_data(const TMeta &meta_data);
  void meta_data(TMeta &&meta_data);
  TMeta& meta_data();
  const TMeta &meta_data() const;
  
  Node *parent();
  void parent(Node *parent);
  Node *l_child();
  const Node *l_child() const;
  Node **l_child_ptr();
  void l_child(Node *l_ch);
  Node *r_child();
  const	Node *r_child() const;
  Node **r_child_ptr();
  void r_child(Node *r_ch);
};

template <class TData, typename TMeta>
inline
void Node<TData, TMeta>::value(const TData& value) {
  _value = value;
}

template <class TData, typename TMeta>
inline
void Node<TData, TMeta>::value(TData&& value) {
  _value = std::move(value);
}

template <class TData, typename TMeta>
inline
TData&Node<TData, TMeta>::value() { return _value; }

template <class TData, typename TMeta>
inline
const TData&Node<TData, TMeta>::value() const { return _value; }

template <class TData, typename TMeta>
inline
void Node<TData, TMeta>::meta_data(const TMeta &meta_data) {
  _meta_data = meta_data;
}

template <class TData, typename TMeta>
inline
void Node<TData, TMeta>::meta_data(TMeta &&meta_data) {
  _meta_data = std::move(meta_data);
}

template <class TData, typename TMeta>
inline
TMeta &Node<TData, TMeta>::meta_data() { return _meta_data; }

template <class TData, typename TMeta>
inline
const TMeta &Node<TData, TMeta>::meta_data() const { return _meta_data; }


template <class TData, typename TMeta>
inline
Node<TData, TMeta> *Node<TData, TMeta>::parent() { return _parent; }

template <class TData, typename TMeta>
inline
void Node<TData, TMeta>::parent(Node *parent) {_parent = parent;}

template <class TData, typename TMeta>
inline
Node<TData, TMeta> *Node<TData, TMeta>::l_child() { return _l_child; }

template <class TData, typename TMeta>
inline
const Node<TData, TMeta> *Node<TData, TMeta>::l_child() const { return _l_child; }


template <class TData, typename TMeta>
inline
Node<TData, TMeta> **Node<TData, TMeta>::l_child_ptr() { return &_l_child; }

template <class TData, typename TMeta>
inline
void Node<TData, TMeta>::l_child(Node *l_ch) { _l_child = l_ch; }

template <class TData, typename TMeta>
inline Node<TData, TMeta> *Node<TData, TMeta>::r_child() { return _r_child; }

template <class TData, typename TMeta>
inline
const Node<TData, TMeta> *Node<TData, TMeta>::r_child() const { return _r_child; }

template <class TData, typename TMeta>
inline
Node<TData, TMeta> **Node<TData, TMeta>::r_child_ptr() { return &_r_child; }

template <class TData, typename TMeta>
inline
void Node<TData, TMeta>::r_child(Node *r_ch) { _r_child = r_ch; }

#endif /* NODE_H */
