#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

template<class T>
class AVLTreeNode//����ġ�AVLTreeNode*����û��<T>�ģ���
{
public:
	T key;
	int height;
	AVLTreeNode* left;
	AVLTreeNode* right;

	AVLTreeNode(T value,AVLTreeNode* l,AVLTreeNode* r):key(value),height(0),left(l),right(r){}
};

template<class T>
class AVLTree//����ġ�AVLTreeNode*������<T>�ģ���
{
public:
	AVLTreeNode<T>* mRoot;

	AVLTree();
	~AVLTree();

	int height(AVLTreeNode<T>* tree);
	AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
	AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);


	//LL:����ת   4����ת�����룬��Ϊ�ô���ת֮ǰ����ת���ֵġ��������䷵��Ҳ��Ϊ�ô���ת֮����ת���ֵġ�����
	AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k);
	//RR:�ҵ���ת
	AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k);
	//LR:��˫��
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k);
	//RL:��˫��
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k);

	AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);//���ڵ���뵽AVL����tree����
	AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);//ɾ��AVL����tree���еĽڵ�z

	void destroy(AVLTreeNode<T>* &tree);//����AVL��
	void print(AVLTreeNode<T>* tree,T key,int direction);//��ӡAVL��
};