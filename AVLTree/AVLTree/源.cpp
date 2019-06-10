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

//LL   4个旋转均返回旋转后的根节点值
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
 将结点插入到AVL树中，并返回根节点

 参数说明：
     tree AVL树的根结点
     key 插入的结点的键值
 返回值：
     根节点
*/
template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key)
{
	if (tree == nullptr)
	{
		tree = new AVLTreeNode<T>(key, nullptr, nullptr);//这里注意一下，看人家怎么新建的
	}
	else if (key < tree->key)
	{
		tree->left = insert(tree->left, key);//在这里，顺便完成了新旧两树的连接工作
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
		cout << "添加失败：不允许添加相同节点！" << endl;
	tree->height = max(height(tree->left), height(tree->right)) + 1;

	return tree;
}

/*
 删除结点(z)，返回根节点

 参数说明：
     tree AVL树的根结点
     z 待删除的结点
 返回值：
     根节点
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
	else//要删除的节点不是左右支，而是tree本身
	{
		if ((tree->left != nullptr) && (tree->right != nullptr))//tree左右都不为空
		{
			if (height(tree->left) > height(tree->right))
			{
				//如果tree左子树比右子树高；
				//则（01）找出tree的左子树中的最大节点
				//（02）将该最大节点的值赋给tree
				//（03）删除该最大节点
				//这类似于用“tree的左子树中最大节点”做tree的“替身”
				//采用这种方法好处是：删除“tree的左子树中最大节点”之后，AVL树仍然是平衡的
				AVLTreeNode<T>* max = maximum(tree->left);
				tree->key = max->key;
				tree->left = remove(tree->left, max);
			}
			else
			{
				//如果tree左子树不比右子树高（相等或右更高）
				//则（01）找出tree的右子树中的最小节点
				//（02）将该最小节点的值赋给tree
				//（03）删除该最小节点
				//这类似于用“tree的右子树中最小节点”做tree的“替身”
				//采用这种方法好处是：删除“tree的右子树中最小节点”之后，AVL树仍然是平衡的
				AVLTreeNode<T>* min = minimum(tree->right);
				tree->key = min->key;
				tree->right = remove(tree->right, min);
			}
		}
		else//tree左右树中，有一为空
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
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction)//没啥大用，不用记
{
	//direction 0表示根节点  -1表示左孩子  1表示右孩子
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


//测试实验
int main()
{
	int arr[]= { 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9 };
	int len = sizeof(arr) / sizeof(int);
	AVLTree<int>* tree = new AVLTree<int>();
	
	cout << "==依次添加：";
	for (int i = 0; i < len; ++i)
	{
		cout << arr[i] << " ";
		tree->insert(tree->mRoot,arr[i]);
	}

	int i = 14;//功略上是删除值为8的点，我们是删除arr[8];
	AVLTreeNode<int>* z = new AVLTreeNode<int>(arr[14], nullptr, nullptr);
	cout << "\n==删除根节点：" << i;
	tree->remove(tree->mRoot,z);
	cout << "\n==高度：" << tree->height(tree->mRoot);
	cout << "\n==树的详细信息：" << endl;
	tree->print(tree->mRoot, tree->mRoot->key,0);

	tree->destroy(tree->mRoot);

	return 0;
}