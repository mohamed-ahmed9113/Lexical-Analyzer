#ifndef DISJOINTNODE_H
#define DISJOINTNODE_H
#include<list>
#include<vector>
#include <string>
using namespace std;
template<class a_type> class DisJointNode {
public:
	a_type coreNode; //input by user contains core info
	DisJointNode<a_type> *parent; //linking structure
	std::list<DisJointNode<a_type> *> *childs; //we need this list for iteration and deletion perposes
	int rank;
public:

	string setName;
	DisJointNode();
	DisJointNode(a_type node);
	void setParent(DisJointNode<a_type>*paren);
	virtual ~DisJointNode();
protected:
};
///////////////////////////////////////////////////////////////////////////////////////////
template<class a_type> DisJointNode<a_type>::DisJointNode(){
}
template<class a_type> DisJointNode<a_type>::DisJointNode(a_type node) {
	this->setName="NONAME";
	this->coreNode = node;
	this->parent = NULL;
	this->rank = 0;
	this->childs = new std::list<DisJointNode<a_type> *>();
}
template<class a_type> void DisJointNode<a_type>::setParent(
		DisJointNode<a_type>*paren) {
	this->parent = paren;
}
template<class a_type> DisJointNode<a_type>::~DisJointNode() {
	//delete is called on the node
	//must delete the core node
	//delete (coreNode);
	delete (childs);

}

#endif // DISJOINTNODE_H
