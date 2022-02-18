/************************************************
 * Name: sqrt.cpp
 * Author: Maciej Kowalczyk
 * Version: 1.0
 * Date: September 2, 2021
 * Description: Computes the square root of the command-line argument
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System
 ************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;


double sqrt(double num, double epsilon){

	if(num < 0){
		return numeric_limits<double>::quiet_NaN();
	}
	else if (num == 0 || num == 1){
		return num;
	}

	double last_guess = num;
	double next_guess = (last_guess + num / last_guess) / 2;

	while (abs(last_guess - next_guess) > epsilon){
		last_guess = next_guess;
		next_guess = (last_guess + num / last_guess) / 2;
	}

	return next_guess;
}

int main(int argc, char* argv[]){

	double num;
	double epsilon = 1e-7;
	istringstream iss;

	if (argc < 2 || argc > 3){
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if(!(iss >> num)){
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}
	iss.clear();

	if(argc == 3){
		iss.str(argv[2]);
		if((!(iss >> epsilon)) | (epsilon <= 0)){
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
	}

	cout.precision(8);
	cout << fixed << sqrt(num, epsilon) << endl;

	return 0;
}




