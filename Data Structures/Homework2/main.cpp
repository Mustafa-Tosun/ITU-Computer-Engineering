#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#define message_character 40

struct message_node{
	char* message;
	int mh;
	message_node *next;
};
struct message_queue{
	message_node *head;
	message_node *last;
	void push(char* ,int );
	char* pop();
	void create();
	
	
};
void message_queue::create(){
	head=NULL;
	last=NULL;
}
char* message_queue::pop(){
	if (head==NULL){
		return NULL;
	}
	char* rmessage=new char[40];
	strcpy(rmessage,head->message);
	message_node *temp=head;
	head=head->next;
	delete temp;
	return rmessage;
}

void message_queue::push(char* message,int mh){
	
	if (head==NULL){
		
		head=new message_node;
		head->message=new char[40];
		strcpy(head->message,message);
		head->mh=mh;
		head->next=NULL;
		last=head;
		
	}
	else {
		last->next=new message_node;
		last->next->message=new char[40];
		strcpy(last->next->message,message);
		last->next->mh=mh;
		last=last->next;
		last->next=NULL;
	}
}

//network iþlemleri
struct system_node{ 
	int bs_id;
	int mh_id;
	int belong_bs_id;
	char* message;
	struct system_node *firstChild; 
	struct system_node *nextSibling; 
	struct system_node *mh_nodes;
};

struct network{
	system_node *tree;
	int add_bs(system_node* ,int ,int);
	int add_mh(system_node* ,int , int );
	system_node *find_message_mh(system_node *, int);
	void add_message_to_mh(int ,char*);
	void create_cc();
	system_node* linked_add_bs(system_node*,int);
	system_node* linked_add_mh(system_node*,int);
	
};
void network::create_cc(){
	tree=new system_node;
	tree->bs_id=0;
//	tree->belong_bs_id=0;
	tree->firstChild=NULL;
	tree->nextSibling=NULL;
	tree->message=NULL;
	tree->mh_id=0;
	tree->mh_nodes=NULL;
}
system_node* network::linked_add_bs(system_node* bs,int bs_id){
	if (bs == NULL){
		bs=new system_node;
		bs->bs_id=bs_id;
		bs->mh_id=0;
		bs->firstChild=NULL;
		bs->nextSibling=NULL;
		bs->message=NULL;
		bs->mh_nodes=NULL;
		return bs;
	}
	system_node* iter=bs;
	while (iter->nextSibling != NULL){
		iter=iter->nextSibling;
	}
	system_node *temp=new system_node;
	iter->nextSibling=temp;
	temp->bs_id=bs_id;
	temp->mh_id=0;
	temp->firstChild=NULL;
	temp->nextSibling=NULL;
	temp->message=NULL;
	temp->mh_nodes=NULL;
	return bs;
}
int network::add_bs(system_node* tree,int bs_id,int belong_bs_id){
    if (tree==NULL){
        return -1;
    }
    if (tree->bs_id==belong_bs_id){
        if(tree->firstChild==NULL){
            tree->firstChild=linked_add_bs(tree->firstChild,bs_id);
            return 1;

          }
        
        linked_add_bs(tree->firstChild,bs_id);
//        printf("burada iþlem bitti \n");
        if (tree->firstChild==NULL){
//            printf("tree->firstChild == NULL \n");
        }
//        printf("ifte sýkýntý yok \n");
        return 1;
    }
    if (add_bs(tree->nextSibling,bs_id,belong_bs_id)==1){
        return 1;
    }
    if (add_bs(tree->firstChild,bs_id,belong_bs_id)==1){
        return 1;
    }
    return -1;
    
}
system_node* network::linked_add_mh(system_node* belong_bs,int mh_id){
	if (belong_bs == NULL){
		belong_bs=new system_node;
		belong_bs->bs_id=0;
		belong_bs->mh_id=mh_id;
		belong_bs->firstChild=NULL;
		belong_bs->nextSibling=NULL;
		belong_bs->message=NULL;
		belong_bs->mh_nodes=NULL;
		return belong_bs;
	}
	system_node* iter=belong_bs;
	while (iter->mh_nodes != NULL){
		iter=iter->mh_nodes;
	}
	system_node *temp=new system_node;
	iter->mh_nodes=temp;
	temp->bs_id=0;
	temp->mh_id=mh_id;
	temp->firstChild=NULL;
	temp->nextSibling=NULL;
	temp->message=NULL;
	temp->mh_nodes=NULL;
	return belong_bs;
}
int network::add_mh(system_node* tree,int mh_id,int belong_bs_id){
	if (tree==NULL){
        return -1;
    }
    if (tree->bs_id==belong_bs_id){
        tree->mh_nodes=linked_add_mh(tree->mh_nodes,mh_id);
        return 1;
    }
    if (add_mh(tree->nextSibling,mh_id,belong_bs_id)==1){
        return 1;
    }
    if (add_mh(tree->firstChild,mh_id,belong_bs_id)==1){
        return 1;
    }
    return -1;
}

system_node* network::find_message_mh(system_node* tree,int finded_mh){  //eklenecek mesajýn bs'si bulundu
	if (tree==NULL){
		return NULL;
	}
	if (tree->mh_id==finded_mh){
		return tree;
	}
	if(find_message_mh(tree->mh_nodes,finded_mh)){
		return find_message_mh(tree->mh_nodes,finded_mh);
	}
	if(find_message_mh(tree->firstChild,finded_mh)){
		return find_message_mh(tree->firstChild,finded_mh);
	}
	if (find_message_mh(tree->nextSibling,finded_mh)){
		return find_message_mh(tree->nextSibling,finded_mh);
	}
	return NULL;


}

void network::add_message_to_mh(int mh_id,char* message){
	system_node* found_node=find_message_mh(tree,mh_id);
	if(found_node == NULL){
		printf("Can not be reached the mobile host mh_%d at the moment",mh_id);
		return;
	}
	found_node->message=message;
	
	return;
}
void bastir(system_node *r){
	while(r != NULL){
		printf("%d \n",r->mh_id);
		r=r->mh_nodes;
	}
}



int main(){
	
	message_queue ms_que;
	char *message=new char[40];
	char *mh_id_ch=new char[5];
	char *just_message=new char[40];
	ms_que.create();
	
	FILE* file = NULL;
	file=fopen("Messages.txt", "r"); 
	while(!feof(file)){
		
		fgets(message,40,file);
		char *just_message = strtok(message, ">");
		char *mh_id_ch=strtok(NULL,">");
		int mh_id=atoi(mh_id_ch);
		
		ms_que.push(just_message,mh_id);
		
	}
    fclose(file);
    printf("mesajý kuyruða alma iþlemi bitti \n");
    
    network nt;
    nt.create_cc();
    
	std::ifstream filep;
	filep.open("Network.txt");
	char *type=new char[3];
    int first_number;
    int second_number;
	while(filep>>type){
		filep>>first_number;
		filep>>second_number;
//		printf("********************************************************* \n");
		
//		printf("%d \n",strcmp(type,"BS"));
//		printf("burayý geçi\n");
		
    	
    	if (strcmp(type,"BS")==0){
//    		printf("%s %d %d \n",type,first_number,second_number);
    		system_node* head=nt.tree;
    		nt.add_bs(nt.tree,first_number,second_number);
//   			printf("BS %d %d eklendi \n",first_number,second_number);
			nt.tree=head;
//    		printf("En sonda tree %d\n",nt.tree->bs_id);
    		
		}
//		printf("********************************************************* \n");

		if (strcmp(type,"MH")==0){
			system_node* head=nt.tree;
			nt.add_mh(nt.tree,first_number,second_number);
			nt.tree=head;
			printf("MH %d %d eklendi \n",first_number,second_number);
			printf("En sonda tree %d\n",nt.tree->bs_id);
			
			
		}
	}
	
	printf("network oluþturma iþlemi bitti \n");
	
	
	printf("-------------------------------------------------\n");
	printf("%d  bu elemeanýn mh'leri \n",nt.tree->bs_id); // 0 0 
	bastir(nt.tree);
		printf("-------------------------------------------------\n");

	
	printf("%d  bu elemanýn mh'leri \n",nt.tree->firstChild->bs_id);  //5 0
	bastir(nt.tree->firstChild);
	printf("%d ..............................\n",nt.tree->firstChild->mh_nodes->mh_nodes->mh_id);

	
		printf("-------------------------------------------------\n");

	
	printf("%d  bu elemanýn mh'leri \n",nt.tree->firstChild->firstChild->bs_id);  //2 5
	bastir(nt.tree->firstChild->firstChild);
		printf("-------------------------------------------------\n");

	
	printf("%d  bu elemanýn mh'leri \n",nt.tree->firstChild->firstChild->nextSibling->bs_id);  //7 5
	bastir(nt.tree->firstChild->firstChild->nextSibling);
		printf("-------------------------------------------------\n");



	printf("%d  bu elemanýn mh'leri \n",nt.tree->firstChild->nextSibling->bs_id); // 9 0 
	bastir(nt.tree->firstChild->nextSibling);
	printf("-------------------------------------------------\n");
	
	printf("%d  bu elemanýn mh'leri \n",nt.tree->firstChild->nextSibling->nextSibling->bs_id);
	bastir(nt.tree->firstChild->nextSibling->nextSibling);	
	printf("-------------------------------------------------\n");
	
	printf("%d  bu elemanýn mh'leri \n",nt.tree->firstChild->nextSibling->nextSibling->firstChild->bs_id);
	bastir(nt.tree->firstChild->nextSibling->nextSibling->firstChild);
	
	printf("-------------------------------------------------\n");
	printf("%d  bu elemanýn mh'leri \n",nt.tree->firstChild->nextSibling->nextSibling->firstChild->firstChild->bs_id);
	bastir(nt.tree->firstChild->nextSibling->nextSibling->firstChild->firstChild);
	
	printf("-------------------------------------------------\n");


	printf("%d  bu elemanýn mh'leri \n",nt.tree->firstChild->nextSibling->nextSibling->nextSibling->bs_id);
	bastir(nt.tree->firstChild->nextSibling->nextSibling->nextSibling);
	printf("-------------------------------------------------\n");

	

//	while(ms_que.head){
//		printf("olay yerindeyiz");
//		nt.add_message_to_mh(ms_que.head->mh,ms_que.pop());
//	}
   	return 0;
}



//system_node* network::add_bs(system_node* tree,int bs_id,int belong_bs_id){
////	printf("%d fonksiyonda \n",tree->bs_id);
//	if (tree==NULL){
//		printf("tree NULL \n");
//		tree=new system_node;
//		tree->bs_id=bs_id;
//		tree->belong_bs_id=belong_bs_id;
//		tree->firstChild=NULL;
//		tree->nextSibling=NULL;
//		tree->message=NULL;
//		tree->mh_id=0;
//		tree->mh_nodes=NULL;
//		return tree;
//	}
//	if (tree->bs_id == belong_bs_id || tree->belong_bs_id != belong_bs_id ){
//		
//		printf("tree->bs_id == belongs_bs_id \n");
//		if(tree->firstChild == NULL && tree->bs_id != belong_bs_id){
//			printf("tree->firstChild NULL but bs_id != belong_bs_id  \n");
//		}
//		if (tree->firstChild == NULL) {
//			printf("tree->firstChild NULL \n");
//    	}
//		tree->firstChild=add_bs(tree->firstChild,bs_id,belong_bs_id);
//		printf("tree->bs_id %d \n",tree->bs_id);
//		return tree;
//	}
//	printf("Kardeþleri geziyoruz \n");
//	printf("tree->nextSibling'ten önceki tree->bs_id = %d \n",tree->bs_id);
//	tree->nextSibling=add_bs(tree->nextSibling,bs_id,belong_bs_id);
//	printf("tree->nextSibling'te tree->bs_id = %d \n",tree->bs_id);
//	return tree;
//}


