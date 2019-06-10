#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

template<class T>
class AVLTreeNode//这里的“AVLTreeNode*”是没有<T>的！！
{
public:
	T key;
	int height;
	AVLTreeNode* left;
	AVLTreeNode* right;

	AVLTreeNode(T value,AVLTreeNode* l,AVLTreeNode* r):key(value),height(0),left(l),right(r){}
};

template<class T>
class AVLTree//这里的“AVLTreeNode*”是有<T>的！！
{
public:
	AVLTreeNode<T>* mRoot;

	AVLTree();
	~AVLTree();

	int height(AVLTreeNode<T>* tree);
	AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
	AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);


	//LL:左单旋转   4个旋转的输入，均为该次旋转之前，旋转部分的“根”；其返回也均为该次旋转之后，旋转部分的“根”
	AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k);
	//RR:右单旋转
	AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k);
	//LR:左双旋
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k);
	//RL:右双旋
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k);

	AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);//将节点插入到AVL树（tree）中
	AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);//删除AVL树（tree）中的节点z

	void destroy(AVLTreeNode<T>* &tree);//销毁AVL树
	void print(AVLTreeNode<T>* tree,T key,int direction);//打印AVL树
};