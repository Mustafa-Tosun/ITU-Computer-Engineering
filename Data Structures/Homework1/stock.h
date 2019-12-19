/* @Author
Student Name: Mustafa Tosun
Student ID: 150170055
Date: 10.10.2019 */

#include <iostream>
using namespace std;

struct node{
	int size;
	int quant;
	node *next;
};
struct stock{
	node *head;
	void create();
	void add_stock(int);
	void sell(int);
	void current_stock();
	void clear();
	void sort();
	node* createnode(int); // create new node to add stock
	int search(int); // search for spesific size in stock, returns list number
};

node* stock::createnode(int size){
	node*nn = new node;
	nn->size = size;
	nn->quant = 1;
	nn->next = NULL;
	return nn;
}
void stock::create(){
	head = NULL;
}
void stock::clear(){
	node *iter;
	while (head){
		iter = head;
		head = head->next;
		delete iter;
	}
}
void stock::current_stock(){
	node* iter = head;
	while (iter != NULL){
		cout << iter->size << ':' << iter->quant << endl;
		iter = iter->next;
	}
}
void stock::sell(int size){
	int i = search(size);
	if (i == -1){ // If there is no pair of shoe of that size
		cout << "NO_STOCK" << endl;
	}
	else{
		node* iter = head;
		node* temp = head;
		int j;
		for (j = 0; j < i; j++){
			temp = iter;
			iter = iter->next;
		}
		if (iter->quant == 1){ // If there is only 1 pair of shoe of that size
			if (iter->next){ // Remove node from the middle
				temp = iter->next;
				iter->size = temp->size;
				iter->quant = temp->quant;
				iter->next = temp->next;
				delete temp;
				sort();
			}
			else{ // Remove last node
				if (head != iter){ // If last node is not first node
					temp->next = NULL;
					delete iter;
				}
				else{ // If last node is also first node
					temp = head;
					head = head->next;
					delete temp;
				}
			}
		}
		else{ // If there are more than 1 pair of shoes of that size
			iter->quant--;
		}
	}
}
void stock::add_stock(int size){
	int i = search(size);
	if (i == -1){ //  If there is no pair of shoe of that size
		node* nn = createnode((size));
		if (head == NULL){ // If there is no node in stock
			head = nn;
		}
		else{ // If there is at least one node in stock but not that size
			node* iter = head;
			while (iter->next){
				iter = iter->next;
			}
			iter->next = nn;
			sort();
		}
	}
	else{ // If there is at least 1 pair of shoe of that size
		node* iter = head;
		for (int j = 0; j < i; j++){
			iter = iter->next;
		}
		iter->quant++;
	}
}
int stock::search(int size){ 
	node* iter = head;
	int i=0;
	while (iter!=NULL){
		if (iter->size == size) return i;
		iter = iter->next;
		i++;
	}
	return -1;
}
void stock::sort(){ // Sort in increasing order of size (in every selling and adding)
	node* iter;
	node* iter2;
	for (iter = head; iter->next != NULL; iter=iter->next){
		for (iter2 = iter->next; iter2 != NULL; iter2=iter2->next){
			if (iter->size > iter2->size){
				int size = iter2->size;
				int quant = iter2->quant;
				iter2->size = iter->size;
				iter2->quant = iter->quant;
				iter->size = size;
				iter->quant = quant;
			}
		}
	}
}