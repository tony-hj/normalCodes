#include <iostream>
using namespace std;
 
typedef char DataType;
 
//二叉树结点定义 
struct node
{
   DataType data; //存放结点数据 
   struct node *lchild, *rchild ; //左右孩子指针 
};
typedef struct  node  BiTree;
typedef struct  node  *ptree;

//函数可直接使用，功能：输出结点数据
void print(DataType d)
 {
   cout<<d<<" ";
 }

/*
函数名：createBiTree
函数功能：创建二叉树，并返回二叉树的根结点指针 
参数：无 
返回值：二叉树的根结点指针 
*/ 
BiTree *createBiTree() {
//请在此处填写代码，完成创建二叉树并返回二叉树根结点指针的功能    
/*-------begin--------*/          
    char x;
	cin>>x;
	ptree root = new BiTree;
	root->data = x;
	if(x == '#') return root;

	root->lchild = createBiTree();
	root->rchild = createBiTree();
    
	return root;
/*-------end--------*/    
}

/*
函数名：preOrder
函数功能：先根遍历二叉树 
参数：二叉树根结点指针 
返回值：无 
*/ 
void preOrder(BiTree *T) 
{
//请在此处填写代码，完成先根遍历二叉树功能    
/*-------begin--------*/
    if(T->data == '#') return;
	print(T->data);
	preOrder(T->lchild);
	preOrder(T->rchild);
    
/*-------end--------*/  
}
 
/*
函数名： inOrder
函数功能：中根遍历二叉树 
参数：二叉树根结点指针 
返回值：无 
*/  
void inOrder(BiTree *T) 
{
    //请在此处填写代码，完成中根遍历二叉树功能    
/*-------begin--------*/
    if(T->data == '#')return;
	inOrder(T->lchild);
	print(T->data);
	inOrder(T->rchild);
    
/*-------end--------*/  
}

/*
函数名：postOrder
函数功能：后根遍历二叉树 
参数：二叉树根结点指针 
返回值：无 
*/  
 void postOrder(BiTree *T)  
    {  
      //请在此处填写代码，完成后根遍历二叉树功能    
/*-------begin--------*/
    if(T->data == '#')return;
	postOrder(T->lchild);
	postOrder(T->rchild);
	print(T->data);
    
/*-------end--------*/  
    }  
 
//求二叉树的深度 
int countLevel(BiTree *root){
	if(root->data == '#')return -1;
	else{
		int left,right;
		left = 1 + countLevel(root->lchild);
		right = 1 + countLevel(root->rchild);
		return left>right?left:right;
	}
}  

//改变二叉树的左右子树 
void changeLR(BiTree *root){
	if(root->data == '#') return;
	BiTree *Temp;
	Temp = root->lchild;
	root->lchild = root->rchild;
	root->rchild = Temp;
	
	if(root->lchild->data == '#')
		changeLR(root->rchild);
	if(root->rchild->data == '#')
		changeLR(root->lchild);
}

//求二叉树的扩充节点数，对返回值减一可求此二叉树结点数 
int  extendedNodeNum(BiTree *T){
	static int num=0;
    if(T->data == '#') {
    	num++;
    	return -1;
	}
	extendedNodeNum(T->lchild);
	extendedNodeNum(T->rchild);
	return num;
}
//求二叉树的叶子节点个数 
int leafNodeNum(BiTree *T){
	static int num=0;
	if(T->data == '#') return -1;
	
	if(T->lchild->data == '#' && T->rchild->data == '#')
	num++; 
	
	leafNodeNum(T->lchild);
	leafNodeNum(T->rchild);
	return num;
}


int main()
{  
    BiTree    *T;  
     T =  createBiTree(   ); //调用创建二叉树功能，得到二叉树的根结点指针
// 
//	 
//    preOrder(  T );//调用先根遍历二叉树，按先根遍历顺序输出二叉树结点功能 
//    cout<<endl; //换行
//	inOrder(T);//调用中根遍历二叉树，按中根遍历顺序输出二叉树结点功能 
//	cout<<endl; 
//    postOrder(T);//调用后根遍历二叉树，按后根遍历顺序输出二叉树结点功能 
//	cout<<endl;   
//   
//	int deep = countLevel(T);
//	cout<<"二叉树的深度："<<deep<<endl;
//	changeLR(T);
//	preOrder(  T );//调用先根遍历二叉树，按先根遍历顺序输出二叉树结点功能 
//    cout<<endl; //换行
//	inOrder(T);//调用中根遍历二叉树，按中根遍历顺序输出二叉树结点功能 
//	cout<<endl; 
//    postOrder(T);//调用后根遍历二叉树，按后根遍历顺序输出二叉树结点功能    
//   
	int deep = countLevel(T);
	cout<<"二叉树的深度："<<deep<<endl;
//	int extendeNode = extendedNodeNum(T);
//	cout<<"二叉树的扩充节点个数："<<extendeNode<<endl;
	int leafNode = leafNodeNum(T);
	cout<<"二叉树的叶子节点个数："<<leafNode<<endl; 
	
	
   return 1;
}  
