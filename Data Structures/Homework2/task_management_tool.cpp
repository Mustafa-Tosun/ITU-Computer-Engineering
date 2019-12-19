/* @Author
Student Name: Mustafa Tosun
Student ID : 150170055
Date: 11.11.2019 */
/*
PLEASE, DO NOT CHANGE void display(bool verbose, bool testing), int getUsableDay() and int getUsableTime() FUNCTIONS.
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS THAT IS MENTIONED ABOVE. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

#include "task_management_tool.h"

using namespace std; 


void WorkPlan::display(bool verbose,bool testing)
{
	string inone="***";
	if (head!=NULL)
	{
		Task *pivot =new Task;
		Task *compeer =new Task;
			
		pivot=head;
		do
		{
			if(testing)
				inone+=" ";
			else
				cout << pivot->day <<". DAY"<< endl;
			compeer=pivot;
			while(compeer!=NULL)
			{
				string PREV= compeer->previous!=NULL?compeer->previous->name:"NULL";
				string NEXT=compeer->next!=NULL?compeer->next->name:"NULL";
				string CONT=compeer->counterpart!=NULL?compeer->counterpart->name:"NULL";
				if (testing)
					inone+=compeer->name;
				else
					if(verbose)
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< PREV<<"\t<- "<< compeer->name <<"("<< compeer->priority <<")->\t"<<NEXT <<"\t |_"<<CONT<<endl;
					else
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< compeer->name <<"("<< compeer->priority <<")"<<endl;				
				compeer=compeer->counterpart;
			}
			pivot=pivot->next;
		}while(pivot!=head);
		if(testing)
		{
			cout<<inone<<endl;
			cout<<"(checking cycled list:";
			if (checkCycledList())
				cout<<" PASS)"<<endl;
			else
				cout<<" FAIL)"<<endl;
		}
	}
	else
		cout<<"There is no task yet!"<<endl;
}

int WorkPlan::getUsableDay()
{
	return usable_day;
}

int WorkPlan::getUsableTime()
{
	return usable_time;
}

void WorkPlan::create()
{
	head = NULL;
}

void WorkPlan::close()
{
	if (head != NULL){ // at least one task in list
		Task *last = head->previous;
		while (head != last){
			Task *iter = head;
			head = head->next;
			while (iter->counterpart != NULL){
				Task *temp = iter;
				iter = iter->counterpart;
				delete temp;
			}
			delete iter;
		}
		if (head == last){
			while (head->counterpart != NULL){
				Task *temp = head;
				head = head->counterpart;
				delete temp;
			}
			head = NULL;
		}
	}
}

Task * WorkPlan::createTask(Task *task){ // creating task with given properties
	Task *newtask = new Task();
	newtask->name = new char[strlen(task->name)];
	strcpy(newtask->name, task->name);
	newtask->day = task->day;
	newtask->time = task->time;
	newtask->priority = task->priority;
	newtask->next = NULL;
	newtask->previous = NULL;
	newtask->counterpart = NULL;
	return newtask;
}

void WorkPlan::add(Task *task)
{
	if (head == NULL){ // no task in list
		head = createTask(task);
		head->previous = head;
		head->next = head;
		return;
	}
	if (getTask(task->day, task->time) != NULL){ // priority
		Task *temp = getTask(task->day, task->time);
		if (task->priority > temp->priority){ // if new task's priority is bigger swap name and priority
			char *name = new char[strlen(temp->name)];
			strcpy(name, temp->name);
			temp->name = new char[strlen(task->name)];
			strcpy(temp->name, task->name);
			task->name = new char[strlen(name)];
			strcpy(task->name, name);
			int priority = temp->priority;
			temp->priority = task->priority;
			task->priority = priority;
			checkAvailableNextTimesFor(task);
		}
		else{
			checkAvailableNextTimesFor(task);
		}
		temp = head;
		int d;
		for (d = 1; d < usable_day; d++){
			temp = temp->next;
		}
		if (temp == head){ // new last day
			task->day = head->previous->day + 1;
			task->time = 8;
			add(task);
			return;
		}
		else{
			task->day = d;
			task->time = usable_time;
			add(task);
			return;
		}
	}

	if (head != NULL){ // at least one task in list
		Task *iter = head;
		if (iter->day != task->day) iter = iter->next;
		while (iter->day != task->day){
			if (iter == head){ // new day
				if (head->day > task->day){ // new first day
					Task *temp = createTask(task);
					temp->next = head;
					temp->previous = head->previous;
					head->previous->next = temp;
					head->previous = temp;
					head = temp;
					return;
				}
				if (head->previous->day < task->day){ // new last day
					Task *temp = createTask(task);
					temp->next = head;
					temp->previous = head->previous;
					head->previous->next = temp;
					head->previous = temp;
					return;
				}
				if (head->day < task->day && head->previous->day > task->day){ // new middle day
					while (1){
						if (iter->day < task->day && iter->next->day > task->day){ // find place
							Task *temp = createTask(task);
							temp->next = iter->next;
							temp->previous = iter;
							iter->next->previous = temp;
							iter->next = temp;
							return;
						}
						iter = iter->next;
					}
				}
			}
			iter = iter->next;
		}
		if (iter->day == task->day){ // counterpart
			while (iter->time < task->time){ // middle or last counterpart
				if (iter->counterpart == NULL){ // last counterpart
					Task *temp = createTask(task);
					iter->counterpart = temp;
					return;
				}
				if (iter->time < task->time && iter->counterpart && iter->counterpart->time > task->time){ // middle counterpart
					Task *temp = createTask(task);
					temp->counterpart = iter->counterpart;
					iter->counterpart = temp;
					return;
				}
				iter = iter->counterpart;
			}
			if (iter->time > task->time){ // first counterpart
				Task *temp = createTask(task);
				temp->next = iter->next;
				temp->previous = iter->previous;
				iter->previous->next = temp;
				iter->next->previous = temp;
				temp->counterpart = iter;
				iter->previous = NULL;
				iter->next = NULL;
				if (iter == head) head = temp;
				return;
			}
		}
	}
	return;
}

Task * WorkPlan::getTask(int day, int time)
{
	if (head == NULL) return NULL; // no task in list
	Task *iter = head;
	if (head->day == day && head->time == time) return head;
	while (head->day == day && iter->time != time && iter->counterpart){
		iter = iter->counterpart;
		if (iter->day == day && iter->time == time) return iter;
	}
	iter = head->next;
	while (iter->day != day){
		if (iter->day == head->day) return NULL; // not found
		iter = iter->next;
	}
	while (iter->time != time){
		iter = iter->counterpart;
		if (iter == NULL) return NULL; // not found
	}
	return iter;
}


void WorkPlan::checkAvailableNextTimesFor(Task *delayed){
	if (getTask(delayed->day, delayed->time) == NULL) {
		usable_day = delayed->day;
		usable_time = delayed->time;
		return;
	}
	Task *iter = head;
	while (iter->day != delayed->day) iter = iter->next;
	Task *first = iter; // first task of day
	while (iter->time != delayed->time) iter = iter->counterpart;
	Task *last = iter; // last task of day
	while (last->counterpart != NULL) last = last->counterpart;
	for (int i = delayed->time; i < last->time; i++){ // try to find availible time in sameday
		if (iter->time != i){
			usable_day = iter->day;
			usable_time = i;
			return;
		}
		iter = iter->counterpart;
	}
	first = first->next;
	iter = first;
	last = first;
	while (last->counterpart != NULL) last = last->counterpart;
	while (first != head){ // try to find availible time in next office days
		for (int i = 8; i < last->time; i++){
			if (iter->time != i){
				usable_day = iter->day;
				usable_time = i;
				return;
			}
			iter = iter->counterpart;
		}
		first = first->next;
		iter = first;
		last = first;
		while (last->counterpart != NULL) last = last->counterpart;
	}
	// not found availible time, make it in new day at 8
	usable_day = (head->previous->day) + 1; 
	usable_time = 8;
	return;
}

void WorkPlan::delayAllTasksOfDay(int day)
{
	Task *iter = head;
	while (day != iter->day){ // find day
		iter = iter->next;
	}
	iter->previous->next = iter->next;
	iter->next->previous = iter->previous;
	if (iter == head) head = iter->next;
	Task *first = iter;
	while (iter != NULL){ // make all appointments next office day at 8
		
		if(first->next == head){ // delay all tasks of last day
			iter->day = (first->day) + 1;
			iter->time = 8;
			iter = iter->counterpart;
		} 
		else{
			iter->day = first->next->day;
			iter->time = 8;
			iter = iter->counterpart;
		}
	}
	iter = first;
	while (iter != NULL){ // find new place for all tasks
		checkAvailableNextTimesFor(iter);
		Task *newone = createTask(iter);
		newone->day = usable_day;
		newone->time = usable_time;
		Task *temp = iter;
		iter = iter->counterpart;
		delete temp;
		add(newone);
	}
	return;
}

void WorkPlan::remove(Task *target)
{
	Task *iter = head;
	while (iter->day != target->day){ // find day
		iter = iter->next;
	}
	while (iter->time != target->time){ // find time
		iter = iter->counterpart;
	}

	if (iter->next == NULL){ // not first task of day
		Task *temp = head;
		while (temp->day != iter->day){
			temp = temp->next;
		}
		while (temp->counterpart->time != iter->time){
			temp = temp->counterpart;
		}
		if (iter->counterpart == NULL){ // last task of day
			temp->counterpart = NULL;
		}
		else{ // middle task of day
			temp->counterpart = iter->counterpart;
		}
		delete iter;
		return;
	}
	else{ // first task of day
		if (iter == head){ // remove head
			if (head->counterpart){ // if head has counterpart
				head->previous->next = head->counterpart;
				head->next->previous = head->counterpart;
				head->counterpart->next = head->next;
				head->counterpart->previous = head->previous;
				head = head->counterpart;
				delete iter;
				return;
			}
			else{ // if head has not counterpart
				head->next->previous = head->previous;
				head->previous->next = head->next;
				head = head->next;
				delete iter;
				return;
			}
		}
		else{ // remove first task different from head
			if (iter->counterpart == NULL){ // if first task has counterpart
				iter->previous->next = iter->next;
				iter->next->previous = iter->previous;
				delete iter;
				return;
			}
			else{ // if first task has not counterpart
				iter->previous->next = iter->counterpart;
				iter->next->previous = iter->counterpart;
				iter->counterpart->next = iter->next;
				iter->counterpart->previous = iter->previous;
				delete iter;
				return;
			}
		}
	}
	return;
}

bool WorkPlan::checkCycledList()
{				
	Task *pivot=new Task();
	pivot=head;
	int patient=100;
	bool r=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->previous;
		if(pivot==head)
		{
			r=true;
			break;
		}
	}
	cout<<"("<<100-patient<<")";
	patient=100;
	bool l=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->next;
		if(pivot==head)
		{
			l=true;
			break;
		}
	}
	return r&l;
}
