/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Maciej Kowalczyk
 * Date        : 9/23/21
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      :I pledge my Honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

bool is_all_lowercase(const string &s) {
    for(const auto &c: s){
    	if(c < 'a' || c > 'z'){
    		return false;
    	}
    }
    return true;
}

bool all_unique_letters(const string &s) {
	unsigned int bit_tracker = 0;
	for(const auto &c: s){
		unsigned int setter = 1 << (c - 'a');
		if (setter & bit_tracker){
			return false;
		}
		bit_tracker = bit_tracker | setter;
	}
	return true;
}

int main(int argc, char * const argv[]) {

	istringstream iss;
	string s;

	if(argc > 2 || argc < 2){
		cerr << "Usage: " << argv[0] << " <string>" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if(!(iss >> s) | !(is_all_lowercase(s))){
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}
	iss.clear();

	if(s.length() > 26 || !(all_unique_letters(s))){
		cout << "Duplicate letters found." << endl;
	}
	else{
		cout << "All letters are unique." << endl;
	}

	return 0;
}
