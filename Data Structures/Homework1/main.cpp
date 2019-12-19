/* @Author
Student Name: Mustafa Tosun
Student ID: 150170055
Date: 10.10.2019 */

#include <iostream>
#include <fstream>
#include "stock.h"
using namespace std;

int main(){
	ifstream input;
	input.open("input.txt"); // argv[1] is command line argument (input.txt)
	if (!input){
		cerr << "Unable to open input.txt";
		return 1;
	}
	stock Stock;
	Stock.create();
	int number;
	while (input>>number){
			if (number > 0){ // Adding shoes to stock
				Stock.add_stock(number);
			}
			else if (number < 0){ // Selling shoes
				Stock.sell(-number);
			}
			else{ // Printing stock info
				Stock.current_stock();
			}
	}
	Stock.clear();
	input.close();
	getchar();
	return 0;
}