#include"AVLTree.h"

template<class T>
AVLTree<T>::AVLTree():mRoot(nullptr){}

template<class T>
AVLTree<T>::~AVLTree()
{
	destroy(mRoot);
}

template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
	if (tree != nullptr)
		return tree->height;
	return 0;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
	if (tree == nullptr)
		return nullptr;
	while (tree->left != nullptr)
		tree = tree->left;
	return tree;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
	if (tree == nullptr)
		return nullptr;
	while (tree->right != nullptr)
		tree = tree->right;
	return tree;
}

//LL   4����ת��������ת��ĸ��ڵ�ֵ
template<class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2)
{
	AVLTreeNode<T>* k1;
	k1 = k2->left; k2->left = k1->right;
	k1->right = k2;

	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;

	return k1;
}

//RR
template<class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
	AVLTreeNode<T>* k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->left), height(k2->right)) + 1;

	return k2;
}

//LR
template<class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
	k3->left = rightRightRotation(k3->left);
	return leftLeftRotation(k3);
}

//RL
template<class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
	k1->right = leftLeftRotation(k1->right);
	return rightRightRotation(k1);
}

/*
 �������뵽AVL���У������ظ��ڵ�

 ����˵����
     tree AVL���ĸ����
     key ����Ľ��ļ�ֵ
 ����ֵ��
     ���ڵ�
*/
template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key)
{
	if (tree == nullptr)
	{
		tree = new AVLTreeNode<T>(key, nullptr, nullptr);//����ע��һ�£����˼���ô�½���
	}
	else if (key < tree->key)
	{
		tree->left = insert(tree->left, key);//�����˳��������¾����������ӹ���
		if (height(tree->left) - height(tree->right) == 2)
		{
			if (key < tree->left->key)
				tree = leftLeftRotation(tree);
			else
				tree = leftRightRotation(tree);
		}
	}
	else if (key > tree->key)
	{
		tree->right = insert(tree->right, key);
		if (height(tree->right) - height(tree->left) == 2)
		{
			if (key > tree->right->key)
				tree = rightRightRotation(tree);
			else
				tree = rightLeftRotation(tree);
		}
	}
	else//key==tree->key
		cout << "���ʧ�ܣ������������ͬ�ڵ㣡" << endl;
	tree->height = max(height(tree->left), height(tree->right)) + 1;

	return tree;
}

/*
 ɾ�����(z)�����ظ��ڵ�

 ����˵����
     tree AVL���ĸ����
     z ��ɾ���Ľ��
 ����ֵ��
     ���ڵ�
*/
template<class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z)
{
	if (tree == nullptr || z == nullptr)
		return nullptr;

	if (z->key < tree->key)
	{
		tree->left = remove(tree->left, z);
		if (height(tree->right) - height(tree->left) == 2)
		{
			AVLTreeNode<T>* r = tree->right;
			if (height(r->left) > height(r->right))
				tree = rightLeftRotation(tree);
			else
				tree = rightRightRotation(tree);
		}
	}
	else if (z->key > tree->key)
	{
		tree->right = remove(tree->right, z);
		if (height(tree->left) - height(tree->right) == 2)
		{
			AVLTreeNode<T>* l = tree->left;
			if (height(l->right) > height(l->left))
				tree = leftRightRotation(tree);
			else
				tree = leftLeftRotation(tree);
		}
	}
	else//Ҫɾ���Ľڵ㲻������֧������tree����
	{
		if ((tree->left != nullptr) && (tree->right != nullptr))//tree���Ҷ���Ϊ��
		{
			if (height(tree->left) > height(tree->right))
			{
				//���tree���������������ߣ�
				//��01���ҳ�tree���������е����ڵ�
				//��02���������ڵ��ֵ����tree
				//��03��ɾ�������ڵ�
				//���������á�tree�������������ڵ㡱��tree�ġ�����
				//�������ַ����ô��ǣ�ɾ����tree�������������ڵ㡱֮��AVL����Ȼ��ƽ���
				AVLTreeNode<T>* max = maximum(tree->left);
				tree->key = max->key;
				tree->left = remove(tree->left, max);
			}
			else
			{
				//���tree�����������������ߣ���Ȼ��Ҹ��ߣ�
				//��01���ҳ�tree���������е���С�ڵ�
				//��02��������С�ڵ��ֵ����tree
				//��03��ɾ������С�ڵ�
				//���������á�tree������������С�ڵ㡱��tree�ġ�����
				//�������ַ����ô��ǣ�ɾ����tree������������С�ڵ㡱֮��AVL����Ȼ��ƽ���
				AVLTreeNode<T>* min = minimum(tree->right);
				tree->key = min->key;
				tree->right = remove(tree->right, min);
			}
		}
		else//tree�������У���һΪ��
		{
			AVLTreeNode<T>* tmp = tree;
			tree = (tree->left != nullptr) ? tree->left : tree->right;
			delete tmp;
		}
	}
	return tree;
}

template<class T>
void AVLTree<T>::destroy(AVLTreeNode<T>* &tree)
{
	if (tree == nullptr)
		return;
	if (tree->left != nullptr)
		destroy(tree->left);
	else
		destroy(tree->right);

	delete tree;
}

template<class T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction)//ûɶ���ã����ü�
{
	//direction 0��ʾ���ڵ�  -1��ʾ����  1��ʾ�Һ���
	if (tree != nullptr)
	{
		if (direction == 0)
			cout << tree->key << "is root" << endl;
		else
			cout << tree->key << " is" << key << "'s" << (direction == 1 ? "right child" : "left child") << endl;
		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}


//����ʵ��
int main()
{
	int arr[]= { 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9 };
	int len = sizeof(arr) / sizeof(int);
	AVLTree<int>* tree = new AVLTree<int>();
	
	cout << "==������ӣ�";
	for (int i = 0; i < len; ++i)
	{
		cout << arr[i] << " ";
		tree->insert(tree->mRoot,arr[i]);
	}

	int i = 14;//��������ɾ��ֵΪ8�ĵ㣬������ɾ��arr[8];
	AVLTreeNode<int>* z = new AVLTreeNode<int>(arr[14], nullptr, nullptr);
	cout << "\n==ɾ�����ڵ㣺" << i;
	tree->remove(tree->mRoot,z);
	cout << "\n==�߶ȣ�" << tree->height(tree->mRoot);
	cout << "\n==������ϸ��Ϣ��" << endl;
	tree->print(tree->mRoot, tree->mRoot->key,0);

	tree->destroy(tree->mRoot);

	return 0;
}