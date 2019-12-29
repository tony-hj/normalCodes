#include <iostream>
using namespace std;

typedef char DataType;

//���������ݽṹ 
struct node
{
	DataType info ; //��Ž������ 
	struct node *lchild , *rchild ; //ָ�����Һ��ӵ�ָ�� 
};

typedef struct node *BiTree ;

/*����������
  ��������createBiTree
  ��������
  ����ֵ�������������ָ��
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

//�����������Ҷ�ӽڵ���� 
int countLeaf(BiTree T)
{
    //���ڴ˴���д���룬 �������������Ҷ�ĸ���
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
//������������� 
void inOrder(BiTree root)
{
	if(root == NULL) return ;
	inOrder(root->lchild);//�ȸ����������� 
	visit(root);//������ 
	inOrder(root->rchild);//���������� 
}

//�������������������� 
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

//��������������ӵĽڵ���� 
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

