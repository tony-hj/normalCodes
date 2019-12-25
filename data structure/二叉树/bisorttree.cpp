#include <iostream>
using namespace std;

//二叉排序树，从一棵空树开始创建 
typedef int DataType;
struct node
{
   DataType info ;
   struct node *lchild ,*rchild ;	
};

typedef struct node *sortTree;

//创建一个结点，值为x 
sortTree createTree(DataType x)
{
	sortTree temp = new struct node;
	temp->info = x ;
	temp->lchild = NULL;
	temp->rchild = NULL;
	return temp;
}

//二叉排序树的创建是一个不断插入结点的过程 
sortTree insert(DataType x ,sortTree T)
{
  //如果T为空，则创建结点 
  if(T == NULL)  T = createTree(x);
  //如果插入值小于T的值，则调用递归函数，插入左子树 
  else   if (x < T->info)  T->lchild =insert (x,T->lchild);
  //如果插入值大于T的值，则调用递归函数，插入右子树 
  else   if (x > T->info)  T->rchild = insert(x,T->rchild);
  return T;
} 

//中序遍历二叉排序树，可以得到一个从小到大排列的顺序 
void inOrder(sortTree T)
{
	if(T==NULL) return ;
	inOrder(T->lchild);
	cout<<T->info<<"  " ;
	inOrder(T->rchild);
}

void preOrder(sortTree T)
{
	if(T==NULL) return ;
	
	cout<<T->info<<"  " ;
	preOrder(T->lchild);
	preOrder(T->rchild);
}

//查询
int find(sortTree T,DataType x){
	
	if(T == NULL) return 0;
	if(T->info == x) return 1;
	
	else if(x < T->info) find(T->lchild,x);
	else find(T->rchild,x);
} 

DataType findMin(sortTree T) {
	if(T->lchild == NULL) return T->info;
	findMin(T->lchild);
}

//测试主程序 
int main()
{
	int a[] = {12,23,1,45,6,78,9};//插入二叉排序树的数值序列 
	sortTree T = NULL;//初始化根为空 
	for(int i = 0; i < 7;i++)
		T = insert(a[i],T); //循环插入数值，得到二叉排序树 
	inOrder(T); //验证二叉排序树是否正确 
	cout<<endl;
	preOrder(T);
	cout<<endl;
//	DataType min = findMin(T);
//	cout<<min;
	int x;
	cout<<"输入要查询的数：";
	cin>>x;
	if(find(T,x))
		cout<<"有这个节点";
	else
		cout<<"没有找到这个值";
}

