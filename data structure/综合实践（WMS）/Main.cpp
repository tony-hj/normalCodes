#include<iostream>
#include"WMS.cpp" 
#include"WMS.h" 

using namespace std;

int main(){


	FilePutaway();
	int n;
	outList *out = new outList;
	out->iList = NULL;
	
	
	while(1){
		cout<<"********************************************"<<endl;
		cout<<"		仓库管理系统"<<endl; 
		cout<<"		1.入库货物"<<endl;
		cout<<"		2.查询货物"<<endl;
		cout<<"		3.出库货物"<<endl;	
		cout<<"		4.查看当前货架状态"<<endl;
		cout<<"		5.退出程序"<<endl;
		cout<<"********************************************"<<endl;
		
		cin>>n;
		switch(n){
			case 1:{
				putaway();
				break;
			}
			case 2:{
				cargoTrace();
				break;
			}
			case 3:{
				delieveryCargo(out);
				break;
			}
			case 4:{
				show();
				break;
			}
			case 5: goto t1; 
		}
	//	system("cls"); 	
	}
	

	t1:
		
		outFile(out);
		return 0;
}
