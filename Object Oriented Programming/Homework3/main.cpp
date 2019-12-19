/* @Author
* Student Name: Mustafa Tosun
* Student ID : 150170055
* Date: 8/5/2019 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Table{
	string name;
	int lines; // first number readed below table name
	vector<string> dishes;
public:
	void set_lines(int line){this->lines=line;}
	int get_lines(){return lines;}
	string get_name(){return name;}
	void set_dishes(string dish, int nums){
		for(int i=0 ; i<nums ; i++){
			dishes.push_back(dish);
		}
	}
	string& get_dish_name(int index){
		return dishes[index];
	}
	int get_size_of_dishes(){
		return dishes.size();
	}
	Table(string name, int lines){
		this->name=name; 
		this->lines=lines;
	}
	Table(string name){
		this->name=name;
	}
/*	~Table(){
		delete dishes;
	}*/

};


class Ingredient{
	double price; //price per grams/unit/mililiter
	string item_name;
public:
	Ingredient(string item_name, double price){
		this->price=price;
		this->item_name=item_name;
	}
	Ingredient(string item_name){
		this->item_name=item_name;
	}
	string get_name(){return item_name;}
	double get_price(){
		return price;
	}
	virtual int get_count(){
		return 0;
	}
	virtual void set_count(int count){
		cout<<"Base";
	}
	virtual int get_type(){
		return 0;
	}
	
};
class Dish{
	string name;
	vector<Ingredient *> ingredients;
public:
	Dish(string name){this->name=name;}
	string get_name(){
		return name;
	}
	void push_ingredients(Ingredient *ingredient){ingredients.push_back(ingredient);}
	Ingredient* get_ingredient(int index){
		return ingredients[index];
	}
	int get_ingredients_size(){
		return ingredients.size();
	}
	void print_dish(){
		cout<<"Dish name: "<<name<<endl;
		cout<<"Ingredients: "<<endl;
		for(long unsigned int i=0 ; i<ingredients.size() ; i++){
			cout<<ingredients[i]->get_name()<<endl;
		}
	}
/*	~Dish(){
		for(int i=0 ; i<ingredients.size() ; i++){
			delete ingredients[i];
		}
	}*/
};


class Type1: public Ingredient{
	int weight;
public:
	Type1(string item_name, int weight, double price);
	Type1(string item_name, int weight);
	virtual int get_count(){
		return weight;
	}
	virtual void set_count(int weight){
		this->weight = weight;
	}
	virtual int get_type(){
		return 1;
	}
};
Type1::Type1(string item_name, int weight, double price):Ingredient(item_name, price){
	this->weight = weight;
};
Type1::Type1(string item_name, int weight):Ingredient(item_name){
	this->weight = weight;
}

class Type2: public Ingredient{
	int number;
public:
	Type2(string item_name, int number, double price);
	Type2(string item_name, int number);
	virtual int get_count(){
		return number;
	}
	virtual void set_count(int number){
		this->number = number;
	}
	virtual int get_type(){
		return 2;
	}
};
Type2::Type2(string item_name, int number, double price):Ingredient(item_name, price){
	this->number = number;
};
Type2::Type2(string item_name, int number):Ingredient(item_name){
	this->number = number;
}


class Type3: public Ingredient{
	int mililiter;
public:
	Type3(string item_name, int mililiter, double price);
	Type3(string item_name, int mililiter);
	virtual int get_count(){
		return mililiter;
	}
	virtual void set_count(int mililiter){
		this->mililiter = mililiter;
	}
	virtual int get_type(){
		return 3;
	}
};
Type3::Type3(string item_name, int mililiter, double price):Ingredient(item_name, price){
	this->mililiter = mililiter;
};
Type3::Type3(string item_name, int mililiter):Ingredient(item_name){
	this->mililiter = mililiter;
}


int main(){

	// Reading stock.txt
	fstream stock;
	stock.open("stock.txt");
	if(!stock){
		cerr << "ERROR: Unable to open stock.txt" << endl;
		return 1;
	}

	string empty;
	getline(stock,empty); // for first line
	string stock_str;
	vector<Ingredient *> stock_list;
	while(getline(stock, stock_str)){
		long unsigned int index=0;
		string item_name;
		while(stock_str[index]!='\t'){
			item_name.push_back(stock_str[index]);
			index++;
		}
		index++;
		string type_str;
		while(stock_str[index]!='\t'){
			type_str.push_back(stock_str[index]);
			index++;
		}
		stringstream typestream(type_str);
		int type;
		typestream >> type;
		index++;
		string count_str;
		while(stock_str[index]!='\t'){
			count_str.push_back(stock_str[index]);
			index++;
		}
		stringstream countstream(count_str);
		int item_count;
		countstream >> item_count;
		index++;
		string price_str;
		while(index < stock_str.size()){
			price_str.push_back(stock_str[index]);
			index++;
		}
		stringstream pricestream(price_str);
		double price;
		pricestream >> price;
	
		switch(type){
			case 1:
				stock_list.push_back(new Type1(item_name, item_count, price));
				break;
			case 2:
				stock_list.push_back(new Type2(item_name, item_count, price));
				break;
			case 3:
				stock_list.push_back(new Type3(item_name, item_count, price));
				break;
		}
	}
	stock.close();

	// Reading menu.txt
	fstream menu;
	menu.open("menu.txt");
	if(!menu){
		cerr << "ERROR: Unable to open menu.txt" << endl;
		return 1;
	}
	getline(menu,empty); // for first line
	vector<Dish> dish_list;
	int dish_index=0;
	string str;
	while(getline(menu,str)){
		long unsigned int index=0;
		string dish;
		
		while(str[index]!='\t'){
			dish.push_back(str[index]);
			index++;
		}
		dish_list.push_back(Dish(dish));
		index++;
		while(index<str.size()-1){
			string ingredient;
			while(str[index]!=','){
				ingredient.push_back(str[index]);
				index++;
				if(index==str.size()-1) break;
			}
			long unsigned int i=0;
			int count;
			string count_str;
			string ingredient_name;
			while(ingredient[i]!=' '){
				count_str.push_back(ingredient[i]);
				i++;
			}
			if(count_str[0]!='N'){
				stringstream countstream(count_str);
				countstream >> count;
				i++;
				if(ingredient[i]=='g' && ingredient[i+1]=='r' && ingredient[i+2]=='a' && ingredient[i+3]=='m'){
					i+=5;
					while(i<ingredient.size()){
						ingredient_name.push_back(ingredient[i]);
						i++;
					}
					dish_list[dish_index].push_ingredients(new Type1(ingredient_name, count));
				}
				else if(ingredient[i]=='m' && ingredient[i+1]=='l'){
					i+=3;
					while(i<ingredient.size()){
						ingredient_name.push_back(ingredient[i]);
						i++;
					}
					dish_list[dish_index].push_ingredients(new Type3(ingredient_name, count));
				}
				else{
					while(i<ingredient.size()){
						ingredient_name.push_back(ingredient[i]);
						i++;
					}
					dish_list[dish_index].push_ingredients(new Type2(ingredient_name, count));
				}
				index+=2;
			}
			else{
				dish_list[dish_index].push_ingredients(new Type2(dish, 1));
			}
		}
		dish_index++;
	}
	menu.close();
		
	// Reading order.txt
	fstream orders;
	orders.open("order.txt");
	if(!orders){
		cerr << "ERROR: Unable to open order.txt" << endl;
		return 1;
	}
	
	int j=-1;
	vector<Table> tables;
	string orders_str;
	while(getline(orders,orders_str)){
		long unsigned int index=0;
		string table_name;
		int table_lines;
		string num_str;
		int num_dish;
		string name_dish;
		if(orders_str[0]=='T'){
			table_name=orders_str;
			if(table_name[table_name.size()-1]==13) table_name.erase(table_name.size()-1);
			tables.push_back(Table(table_name));
			j = j+1;

		}
		else if(orders_str.size()==2){
			stringstream linestream(orders_str);
			linestream >> table_lines;
			tables[j].set_lines(table_lines);
		}
		else{
			while(orders_str[index]!=' '){
				num_str.push_back(orders_str[index]);
				index++;
			}
			stringstream numstream(num_str);
			numstream >> num_dish;
			index++;
			while(index<orders_str.size()){
				if(orders_str[index]==13) break;
				name_dish.push_back(orders_str[index]);
				index++;
			}
			tables[j].set_dishes(name_dish,num_dish);
		}
		
	}
	orders.close();
	
	// Calculations and output
	for(long unsigned int i=0 ; i<tables.size() ; i++){
		double check=0;
		double tip=0;
		double tax_rate=0;
		cout<<tables[i].get_name()<<" ordered:"<<endl;

		for(int j=0 ; j<tables[i].get_size_of_dishes() ; j++){
			bool flag=false;
			int k=0;
			while(dish_list[k].get_name()!=tables[i].get_dish_name(j)) k++;
			int number=1;
			while(tables[i].get_dish_name(j)==tables[i].get_dish_name(j+1)){
				number++;
				j++;
			}
			int num_served=0;
			int x=1;
			while(x<=number){
			for(int l=0 ; l<dish_list[k].get_ingredients_size() ; l++){
				Ingredient *menuptr = dish_list[k].get_ingredient(l);
				int m=0;
				while(menuptr->get_name()!=stock_list[m]->get_name()) m++;

				if(menuptr->get_count()*x > stock_list[m]->get_count()){
					flag=true;
				}
			}
			if(!flag) num_served++;
			x++;
			}
			if(num_served!=number){
				while(tables[i].get_dish_name(j) == tables[i].get_dish_name(j+1)) j++;
				cout<<"We don't have enough "<<tables[i].get_dish_name(j)<<endl;
			}
			if(num_served!=0){
				double cost=0;
				for(int l=0 ; l<dish_list[k].get_ingredients_size() ; l++){
					Ingredient *menuptr = dish_list[k].get_ingredient(l);
					int m=0;
					while(menuptr->get_name()!=stock_list[m]->get_name()) m++;
					for(int q=0 ; q<num_served ; q++){
						stock_list[m]->set_count(stock_list[m]->get_count()-menuptr->get_count());
						cost += menuptr->get_count()*stock_list[m]->get_price();
					}
				}
				check+=cost;
				cout<<num_served<<" "<<tables[i].get_dish_name(j);
				cout<<" cost = "<<cost<<endl;
			}
		}
		tip=check*15/100;
		tax_rate=check*8/100;
		check=check+tip+tax_rate;
		cout<<"Tip is "<<tip<<endl;
		cout<<"Total cost: "<<check<<" TL"<<endl;
	}
	
	// Update stock.txt
	ofstream temp;
	temp.open("temp.txt");
	temp<<"Name"<<'\t'<<"Type"<<'\t'<<"ItemCount"<<'\t'<<"Price"<<endl;
	for(int i=0 ; i<27 ; i++){
		temp<<stock_list[i]->get_name()<<'\t';
		temp<<stock_list[i]->get_type()<<'\t';
		temp<<stock_list[i]->get_count()<<'\t';
		temp<<stock_list[i]->get_price()<<endl;
	}
	temp.close();
	remove("stock.txt");
	rename("temp.txt", "stock.txt");


	return 0;
}