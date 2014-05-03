#ifndef DISJOINLIST_H
#define DISJOINLIST_H
#include "DisJointNode.h"
#include<list>
#include <iostream>
#include <string>
using namespace std;
/**
 we must include the implementation in the header file
 why? because...what ever iam too lazy to know
 **/
template<class a_type>  //indicate a template type to the compiler
class DisjoinList {
protected:
public:
	string name;
	DisJointNode<a_type> *root;
	void getList(std::list<DisJointNode<a_type>*> *input);
	DisjoinList(DisJointNode<a_type> *root); //make set
	DisjoinList(); //make set
	DisJointNode<a_type>* find(DisJointNode<a_type> *x); //find set
	void unionSets(DisjoinList<a_type> *x); //Union set
	void Link(DisJointNode<a_type> *x, DisJointNode<a_type> *y,
			DisjoinList<a_type> *list);
	virtual ~DisjoinList();
private:
	void getListRecursive(std::list<DisJointNode<a_type>*> *input,
			DisJointNode<a_type> *root);

};

///////////////////////////////////////////////////////////////////////////////////////// cpp
template<class a_type>
DisjoinList<a_type>::DisjoinList()
{

}
template<class a_type>
void DisjoinList<a_type>::getList(std::list<DisJointNode<a_type>*> *input) {
	//in order traversal
	//this->root=find(this->root);
	getListRecursive(input, this->root);
}

template<class a_type>
void DisjoinList<a_type>::getListRecursive(
		std::list<DisJointNode<a_type>*> *input, DisJointNode<a_type> *root) {
	//in order traversal

//	cout<<"Root is  "<<root->coreNode;
//	cout<<""<<endl;
	typename std::list<DisJointNode<a_type> *>::iterator it =
			root->childs->begin();
	input->push_front(root);
	for (int i = 0; it != root->childs->end(); ++it) {
//		cout<<"curr childs is :  "<<(*it)->coreNode;
//			cout<<""<<endl;
		getListRecursive(input, *it);
	}
	return;
}


/**
 * constructor, root node is input
 */
template<class a_type>
DisjoinList<a_type>::DisjoinList(DisJointNode<a_type> *root)
{
	this->root = root;
	this->root->parent = this->root;

}
///**
// * on create, create a dummy node
// * which will serve as a representative for the list
// */
//template<class a_type>
//DisjoinList<a_type>::DisjoinList(a_type *data) {
//	this->root = new DisJointNode<a_type>(data);
//	this->root->parent = this->root;
//
//}
template<class a_type>
void DisjoinList<a_type>::unionSets(DisjoinList<a_type> *x) {
//	cout<<"unioninnggg  ->> "<<this->root->setName;
//	cout<<""<<endl;
//	cout<<"and  ->> "<<x->root->setName;
//		cout<<""<<endl;
	Link(this->root, x->root, x);

}
template<class a_type>
DisJointNode<a_type>* DisjoinList<a_type>::find(DisJointNode<a_type> *x) {
	if (x->parent != x) {
		x->parent = find(x->parent);
	}
	return x->parent;

}
/**
 * links two lists by adjusting their roots
 */
template<class a_type>
void DisjoinList<a_type>::Link(DisJointNode<a_type> *x, DisJointNode<a_type> *y,
		DisjoinList<a_type> *list) {
	if (x->rank > y->rank) {
		y->parent = x;
		x->childs->push_front(y); // adding y to x's childs
		list->root = x;

	} else {
		x->parent = y;
		y->childs->push_front(x); // adding y to x's childs
		this->root = y;
	}
	if (x->rank == y->rank) {

		(y->rank)++;
	}

}
template<class a_type>
DisjoinList<a_type>::~DisjoinList() {
	if (root == NULL)
			return;
		std::list<DisJointNode<a_type> *> *nodes;
		getList(nodes);
		delete (nodes);
}
#endif // DISJOINLIST_H
