#include<iostream>
#include<fstream>
#include"WMS.h"
#include<string.h>
using namespace std;

/*��⺯�������ļ��ж�ȡ�� (Ƚ���)
��������Ϣ���ļ��ж�ȡ����������inList�����У�
�������еĻ��ﰴ�����Ӧ�ĳߴ��С������ܣ�
������������ʣ��û�гɹ�������ܵĻ�������
д���ļ����´��ٴ� 
ע���������ǰ�����ȸ�������ÿ��λ������һ���ռ䣬����bigShelf[0][0] = new Shelf; ������ָ��ΪNULL 
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
        printf("���ļ�ʧ��!");
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
    		//С����
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
       
       //�л���
       
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
       
       
      //�����
       
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
        printf("���ļ�ʧ��!");
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


/*��⺯�������ԴӼ������ֶ���⣩ (Ƚ���)
���������Ҫ���ĳһ�����ֱ����ϵͳ�����ֶ�
����ķ�ʽ��ȡ�������Ϣ�������������ܣ���Ҫ����
�����Ƿ�ɹ�����ʾ��������ɹ�����д�������ļ�
�� 
*/ 
void putaway(){
	Goods *head =(Goods*)malloc(sizeof(Goods));
    int num,size,j,k,n;
    long long pNum;
    char name[10];
    Goods *p,*q;
    p=head;
    cout<<"��������������"<<endl;
	 cin>>n;
	 for(j=0;j<n;j++){
	 	cout<<"�������ݵ��ţ�"<<endl;
	 	cin>>num;
	 	cout<<"�������ռ���������"<<endl;
	 	cin>>name;
	 	cout<<"�������ռ��˵绰��"<<endl;
	 	cin>>pNum;
	 	cout<<"���������ߴ磺��0.С����  1.�а��� 2.�������"<<endl;
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
    		//С����
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
       
       //�л���
       
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
       
       
      //�����
       
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
        printf("���ļ�ʧ��!");
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
        printf("���ļ�ʧ��!");
        exit(0); 
    }
	p=head;
	while(p->next!=NULL){
	fprintf(r,"%d %s %lld %d \n",q->ExpressNumber,q->name,q->phoneNumber,q->size);
	p=p->next;
		}
}



//��ѯ�������û�����ͨ�������ݵ��ţ��ջ����������ջ��˵绰�Դ˻�����в��ң����㴺�� 
/*��ʾ�û�������һ������Ϣ�� ��ݵ��ţ��ջ���������
�ջ��˵绰�ȣ���ݵ���ֻ��ӦΨһһ�����������
�绰���ܶ�Ӧ�������轫��ȫ����� 
*/
void cargoTrace(){
cout<<"1��ͨ����ݵ��Ų�ѯ"<<endl;
	cout<<"2��ͨ���ջ���������ѯ"<<endl;
	cout<<"3��ͨ���ջ��˵绰��ѯ"<<endl;
	int n;int number;char name[10];long long phoneNumber;int flag=0;
	cout<<"��������ѡ��Ĳ�ѯ��ʽ�ı�ţ�";
	cin>>n;
	switch(n){
		case 1:cout<<"�������ݵ��ţ�";
				 cin>>number;
				 for(int i=0;i<3;i++){
				 	for(int j=0;j<3;j++){
				 		if(bigShelf[i][j]->isStore!=false){
				 			if(bigShelf[i][j]->good->ExpressNumber==number){
				 				cout<<"����� ��"<<i+1<<"�� ��"<<j+1<<"��"<<endl; 
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
				 				cout<<"�л��� ��"<<i+1<<"�� ��"<<j+1<<"��"<<endl;
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
				 				cout<<"С���� ��"<<i+1<<"�� ��"<<j+1<<"��"<<endl;
				 				flag=1;
				 				return;
							 }
						 }
					 }
				 }
				 if(flag==0){
				 	cout<<"��ȷ�Ͽ�ݵ����Ƿ���ȷ��"<<endl;
				 }
		case 2:cout<<"�������ռ��˵�������";
				cin>>name;
				for(int i=0;i<3;i++){
				 	for(int j=0;j<3;j++){
				 		if(bigShelf[i][j]->isStore!=false){
				 			if(strcmp(bigShelf[i][j]->good->name,name)==0){
				 				cout<<"����� ��"<<i+1<<"�� ��"<<j+1<<"��"<<endl;
				 				flag=1;

							}
						 }
					 }
				 }
				 for(int i=0;i<4;i++){
				 	for(int j=0;j<4;j++){
				 		if(midShelf[i][j]->isStore!=false){
				 			if(strcmp(midShelf[i][j]->good->name,name)==0){
				 				cout<<"�л��� ��"<<i+1<<"�� ��"<<j+1<<"��"<<endl;
				 				flag=1;

							 }
						 }
					 }
				 } 
				 for(int i=0;i<5;i++){
				 	for(int j=0;j<5;j++){
				 		if(smallShell[i][j]->isStore!=false){
				 			if(strcmp(smallShell[i][j]->good->name,name)==0){
				 				cout<<"С���� ��"<<i+1<<"�� ��"<<j+1<<"��"<<endl;
				 				flag=1;

							 }
						 }
					 }
				 }
				 if(flag==0){
				 	cout<<"��ȷ��������ռ��������Ƿ���ȷ��"<<endl; 
				 }
				 	goto p;
		case 3:{cout<<"�������ռ��˵ĵ绰���룺";
				cin>>phoneNumber;
					for(int i=0;i<3;i++){
				 	for(int j=0;j<3;j++){
				 		if(bigShelf[i][j]->isStore!=false){
				 			if(bigShelf[i][j]->good->phoneNumber==phoneNumber){
				 				cout<<"����� ��"<<i+1<<"�� ��"<<j+1<<"��"<<endl;
				 				flag=1;

							}
						 }
					 }
				 }
				 for(int i=0;i<4;i++){
				 	for(int j=0;j<4;j++){
				 		if(midShelf[i][j]->isStore!=false){
				 			if(midShelf[i][j]->good->phoneNumber==phoneNumber){
				 				cout<<"�л��� ��"<<i+1<<"�� ��"<<j+1<<"��"<<endl;
				 				flag=1;

							 }
						 }
					 }
				 } 
				 for(int i=0;i<5;i++){
				 	for(int j=0;j<5;j++){
				 		if(smallShell[i][j]->isStore!=false){
				 			if(smallShell[i][j]->good->phoneNumber==phoneNumber){
				 				cout<<"С���� ��"<<i+1<<"�� ��"<<j+1<<"��"<<endl;
				 				flag=1;

							 }
						 }
					 }
				 }
				 if(flag==0){
				 	cout<<"��ȷ��������ռ��˵ĵ绰�����Ƿ���ȷ��"<<endl;
				 }
	}
	goto p; 
	} 
	p:
		return ;
}


//��ѯ����,����ר�ã�ֻ��ͨ����ݵ��Ų��ң����������λ�õ�ָ���Ա�
//����ʱ�����ÿմ��� 
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

//ͨ������ĵ��ŶԻ�����г��⴦�� (���������¼д������¼�ļ�)����˼�꣩ 
void delieveryCargo(outList *out){
	cout<<"-----------------------------------------"<<endl;
	cout<<"-----------------------------------------"<<endl;
	int number;
	cout<<"������Ҫ����Ŀ�ݵ��ţ�";
	cin>>number;
	Goods *sh = OcargoTrace(number);
	if(sh == NULL){
		cout<<"û���ҵ��õ��ţ�"<<endl;
		cout<<"-----------------------------------------"<<endl;
		cout<<"-----------------------------------------"<<endl;
		return;
	}
	sh->next = out->iList;
	out->iList = sh;
	cout<<"�ÿ�ݵ��ռ�������Ϊ��"<<sh->name<<endl;
	cout<<"�ÿ�ݵ��ռ��˵绰Ϊ��"<<sh->phoneNumber<<endl;
	cout<<"�û���ĳߴ�Ϊ��";
	if(sh->size == 0) cout<<"С����"<<endl;
	else if(sh->size == 1) cout<<"�л���"<<endl;
	else cout<<"�����"<<endl;
//	cout<<"�û�������λ��Ϊ��";
//	if(sh->size == 0) cout<<"С����"<<sh->location[0]<<"��"<<sh->location[1]<<"��"<<endl;
//	else if(sh->size == 1) cout<<"�л���"<<sh->location[0]<<"��"<<sh->location[1]<<"��"<<endl;
//	else cout<<"�����"<<sh->location[0]<<"��"<<sh->location[1]<<"��"<<endl;
	cout<<"�����ɹ���"<<endl;
//	free(sh);
	return;
}


void show(){
	cout<<"С�������"<<endl;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(smallShell[i][j]->isStore == false){
				cout<<"��	";
			}else{
				cout<<"��	";
			} 
		}
		cout<<endl;
	}cout<<endl;
	cout<<"�еȻ������"<<endl;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(midShelf[i][j]->isStore == false){
				cout<<"��	";
			}else{
				cout<<"��	";
			} 
		}
		cout<<endl;
	}cout<<endl;
	cout<<"��������"<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(bigShelf[i][j]->isStore == false){
				cout<<"��	";
			}else{
				cout<<"��	";
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
	cout<<"�����ļ��ɹ���";
}
