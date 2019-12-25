#include<iostream>
#include<fstream>
#include"WMS.h"
#include<string.h>
using namespace std;

/*入库函数（从文件中读取） (冉宇浩)
将货物信息从文件中读取出来，存入inList链表中，
将链表中的货物按照其对应的尺寸大小存入货架，
若货架已满则将剩余没有成功存入货架的货物重新
写回文件中下次再存 
注：存入货架前必须先给货架上每个位置申请一个空间，例：bigShelf[0][0] = new Shelf; 否则其指向为NULL 
*/	
Goods *FilePutaway(){
	Goods *head =(Goods*)malloc(sizeof(Goods));
    int num,size,j,k;
    long long pNum;
    char name[10];
    Goods *p,*q;
    p=head;
    FILE * r= fopen("info.txt","r");
    if(r==NULL) 
    {
        printf("打开文件失败!");
        return NULL; 
    }
     
    while(fscanf(r,"%d %s %lld %d ",&num,name,&pNum,&size)!=EOF)
    {
       q= (Goods*)malloc(sizeof(Goods));
       q->ExpressNumber=num;
       strcpy(q->name,name);
       q->phoneNumber=pNum;
       q->size=size;
    	//printf("%d %s %lld %d \n",q->ExpressNumber,q->name,q->phoneNumber,q->size);
       p->next=q;
       p=q;
       p->next=NULL;
	   }


		for(int i=0;i<5;i++){
			for(int m=0;m<5;m++){
				smallShell[i][m] = new Shelf;
			}
		}
		for(int i=0;i<4;i++){
			for(int m=0;m<4;m++){
				midShelf[i][m] = new Shelf;
			}
		}
		for(int i=0;i<3;i++){
			for(int m=0;m<3;m++){
				bigShelf[i][m] = new Shelf;
			}
		}

    	p=head;
    	part:
    	int flag=1;
    	while(p->next!=NULL){
    		//小货物
        if(p->next->size==0){
       		for(j=0;j<5;j++){
	       		for(k=0;k<5;k++){
		       		if(smallShell[j][k]->isStore==false){
		       		smallShell[j][k]->good = new Goods;
					smallShell[j][k]->good->ExpressNumber = p->next->ExpressNumber;
					strcpy(smallShell[j][k]->good->name,p->next->name);
					smallShell[j][k]->good->phoneNumber = p->next->phoneNumber;
					smallShell[j][k]->good->size = p->next->size;
			
			       	p->next=p->next->next;   	
			       	smallShell[j][k]->isStore=true;
			       	flag = 0;
			       	goto part;
				   }
					 	
       			}      
       		}
       }
       
       //中货物
       
       else if(p->next->size==1){
       		for(j=0;j<4;j++){
	       		for(k=0;k<4;k++){
		       		if(midShelf[j][k]->isStore==false){
		       		midShelf[j][k]->good = new Goods;
					midShelf[j][k]->good->ExpressNumber = p->next->ExpressNumber;
					strcpy(midShelf[j][k]->good->name,p->next->name);
					midShelf[j][k]->good->phoneNumber = p->next->phoneNumber;
					midShelf[j][k]->good->size = p->next->size;
			
			       	p->next=p->next->next;   	
			       	midShelf[j][k]->isStore=true;
			       	flag = 0;
			       	goto part;
				   }
       			}      
       		}
       }
       
       
      //大货物
       
      else if(p->next->size==2){
       		for(j=0;j<3;j++){
	       		for(k=0;k<3;k++){
		       		if(bigShelf[j][k]->isStore==false){
		       		bigShelf[j][k]->good = new Goods;
					bigShelf[j][k]->good->ExpressNumber = p->next->ExpressNumber;
					strcpy(bigShelf[j][k]->good->name,p->next->name);
					bigShelf[j][k]->good->phoneNumber = p->next->phoneNumber;
					bigShelf[j][k]->good->size = p->next->size;
			
			       	p->next=p->next->next;   	
			       	bigShelf[j][k]->isStore=true;
			       	flag = 0;
			       	goto part;
				   }

					}  	
       			}      
       		}
       	if(flag){
		   FILE * r= fopen("info1.txt","a");
    if(r==NULL) 
    {
        printf("打开文件失败!");
        exit(0); 
    }
	p=head;
	while(p->next!=NULL){
	fprintf(r,"%d %s %lld %d \n",q->ExpressNumber,q->name,q->phoneNumber,q->size);
	p=p->next;
		}
		} 	
       }
       return head;
   }


/*入库函数（用以从键盘上手动入库） (冉宇浩)
特殊情况需要入库某一个货物，直接再系统中用手动
输入的方式获取货物的信息，并将其存入货架，需要给出
存入是否成功的提示，如果不成功将其写入待入库文件
中 
*/ 
void putaway(){
	Goods *head =(Goods*)malloc(sizeof(Goods));
    int num,size,j,k,n;
    long long pNum;
    char name[10];
    Goods *p,*q;
    p=head;
    cout<<"请输入货物个数："<<endl;
	 cin>>n;
	 for(j=0;j<n;j++){
	 	cout<<"请输入快递单号："<<endl;
	 	cin>>num;
	 	cout<<"请输入收件人姓名："<<endl;
	 	cin>>name;
	 	cout<<"请输入收件人电话："<<endl;
	 	cin>>pNum;
	 	cout<<"请输入货物尺寸：（0.小包裹  1.中包裹 2.大包裹）"<<endl;
	 	cin>>size;
	 	q= (Goods*)malloc(sizeof(Goods));
       q->ExpressNumber=num;
       strcpy(q->name,name);
       q->phoneNumber=pNum;
       q->size=size;
    	printf("%d %s %lld %d \n",q->ExpressNumber,q->name,q->phoneNumber,q->size);
       p->next=q;
       p=q;
       p->next=NULL;
	 }

	p=head;
    	part:
    	int flag=1;
    	while(p->next!=NULL){
    		//小货物
        if(p->next->size==0){
       		for(j=0;j<5;j++){
	       		for(k=0;k<5;k++){
		       		if(smallShell[j][k]->isStore==false){
		       		smallShell[j][k]->good = new Goods;
					smallShell[j][k]->good->ExpressNumber = p->next->ExpressNumber;
					strcpy(smallShell[j][k]->good->name,p->next->name);
					smallShell[j][k]->good->phoneNumber = p->next->phoneNumber;
					smallShell[j][k]->good->size = p->next->size;
			
			       	p->next=p->next->next;   	
			       	smallShell[j][k]->isStore=true;
			       	flag = 0;
			       	goto part;
				   }
					 	
       			}      
       		}
       }
       
       //中货物
       
       else if(p->next->size==1){
       		for(j=0;j<4;j++){
	       		for(k=0;k<4;k++){
		       		if(midShelf[j][k]->isStore==false){
		       		midShelf[j][k]->good = new Goods;
					midShelf[j][k]->good->ExpressNumber = p->next->ExpressNumber;
					strcpy(midShelf[j][k]->good->name,p->next->name);
					midShelf[j][k]->good->phoneNumber = p->next->phoneNumber;
					midShelf[j][k]->good->size = p->next->size;
			
			       	p->next=p->next->next;   	
			       	midShelf[j][k]->isStore=true;
			       	flag = 0;
			       	goto part;
				   }
       			}      
       		}
       }
       
       
      //大货物
       
      else if(p->next->size==2){
       		for(j=0;j<3;j++){
	       		for(k=0;k<3;k++){
		       		if(bigShelf[j][k]->isStore==false){
		       		bigShelf[j][k]->good = new Goods;
					bigShelf[j][k]->good->ExpressNumber = p->next->ExpressNumber;
					strcpy(bigShelf[j][k]->good->name,p->next->name);
					bigShelf[j][k]->good->phoneNumber = p->next->phoneNumber;
					bigShelf[j][k]->good->size = p->next->size;
			
			       	p->next=p->next->next;   	
			       	bigShelf[j][k]->isStore=true;
			       	flag = 0;
			       	goto part;
				   }

					}  	
       			}      
       		}
       	if(flag){
		 FILE * r= fopen("info1.txt","a");
    if(r==NULL) 
    {
        printf("打开文件失败!");
        exit(0); 
    }
	p=head;
	while(p->next!=NULL){
	fprintf(r,"%d %s %lld %d \n",q->ExpressNumber,q->name,q->phoneNumber,q->size);
	p=p->next;
		}
		} 	
       }
   
   	  FILE * r= fopen("info1.txt","a");
    if(r==NULL) 
    {
        printf("打开文件失败!");
        exit(0); 
    }
	p=head;
	while(p->next!=NULL){
	fprintf(r,"%d %s %lld %d \n",q->ExpressNumber,q->name,q->phoneNumber,q->size);
	p=p->next;
		}
}



//查询函数，用户可以通过输入快递单号，收货人姓名，收货人电话对此货物进行查找（吕广春） 
/*提示用户输入查找货物的信息， 快递单号，收货人姓名，
收货人电话等，快递单号只对应唯一一个货物，姓名，
电话可能对应多个货物，需将其全部输出 
*/
void cargoTrace(){
cout<<"1、通过快递单号查询"<<endl;
	cout<<"2、通过收货人姓名查询"<<endl;
	cout<<"3、通过收货人电话查询"<<endl;
	int n;int number;char name[10];long long phoneNumber;int flag=0;
	cout<<"请输入您选择的查询方式的编号：";
	cin>>n;
	switch(n){
		case 1:cout<<"请输入快递单号：";
				 cin>>number;
				 for(int i=0;i<3;i++){
				 	for(int j=0;j<3;j++){
				 		if(bigShelf[i][j]->isStore!=false){
				 			if(bigShelf[i][j]->good->ExpressNumber==number){
				 				cout<<"大货架 第"<<i+1<<"行 第"<<j+1<<"列"<<endl; 
				 				flag=1;
				 				return;
							}
						 }
					 }
				 }
				 for(int i=0;i<4;i++){
				 	for(int j=0;j<4;j++){
				 		if(midShelf[i][j]->isStore!=false){
				 			if(midShelf[i][j]->good->ExpressNumber==number){
				 				cout<<"中货架 第"<<i+1<<"行 第"<<j+1<<"列"<<endl;
				 				flag=1;
				 				return;
							 }
						 }
					 }
				 } 
				 for(int i=0;i<5;i++){
				 	for(int j=0;j<5;j++){
				 		if(smallShell[i][j]->isStore!=false){
				 			if(smallShell[i][j]->good->ExpressNumber==number){
				 				cout<<"小货架 第"<<i+1<<"行 第"<<j+1<<"列"<<endl;
				 				flag=1;
				 				return;
							 }
						 }
					 }
				 }
				 if(flag==0){
				 	cout<<"请确认快递单号是否正确！"<<endl;
				 }
		case 2:cout<<"请输入收件人的姓名：";
				cin>>name;
				for(int i=0;i<3;i++){
				 	for(int j=0;j<3;j++){
				 		if(bigShelf[i][j]->isStore!=false){
				 			if(strcmp(bigShelf[i][j]->good->name,name)==0){
				 				cout<<"大货架 第"<<i+1<<"行 第"<<j+1<<"列"<<endl;
				 				flag=1;

							}
						 }
					 }
				 }
				 for(int i=0;i<4;i++){
				 	for(int j=0;j<4;j++){
				 		if(midShelf[i][j]->isStore!=false){
				 			if(strcmp(midShelf[i][j]->good->name,name)==0){
				 				cout<<"中货架 第"<<i+1<<"行 第"<<j+1<<"列"<<endl;
				 				flag=1;

							 }
						 }
					 }
				 } 
				 for(int i=0;i<5;i++){
				 	for(int j=0;j<5;j++){
				 		if(smallShell[i][j]->isStore!=false){
				 			if(strcmp(smallShell[i][j]->good->name,name)==0){
				 				cout<<"小货架 第"<<i+1<<"行 第"<<j+1<<"列"<<endl;
				 				flag=1;

							 }
						 }
					 }
				 }
				 if(flag==0){
				 	cout<<"请确认输入的收件人姓名是否正确！"<<endl; 
				 }
				 	goto p;
		case 3:{cout<<"请输入收件人的电话号码：";
				cin>>phoneNumber;
					for(int i=0;i<3;i++){
				 	for(int j=0;j<3;j++){
				 		if(bigShelf[i][j]->isStore!=false){
				 			if(bigShelf[i][j]->good->phoneNumber==phoneNumber){
				 				cout<<"大货架 第"<<i+1<<"行 第"<<j+1<<"列"<<endl;
				 				flag=1;

							}
						 }
					 }
				 }
				 for(int i=0;i<4;i++){
				 	for(int j=0;j<4;j++){
				 		if(midShelf[i][j]->isStore!=false){
				 			if(midShelf[i][j]->good->phoneNumber==phoneNumber){
				 				cout<<"中货架 第"<<i+1<<"行 第"<<j+1<<"列"<<endl;
				 				flag=1;

							 }
						 }
					 }
				 } 
				 for(int i=0;i<5;i++){
				 	for(int j=0;j<5;j++){
				 		if(smallShell[i][j]->isStore!=false){
				 			if(smallShell[i][j]->good->phoneNumber==phoneNumber){
				 				cout<<"小货架 第"<<i+1<<"行 第"<<j+1<<"列"<<endl;
				 				flag=1;

							 }
						 }
					 }
				 }
				 if(flag==0){
				 	cout<<"请确认输入的收件人的电话号码是否正确！"<<endl;
				 }
	}
	goto p; 
	} 
	p:
		return ;
}


//查询函数,出库专用，只能通过快递单号查找，并返回这个位置的指针以便
//出库时进行置空处理 
Goods* OcargoTrace(int number){
	int i,j;
	for(i = 0;i < 3;i++){
		for(j = 0;j < 3;j++){
			if(bigShelf[i][j]->isStore == false) continue;
			if(bigShelf[i][j]->good->ExpressNumber == number){
				Goods *sh = bigShelf[i][j]->good;
				bigShelf[i][j]->isStore = false;
				bigShelf[i][j]->good = NULL;
				sh->next = NULL;
				return sh;
			}
		}
	}
	for(i = 0;i < 4;i++){
		for(j = 0;j < 4;j++){
			if(midShelf[i][j]->isStore == false) continue;
			if(midShelf[i][j]->good->ExpressNumber == number){
				Goods *sh = midShelf[i][j]->good;
				midShelf[i][j]->isStore = false;
				midShelf[i][j]->good = NULL;
				sh->next = NULL;
				return sh;
			}
		}
	}
	for(i = 0;i < 5;i++){
		for(j = 0;j < 5;j++){
			if(smallShell[i][j]->isStore == false) continue;
			if(smallShell[i][j]->good->ExpressNumber == number){
				Goods *sh = smallShell[i][j]->good;
				smallShell[i][j]->isStore = false;
				smallShell[i][j]->good = NULL;
				sh->next = NULL;
				return sh;
			}
		}
	}
	return NULL;
}

//通过输入的单号对货物进行出库处理 (并将出库记录写入出库记录文件)（林思宏） 
void delieveryCargo(outList *out){
	cout<<"-----------------------------------------"<<endl;
	cout<<"-----------------------------------------"<<endl;
	int number;
	cout<<"请输入要出库的快递单号：";
	cin>>number;
	Goods *sh = OcargoTrace(number);
	if(sh == NULL){
		cout<<"没有找到该单号！"<<endl;
		cout<<"-----------------------------------------"<<endl;
		cout<<"-----------------------------------------"<<endl;
		return;
	}
	sh->next = out->iList;
	out->iList = sh;
	cout<<"该快递的收件人姓名为："<<sh->name<<endl;
	cout<<"该快递的收件人电话为："<<sh->phoneNumber<<endl;
	cout<<"该货物的尺寸为：";
	if(sh->size == 0) cout<<"小货件"<<endl;
	else if(sh->size == 1) cout<<"中货件"<<endl;
	else cout<<"大货件"<<endl;
//	cout<<"该货物所在位置为：";
//	if(sh->size == 0) cout<<"小货架"<<sh->location[0]<<"行"<<sh->location[1]<<"列"<<endl;
//	else if(sh->size == 1) cout<<"中货架"<<sh->location[0]<<"行"<<sh->location[1]<<"列"<<endl;
//	else cout<<"大货架"<<sh->location[0]<<"行"<<sh->location[1]<<"列"<<endl;
	cout<<"出货成功！"<<endl;
//	free(sh);
	return;
}


void show(){
	cout<<"小货物货架"<<endl;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(smallShell[i][j]->isStore == false){
				cout<<"空	";
			}else{
				cout<<"存	";
			} 
		}
		cout<<endl;
	}cout<<endl;
	cout<<"中等货物货架"<<endl;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(midShelf[i][j]->isStore == false){
				cout<<"空	";
			}else{
				cout<<"存	";
			} 
		}
		cout<<endl;
	}cout<<endl;
	cout<<"大货物货架"<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(bigShelf[i][j]->isStore == false){
				cout<<"空	";
			}else{
				cout<<"存	";
			} 
		}
		cout<<endl;
	}
}


void outFile(outList *out){
	ofstream ou("outfo.txt",ios::app);
	while(out->iList != NULL){
		ou<<out->iList->ExpressNumber<<" "<<out->iList->name<<" "<<out->iList->phoneNumber<<endl;
		out->iList = out->iList->next;
	}
	ou.close();
	cout<<"保存文件成功！";
}
