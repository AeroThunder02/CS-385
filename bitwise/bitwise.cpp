/*
 * bitwise.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: user
 */
#include <iostream>
#include <cmath>
using namespace std;

int mystery1(int a, int b){
	int c = a - b;
	int d = (c >> 7) & 1;
	return a - (c * d);
}

int mystery2(int x){
	return (x && !(x & (x - 1)));
}

int mystery3(int x, int y){
	int s, c;
	s = x ^ y;
	c = x & y;
	while (c != 0) {
		c = c << 1;
		x = s;
		y = c;
		s = x ^ y;
		c = x & y;
	}
	return s;
}

int main(int argc, char* argv[]){
	cout << mystery1(3, 7) << endl;
	cout << mystery1(8, 7) << endl;
	cout << " ---------------------------------" << endl;
	cout << mystery2(1) << endl;
	cout << mystery2(2) << endl;
	cout << mystery2(3) << endl;
	cout << mystery2(4) << endl;
	cout << mystery2(5) << endl;
	cout << mystery2(6) << endl;
	cout << mystery2(7) << endl;
	cout << mystery2(8) << endl;
	cout << " ---------------------------------" << endl;
	cout << mystery3(5, 7) << endl;
	cout << mystery3(2, 8) << endl;
	return 0;
}

