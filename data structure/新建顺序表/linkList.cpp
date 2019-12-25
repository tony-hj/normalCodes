

linkList createNUllList(){
	listList head = new linkList;
	if(head == NULL){
	return NULL;		
	}
	head->info = 0;
	head->link = NULL;
	return head;
}

void insetTail(linkList llist,DataType x ){
	linkList temp = new linkList;
	temp->info = x;
	temp->link = NULL;
	linkList tail = llist->link;
	if(tail == NULL){
		llist->link = temp;
		llist->info++;
	}
	else{
		while(tail->link != NULL)
			tail = tail->link;
		tail->link = temp;
	}
}


 void printLlist(linkList llist) 
 {
 	cout<<"线性表中的数据元素如下\n";
 	llist = llist->link; 
 	while(llist != NULL)
 	cout<<llist->info<<" ";
	  	
 	cout<<endl; //最后输出一个换行 
 } 
