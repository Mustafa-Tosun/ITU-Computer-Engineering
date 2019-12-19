/*
	Mustafa Tosun
	  150170055
*/

#include <iostream>
#include <string>
using namespace std;
#ifndef MAX_OPERATOR_SIZE
#define MAX_OPERATOR_SIZE 500
#endif

class Operator{
	int center_x;
	int center_y;
	int op_size;
 
public:
	Operator(int x, int y, int size); // Constructor
	
	void reset(int new_x, int new_y, int new_size);

	void set_x(int new_x){center_x = new_x; }
	int get_x(){ return center_x; }

	void set_y(int new_y){center_y = new_y; }
	int get_y(){ return center_y; }

	void set_size(int new_size){ op_size = new_size; }
	int get_size(){ return op_size; }
};

Operator::Operator(int x, int y, int size){
	center_x = x;
	center_y = y;
	op_size = size;
}

void Operator::reset(int new_x, int new_y, int new_size){
	center_x = new_x;
	center_y = new_y;
	op_size = new_size;
}

class ArithmeticOperator: public Operator{
	char sign;

public:
	ArithmeticOperator(int x, int y, int size, char sign);
	char get_sign(){ return sign; }
	// Prints out operator's center location, size and sign character
	void print_operator(){
		cout<<"ARITHMETIC_OPERATOR["<<get_sign()<<"], CENTER_LOCATION["<<get_x()<<','<<get_y()<<"], SIZE["<<get_size()<<']'<<endl;
	}

};

ArithmeticOperator::ArithmeticOperator(int x, int y, int size, char sign):Operator(x, y, size)
{
	if(sign!='+' && sign!='-' && sign!='x' && sign!='/'){
		cout<<"SIGN parameter is invalid!"<<endl;
		this->sign='0';
	}
	else{
		this->sign=sign;
	}
}

class OperatorGrid{
	int grid_rows;
	int grid_cols;
	char **grid;
	int num_operators;
	ArithmeticOperator *operators[MAX_OPERATOR_SIZE];

public:
	OperatorGrid(int rows, int cols);
	~OperatorGrid();
	bool place_operator(ArithmeticOperator *);
	bool move_operator(int x, int y, char direction, int move_by);
	void print_operators(){
		for(int i=0 ; i<num_operators ; i++){
			operators[i]->print_operator();
		}
	}
};

OperatorGrid::OperatorGrid(int rows, int cols){
	num_operators=0;
	grid_rows = rows;
	grid_cols = cols;
	grid = new char*[grid_rows];
	for(int i=0;i<grid_rows;i++){
		grid[i] = new char[grid_cols];
	}
	for(int i=0;i<grid_rows;i++){
		for(int j=0;j<grid_cols;j++){
			grid[i][j]='0';
		}
	}
}

OperatorGrid::~OperatorGrid(){
	for (int i = 0; i < grid_rows; i++) {
		delete[] grid[i];
	}
	delete[] grid;
	cout<<"DESTRUCTOR: GIVE BACK["<<grid_rows<<','<<grid_cols<<"] chars."<<endl;
	if(num_operators!=0){
	for(int i=1 ; i<num_operators ; i++){
		delete operators[i];
	}
	delete[] *operators;
	}	
	cout<<"DESTRUCTOR: GIVE BACK["<<num_operators<<"] Operators."<<endl;
}

bool OperatorGrid::place_operator(ArithmeticOperator *op){
	ArithmeticOperator *new_op;
	int i;
	bool conflict=false; // false means no conflict error
	bool border=false; // false means no border error
	bool sign_flag=false; // false means sign is valid
	switch(op->get_sign()){
		case '-':
			if(grid_cols <= op->get_y()-1+op->get_size() || 0 > op->get_y()-1-op->get_size()){
				border = true;
			}
			break;
		case '+':
		case 'x':
		case '/':
			if(grid_rows <= op->get_x()-1+op->get_size() || 0 > op->get_x()-1-op->get_size() || grid_cols <= op->get_y()-1+op->get_size() || 0 > op->get_y()-1-op->get_size() ){
				border=true;
			}
			break;
		default:
			sign_flag=true;
			break;
	}
	switch(op->get_sign()){
		case '+':
			for(i=0; i<=op->get_size(); i++){
				if(grid_rows > op->get_x()-1+i && 0 <= op->get_x()-1-i && grid_cols > op->get_y()-1 && 0 <= op->get_y()-1 ) {
					if(grid[op->get_x()-1+i][op->get_y()-1] != '0') conflict=true; 
				}
				if(grid_rows > op->get_x()-1+i && 0 <= op->get_x()-1-i && grid_cols > op->get_y()-1 && 0 <= op->get_y()-1){
					if(grid[op->get_x()-1-i][op->get_y()-1] != '0') conflict=true;
				}
				if(grid_rows > op->get_x()-1 && 0 <= op->get_x()-1 && grid_cols > op->get_y()-1+i && 0 <= op->get_y()-1+i){
					if(grid[op->get_x()-1][op->get_y()-1+i] != '0') conflict=true;
				}
				if(grid_rows > op->get_x()-1 && 0 <= op->get_x()-1 && grid_cols > op->get_y()-1-i && 0 <= op->get_y()-1-i){
					if(grid[op->get_x()-1][op->get_y()-1-i] != '0') conflict=true;
				}
			}
			if (conflict == false && border==false){
				for(i=0; i<=op->get_size(); i++){
					grid[op->get_x()+i-1][op->get_y()-1] = op->get_sign();
					grid[op->get_x()-1][op->get_y()+i-1] = op->get_sign();
					grid[op->get_x()-1][op->get_y()-i-1] = op->get_sign();
					grid[op->get_x()-i-1][op->get_y()-1] = op->get_sign();
				}
			}
			break;
		case '-':
			for(i=0; i<=op->get_size(); i++){
				if(0 <= op->get_x()-1 && grid_rows > op->get_x()-1 && grid_cols > op->get_y()-1+i && 0 <= op->get_y()-1+i ){
					if(grid[op->get_x()-1][op->get_y()-1+i] != '0') conflict=true;
				}
				if(0 <= op->get_x()-1 && grid_rows > op->get_x()-1 && grid_cols > op->get_y()-1-i && 0 <= op->get_y()-1-i){
					if(grid[op->get_x()-1][op->get_y()-1-i] != '0') conflict=true;
				}
			}
			if(conflict == false && border==false){
				for(i=0; i<=op->get_size(); i++){
					grid[op->get_x()-1][op->get_y()+i-1] = op->get_sign();
					grid[op->get_x()-1][op->get_y()-i-1] = op->get_sign();
				}
			}
			break;
		case 'x':
			for(i=0; i<=op->get_size(); i++){
				if(grid_rows > op->get_x()-1+i && 0 <= op->get_x()-1+i && grid_cols > op->get_y()-1+i && 0 <= op->get_y()-1+i ) {
					if(grid[op->get_x()-1+i][op->get_y()-1+i] != '0') conflict=true; 
				}
				if(grid_rows > op->get_x()-1+i && 0 <= op->get_x()-1+i && grid_cols > op->get_y()-1-i && 0 <= op->get_y()-1-i ) {
					if(grid[op->get_x()-1+i][op->get_y()-1-i] != '0') conflict=true; 
				}
				if(grid_rows > op->get_x()-1-i && 0 <= op->get_x()-1-i && grid_cols > op->get_y()-1-i && 0 <= op->get_y()-1-i ) {
					if(grid[op->get_x()-1-i][op->get_y()-1-i] != '0') conflict=true; 
				}
				if(grid_rows > op->get_x()-1-i && 0 <= op->get_x()-1-i && grid_cols > op->get_y()-1+i && 0 <= op->get_y()-1+i ) {
					if(grid[op->get_x()-1-i][op->get_y()-1+i] != '0') conflict=true; 
				}
			}
			if(conflict == false && border==false){
				for(i=0; i<=op->get_size(); i++){
					grid[op->get_x()+i-1][op->get_y()+i-1] = op->get_sign();
					grid[op->get_x()+i-1][op->get_y()-i-1] = op->get_sign();
					grid[op->get_x()-i-1][op->get_y()-i-1] = op->get_sign();
					grid[op->get_x()-i-1][op->get_y()+i-1] = op->get_sign();
				}
			}
			break;
		case '/':
			for(i=0; i<=op->get_size(); i++){
				if(0 <= op->get_x()-1-i && grid_rows > op->get_x()-1-i && grid_cols > op->get_y()-1+i && 0 <= op->get_y()-1+i ){
					if(grid[op->get_x()-1-i][op->get_y()-1+i] != '0') conflict=true;
				}
				if(0 <= op->get_x()-1+i && grid_rows > op->get_x()-1+i && grid_cols > op->get_y()-1-i && 0 <= op->get_y()-1-i){
					if(grid[op->get_x()-1+i][op->get_y()-1-i] != '0') conflict=true;
				}
			}
			if(conflict == false && border==false){
				for(i=0; i<=op->get_size(); i++){
					grid[op->get_x()+i-1][op->get_y()-i-1] = op->get_sign();
					grid[op->get_x()-i-1][op->get_y()+i-1] = op->get_sign();
				}
			}
			break;
		default :
			break;
	}
	if(conflict==true && border==true && sign_flag==false){
		cout<<"BORDER ERROR: Operator "<<op->get_sign()<<" with size "<<op->get_size()<<" can not be placed on ("<<op->get_x()<<','<<op->get_y()<<")."<<endl;
		cout<<"CONFLICT ERROR: Operator "<<op->get_sign()<<" with size "<<op->get_size()<<" can not be placed on ("<<op->get_x()<<','<<op->get_y()<<")."<<endl;
		return false;
	}
	else if(conflict==true && border==false && sign_flag==false){
		cout<<"CONFLICT ERROR: Operator "<<op->get_sign()<<" with size "<<op->get_size()<<" can not be placed on ("<<op->get_x()<<','<<op->get_y()<<")."<<endl;
		return false;
	}
	else if(conflict==false && border==true && sign_flag==false){
		cout<<"BORDER ERROR: Operator "<<op->get_sign()<<" with size "<<op->get_size()<<" can not be placed on ("<<op->get_x()<<','<<op->get_y()<<")."<<endl;
		return false;
	}
	else if(conflict==false && border==false && sign_flag==false){
		cout<<"SUCCESS: Operator "<<op->get_sign()<<" with size "<<op->get_size()<<" is placed on ("<<op->get_x()<<','<<op->get_y()<<")."<<endl;
		new_op=new ArithmeticOperator(op->get_x(), op->get_y(), op->get_size(), op->get_sign());
		operators[num_operators]=new_op;
		num_operators+=1;
		return true;
	}
	else{
		return false;
	}
}

bool OperatorGrid::move_operator(int x, int y, char direction, int move_by){
	bool sign_flag=false;
	bool conflict=false;
	bool border=false;
	int cen_x,cen_y,size,x_after,y_after,it_op;
	char sign=grid[x-1][y-1];
	switch(sign){
		case '+':
			for(int i=0 ; i<num_operators ; i++){
				for(int j=0 ; j<=operators[i]->get_size() ; j++){
					if( (x==operators[i]->get_x()+j && y==operators[i]->get_y() ) || ( x==operators[i]->get_x()-j && y==operators[i]->get_y() ) || ( y==operators[i]->get_y()+j && x==operators[i]->get_x() ) || ( y==operators[i]->get_y()-j && x==operators[i]->get_x() ) ) {
						if(grid[operators[i]->get_x()-1][operators[i]->get_y()-1]=='+'){
						cen_x = operators[i]->get_x();
						cen_y = operators[i]->get_y();
						size = operators[i]->get_size();
						it_op=i;
						}
					}
				}
			}
			for(int i=0 ; i<=size ; i++){
				grid[cen_x+i-1][cen_y-1] = '0';
				grid[cen_x-1][cen_y+i-1] = '0';
				grid[cen_x-1][cen_y-i-1] = '0';
				grid[cen_x-i-1][cen_y-1] = '0';
			}
			switch(direction){
				case 'R':
					if(grid_cols <= cen_y-1+size+move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(grid_cols > cen_y-1+i+move_by){
							if(grid[cen_x+i-1][cen_y-1+move_by] != '0' || grid[cen_x-1][cen_y+i-1+move_by] != '0' || grid[cen_x-1][cen_y-i-1+move_by] != '0' || grid[cen_x-i-1][cen_y-1+move_by] != '0'){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1][cen_y-1+move_by] = sign;
							grid[cen_x-1][cen_y+i-1+move_by] = sign;
							grid[cen_x-1][cen_y-i-1+move_by] = sign;
							grid[cen_x-i-1][cen_y-1+move_by] = sign;	
						}
					}
					x_after = cen_x;
					y_after = cen_y+move_by;	
					break;
				case 'L':
					if(0 > cen_y-1-size-move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(0 <= cen_y-1-i-move_by){
							if(grid[cen_x+i-1][cen_y-1-move_by] != '0' || grid[cen_x-1][cen_y+i-1-move_by] != '0' || grid[cen_x-1][cen_y-i-1-move_by] != '0' || grid[cen_x-i-1][cen_y-1-move_by] != '0'){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1][cen_y-1-move_by] = sign;
							grid[cen_x-1][cen_y+i-1-move_by] = sign;
							grid[cen_x-1][cen_y-i-1-move_by] = sign;
							grid[cen_x-i-1][cen_y-1-move_by] = sign;
						}
					}
					x_after = cen_x;
					y_after = cen_y-move_by;
					break;
				case 'U':
					if(0 > cen_x-1-size-move_by){
						border = true;

					}
					for(int i=0 ; i<=size ; i++){
						if(0 <= cen_x-1-i-move_by){
							if(grid[cen_x+i-1-move_by][cen_y-1] != '0' || grid[cen_x-1-move_by][cen_y+i-1] != '0' || grid[cen_x-1-move_by][cen_y-i-1] != '0' || grid[cen_x-i-1-move_by][cen_y-1] != '0'){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1-move_by][cen_y-1] = sign;
							grid[cen_x-1-move_by][cen_y+i-1] = sign;
							grid[cen_x-1-move_by][cen_y-i-1] = sign;
							grid[cen_x-i-1-move_by][cen_y-1] = sign;
						}
					}
					x_after = cen_x-move_by;
					y_after = cen_y;
					break;
				case 'D':
					if(grid_rows <= cen_x-1+size+move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(grid_rows > cen_x-1+i+move_by){
							if(grid[cen_x+i-1+move_by][cen_y-1] != '0' || grid[cen_x-1+move_by][cen_y+i-1] != '0' || grid[cen_x-1+move_by][cen_y-i-1] != '0' || grid[cen_x-i-1+move_by][cen_y-1] != '0'){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1+move_by][cen_y-1] = sign;
							grid[cen_x-1+move_by][cen_y+i-1] = sign;
							grid[cen_x-1+move_by][cen_y-i-1] = sign;
							grid[cen_x-i-1+move_by][cen_y-1] = sign;		
						}
					}
					x_after = cen_x+move_by;
					y_after = cen_y;
					break;
				default:
					break;
			}
			if(conflict==true || border==true){
				for(int i=0 ; i<=size ; i++){
					grid[cen_x+i-1][cen_y-1] = sign;
					grid[cen_x-1][cen_y+i-1] = sign;
					grid[cen_x-1][cen_y-i-1] = sign;
					grid[cen_x-i-1][cen_y-1] = sign;				
				}
			}
			break;
		case '-':
			for (int i=0 ; i<num_operators ; i++){
				for(int j=0 ; j<=operators[i]->get_size() ; j++){
					if( ( x==operators[i]->get_x() )&& (y==operators[i]->get_y()+j || y==operators[i]->get_y()-j)){
						if(grid[operators[i]->get_x()-1][operators[i]->get_y()-1]=='-'){
						cen_x = operators[i]->get_x();
						cen_y = operators[i]->get_y();
						size = operators[i]->get_size();
						it_op=i;
						}
					}
				}
			}
			for(int i=0 ; i<=size ; i++){
				grid[cen_x-1][cen_y+i-1] = '0';
				grid[cen_x-1][cen_y-i-1] = '0';	
			}
			switch(direction){
				case 'R':
					if(grid_cols <= cen_y-1+size+move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(grid_cols > cen_y-1+i+move_by){
							if(grid[cen_x-1][cen_y+i-1+move_by] != '0' || grid[cen_x-1][cen_y-i-1+move_by] != '0' ){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x-1][cen_y+i-1+move_by] = sign;
							grid[cen_x-1][cen_y-i-1+move_by] = sign;		
						}
					}
					x_after = cen_x;
					y_after = cen_y+move_by;
					break;
				case 'L':
					if(0 > cen_y-1-size-move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(0 <= cen_y-1-i-move_by){
							if(grid[cen_x-1][cen_y+i-1-move_by] != '0' || grid[cen_x-1][cen_y-i-1-move_by] != '0' ){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x-1][cen_y+i-1-move_by] = sign;
							grid[cen_x-1][cen_y-i-1-move_by] = sign;		
						}
					}
					x_after = cen_x;
					y_after = cen_y-move_by;
					break;
				case 'U':
					if(0 > cen_x-1-move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(0 <= cen_x-1-move_by){
							if(grid[cen_x-1-move_by][cen_y+i-1] != '0' || grid[cen_x-1-move_by][cen_y-i-1] != '0' ){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x-1-move_by][cen_y+i-1] = sign;
							grid[cen_x-1-move_by][cen_y-i-1] = sign;		
						}
					}
					x_after = cen_x-move_by;
					y_after = cen_y;
					break;
				case 'D':
					if(grid_rows <= cen_x-1+move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(grid_rows > cen_x-1+move_by){
							if(grid[cen_x-1+move_by][cen_y+i-1] != '0' || grid[cen_x-1+move_by][cen_y-i-1] != '0' ){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x-1+move_by][cen_y+i-1] = sign;
							grid[cen_x-1+move_by][cen_y-i-1] = sign;		
						}
					}
					x_after = cen_x+move_by;
					y_after = cen_y;
					break;
				default:
					break;
			}
			if(conflict==true || border==true){
				for(int i=0 ; i<=size ; i++){
					grid[cen_x-1][cen_y+i-1] = sign;
					grid[cen_x-1][cen_y-i-1] = sign;
				}	
			}
			break;
		case 'x':
			for(int i=0 ; i<num_operators ; i++){
				for(int j=0 ; j<=operators[i]->get_size() ; j++){
					if((x==operators[i]->get_x()+j && (y==operators[i]->get_y()+j || y== operators[i]->get_y()-j)) || (x==operators[i]->get_x()-j && (y==operators[i]->get_y()+j || y==operators[i]->get_y()-j) )){
						if(grid[operators[i]->get_x()-1][operators[i]->get_y()-1]=='x'){
						cen_x = operators[i]->get_x();
						cen_y = operators[i]->get_y();
						size = operators[i]->get_size();
						it_op=i;
						}
					}
				}
			}
			for(int i=0 ; i<=size ; i++){
				grid[cen_x+i-1][cen_y+i-1] = '0';
				grid[cen_x+i-1][cen_y-i-1] = '0';
				grid[cen_x-i-1][cen_y-i-1] = '0';
				grid[cen_x-i-1][cen_y+i-1] = '0';		
			}
			switch(direction){
				case 'R':
					if(grid_cols <= cen_y-1+size+move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(grid_cols > cen_y-1+i+move_by){
							if(grid[cen_x+i-1][cen_y+i-1+move_by] != '0' || grid[cen_x+i-1][cen_y-i-1+move_by] != '0' || grid[cen_x-i-1][cen_y-i-1+move_by] != '0' || grid[cen_x-i-1][cen_y+i-1+move_by] != '0'){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1][cen_y+i-1+move_by] = sign;
							grid[cen_x+i-1][cen_y-i-1+move_by] = sign;
							grid[cen_x-i-1][cen_y-i-1+move_by] = sign;
							grid[cen_x-i-1][cen_y+i-1+move_by] = sign;							
						}
					}
					x_after = cen_x;
					y_after = cen_y+move_by;
					break;
				case 'L':
					if(0 > cen_y-1-size-move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(0 <= cen_y-1-i-move_by){
							if(grid[cen_x+i-1][cen_y+i-1-move_by] != '0' || grid[cen_x+i-1][cen_y-i-1-move_by] != '0' || grid[cen_x-i-1][cen_y-i-1-move_by] != '0' || grid[cen_x-i-1][cen_y+i-1-move_by] != '0'){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1][cen_y+i-1-move_by] = sign;
							grid[cen_x+i-1][cen_y-i-1-move_by] = sign;
							grid[cen_x-i-1][cen_y-i-1-move_by] = sign;
							grid[cen_x-i-1][cen_y+i-1-move_by] = sign;		
						}
					}
					x_after = cen_x;
					y_after = cen_y-move_by;
					break;
				case 'U':
					if(0 > cen_x-1-size-move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(0 <= cen_x-1-i-move_by){
							if(grid[cen_x+i-1-move_by][cen_y+i-1] != '0' || grid[cen_x+i-1-move_by][cen_y-i-1] != '0' || grid[cen_x-i-1-move_by][cen_y-i-1] != '0' || grid[cen_x-i-1-move_by][cen_y+i-1] != '0'){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1-move_by][cen_y+i-1] = sign;
							grid[cen_x+i-1-move_by][cen_y-i-1] = sign;
							grid[cen_x-i-1-move_by][cen_y-i-1] = sign;
							grid[cen_x-i-1-move_by][cen_y+i-1] = sign;
						}
					}
					x_after = cen_x-move_by;
					y_after = cen_y;
					break;
				case 'D':
					if(grid_rows <= cen_x-1+size+move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(grid_rows > cen_x-1+i+move_by){
							if(grid[cen_x+i-1+move_by][cen_y+i-1] != '0' || grid[cen_x+i-1+move_by][cen_y-i-1] != '0' || grid[cen_x-i-1+move_by][cen_y-i-1] != '0' || grid[cen_x-i-1+move_by][cen_y+i-1] != '0'){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1+move_by][cen_y+i-1] = sign;
							grid[cen_x+i-1+move_by][cen_y-i-1] = sign;
							grid[cen_x-i-1+move_by][cen_y-i-1] = sign;
							grid[cen_x-i-1+move_by][cen_y+i-1] = sign;
						}
					}
					x_after = cen_x+move_by;
					y_after = cen_y;
					break;
				default:
					break;
			}
			if(conflict==true || border==true){
				for(int i=0 ; i<=size ; i++){
					grid[cen_x+i-1][cen_y+i-1] = sign;
					grid[cen_x+i-1][cen_y-i-1] = sign;
					grid[cen_x-i-1][cen_y-i-1] = sign;
					grid[cen_x-i-1][cen_y+i-1] = sign;
				}
			}
			break;
		case '/':
			for(int i=0 ; i<num_operators ; i++){
				for(int j=0 ; j<=operators[i]->get_size() ; j++){
					if((x==operators[i]->get_x()+j && y==operators[i]->get_y()-j) ||(x==operators[i]->get_x()-j && y==operators[i]->get_y()+j )){
						if(grid[operators[i]->get_x()-1][operators[i]->get_y()-1]=='/'){
						cen_x = operators[i]->get_x();
						cen_y = operators[i]->get_y();
						size = operators[i]->get_size();
						it_op=i;
						}
					}
				}
			}
			for(int i=0 ; i<=size ; i++){
				grid[cen_x+i-1][cen_y-i-1] = '0';
				grid[cen_x-i-1][cen_y+i-1] = '0';		
			}
			switch(direction){
				case 'R':
					if(grid_cols <= cen_y-1+size+move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(grid_cols > cen_y-1+i+move_by){
							if(grid[cen_x+i-1][cen_y-i-1+move_by] != '0' || grid[cen_x-i-1][cen_y+i-1+move_by] != '0' ){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1][cen_y-i-1+move_by] = sign;
							grid[cen_x-i-1][cen_y+i-1+move_by] = sign;		
						}
					}
					x_after = cen_x;
					y_after = cen_y+move_by;
					break;
				case 'L':
					if(0 > cen_y-1-size-move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(0 <= cen_y-1-i-move_by){
							if(grid[cen_x+i-1][cen_y-i-1-move_by] != '0' || grid[cen_x-i-1][cen_y+i-1-move_by] != '0' ){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1][cen_y-i-1-move_by] = sign;
							grid[cen_x-i-1][cen_y+i-1-move_by] = sign;		
						}
					}
					x_after = cen_x;
					y_after = cen_y-move_by;
					break;
				case 'U':
					if(0 > cen_x-1-size-move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(0 <= cen_x-1-i-move_by){
							if(grid[cen_x+i-1-move_by][cen_y-i-1] != '0' || grid[cen_x-i-1-move_by][cen_y+i-1] != '0' ){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1-move_by][cen_y-i-1] = sign;
							grid[cen_x-i-1-move_by][cen_y+i-1] = sign;
						}
					}
					x_after = cen_x-move_by;
					y_after = cen_y;
					break;
				case 'D':
					if(grid_rows <= cen_x-1+size+move_by){
						border = true;
					}
					for(int i=0 ; i<=size ; i++){
						if(grid_rows > cen_x-1+i+move_by){
							if(grid[cen_x+i-1+move_by][cen_y-i-1] != '0' || grid[cen_x-i-1+move_by][cen_y+i-1] != '0' ){
								conflict = true;
								break;
							}
						}
					}
					if(conflict==false && border==false){
						for(int i=0 ; i<=size ; i++){
							grid[cen_x+i-1+move_by][cen_y-i-1] = sign;
							grid[cen_x-i-1+move_by][cen_y+i-1] = sign;
						}
					}
					x_after = cen_x+move_by;
					y_after = cen_y;
					break;
				default:
					break;
			}
			if(conflict==true || border==true){
				for(int i=0 ; i<=size ; i++){
					grid[cen_x+i-1][cen_y-i-1] = sign;
					grid[cen_x-i-1][cen_y+i-1] = sign;		
				}
			}
			break;
		default:
			sign_flag=true;
			break;
	}
	if(conflict==true && border==true && sign_flag==false){
		cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<cen_x<<','<<cen_y<<") to ("<<x_after<<','<<y_after<<")."<<endl;
		cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<cen_x<<','<<cen_y<<") to ("<<x_after<<','<<y_after<<")."<<endl;
		return false;
	}
	else if(conflict==true && border==false && sign_flag==false){
		cout<<"CONFLICT ERROR: "<<sign<<" can not be moved from ("<<cen_x<<','<<cen_y<<") to ("<<x_after<<','<<y_after<<")."<<endl;
		return false;
	}
	else if(conflict==false && border==true && sign_flag==false){
		cout<<"BORDER ERROR: "<<sign<<" can not be moved from ("<<cen_x<<','<<cen_y<<") to ("<<x_after<<','<<y_after<<")."<<endl;
		return false;
	}
	else if(conflict==false && border==false && sign_flag==false){
		cout<<"SUCCESS: "<<sign<<" moved from ("<<cen_x<<','<<cen_y<<") to ("<<x_after<<','<<y_after<<")."<<endl;
		operators[it_op]->set_x(x_after);
		operators[it_op]->set_y(y_after);
		return true;
	}
	else{
		return false;
	}
}