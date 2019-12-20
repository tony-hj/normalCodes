#include <iostream>
using namespace std;

typedef char DataType;

//二叉树数据结构 
struct node
{
	DataType info ; //存放结点数据 
	struct node *lchild , *rchild ; //指向左右孩子的指针 
};

typedef struct node *BiTree ;

/*创建二叉树
  函数名：createBiTree
  参数：无
  返回值：二叉树根结点指针
  */
BiTree createBiTree(void)
{
	char ch ;
	BiTree  root ;
	cin>>ch ;
	if(ch == '#') root = NULL;
	else{
        root = new struct node ;
        root->info = ch ;
        root->lchild = createBiTree() ;
        root->rchild = createBiTree();
	}
	return root ;
}


void visit(BiTree T)
{
	cout<<T->info ;
}

//计算二叉树的叶子节点个数 
int countLeaf(BiTree T)
{
    //请在此处填写代码， 计算二叉树中树叶的个数
    /********** Begin **********/

	static int num=0;
	if(T == NULL) return -1;
	
	if(T->lchild ==  NULL && T->rchild == NULL)
	num++; 
	
	countLeaf(T->lchild);
	countLeaf(T->rchild);
	return num;



    /********** End **********/
}
//中序遍历二叉树 
void inOrder(BiTree root)
{
	if(root == NULL) return ;
	inOrder(root->lchild);//先根遍历左子树 
	visit(root);//遍历根 
	inOrder(root->rchild);//遍历右子树 
}

//交换二叉树的左右子树 
void changeLR(BiTree root)
{
	if(root == NULL) return;
	BiTree Temp;
	Temp = root->lchild;
	root->lchild = root->rchild;
	root->rchild = Temp;
	
	if(root->lchild == NULL)
		changeLR(root->rchild);
	if(root->rchild == NULL)
		changeLR(root->lchild);
}

//计算具有两个孩子的节点个数 
int countFullNode(BiTree T)
{
	static int num=0;
	if(T == NULL) return -1;
	
	if(T->lchild != NULL && T->rchild != NULL)
	num++; 
	
	countFullNode(T->lchild);
	countFullNode(T->rchild);
	return num;
}

int main(void)
{
	BiTree root = createBiTree();
	cout<<countLeaf(root);
}

