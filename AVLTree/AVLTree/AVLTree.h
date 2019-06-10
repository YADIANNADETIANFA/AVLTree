#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

template<class T>
class AVLTreeNode
{
public:
	T key;
	int height;
	AVLTreeNode* left;
	AVLTreeNode* right;

	AVLTreeNode(T value,AVLTreeNode* l,AVLTreeNode* r):key(value),height(0),left(l),right(r){}
};

template<class T>
class AVLTree
{
public:
	AVLTreeNode<T>* mRoot;

	AVLTree();
	~AVLTree();

	int height(AVLTreeNode<T>* tree);
	AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
	AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);


	//LL:左单旋转   4个旋转均返回旋转后的根节点值
	AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);
	//RR:右单旋转
	AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);
	//LR:左双旋
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);
	//RL:右双旋
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);

	AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);//将节点插入到AVL树（tree）中
	AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);//删除AVL树（tree）中的节点z

	void destroy(AVLTreeNode<T>* &tree);//销毁AVL树
	void print(AVLTreeNode<T>* tree,T key,int direction);//打印AVL树
};