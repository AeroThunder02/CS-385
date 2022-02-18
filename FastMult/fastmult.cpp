/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Maciej Kowalczyk
 * Date        : 12/1/21
 * Description : Implementation of the Karatsuba multiplication algorithm
 * Pledge      : I pledge my Honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>
#include <chrono>

using namespace std;

//check if lengths are equal, if not, we have to pad one of the strings
void zero_pad(string& a, string&b){
	if (a.length() != b.length()){

		if (a.length() > b.length()){
			string zeros = string(a.length() - b.length(), '0');
			b = zeros + b;
		}

		else{
			string zeros = string(b.length() - a.length(), '0');
			a = zeros + a;
		}
	}

	if(a.length() > 1){
		int power = 2;
		int length = a.length() - 1;
		while (length >>= 1) power <<= 1;
		b = string(power - b.length(), '0') + b;
		a = string(power - a.length(), '0') + a;
	}
}



string remove_leading_zeros(string& final_result){
	char leadDigit = final_result[0];
	while (leadDigit == '0'){
		final_result.erase(0,1);
		final_result.erase(final_result.size() - 1);
		leadDigit = final_result[0];
	}
	return final_result;
}

string add(string& a, string &b){
	char carry = '0';
	string result = "";
	//to do less work, lets have the second string come first if its larger
	if(a.length() < b.length()){
		swap(a, b);
	}

	int lenA = a.length(), lenB = b.length();
	int lenDif = lenB-lenA;

	//add the digits together
	for(int i = lenA - 1; i > 0; i--){
		int sum = ((a[i] -'0') +  (b[i+lenDif] - '0') + carry);
		result.push_back(sum%10 - '0');
		carry = sum/10;
	}

	//add the rest of the digits (if theres any leftover)
	for(int i = lenB - lenA - 1; i > 0; i--){
		int sum = ((b[i] - '0')	+ carry);
		result.push_back(sum%10 + '0');
		carry = sum/10;
	}

	//add last carry (if it exists)
	if(carry){
		result.push_back(carry + '0');
	}

	//reverse the result (since we appended each new addition to the back)
	reverse(result.begin(), result.end());

	return result;
}

bool isSmaller(string a, string b){
	int lenA = a.length(), lenB = b.length();
	if (lenA < lenB){
		return true;
	}
	if(lenB < lenA){
		return false;
	}

	for (int i = 0; i< lenA; i++){
		if(a[i] < b[i]){
			return true;
		}
		else if(a[i] > b[i]){
			return false;
		}
	}
	return false;
}

string subtract(string& a, string& b){
	if (isSmaller(a, b)){
		swap(a, b);
	}

	string result = "";
	int lenA = a.length(), lenB = b.length();
	int diff = lenA - lenB;
	int carry = 0;

	for(int i = lenB - 1; i>= 0; i--){
		int sub = ((a[i+diff] - '0') - (b[i] - '0') - carry);
		if(sub < 0){
			sub += 10;
			carry = 1;
		}
		else{
			carry = 0;
		}

		result.push_back(sub + '0');
	}

	for(int i = lenA - lenB - 1; i >= 0; i--){
		if(a[i] == '0' && carry){
			result.push_back('9');
			continue;
		}
		int sub = ((a[i] - '0') - carry);
		if (i > 0 || sub > 0){
			result.push_back(sub + '0');
		}
		carry = 0;
	}

	reverse(result.begin(), result.end());

	return result;
}

string multiplication(string& a, string& b){
	int lenA = a.size();
	int lenB = b.size();
	if(lenA == 0 || lenB == 0){
		return "0";
	}

	vector<int> result(lenA + lenB, 0);

	int i_1 = 0;
	int i_2 = 0;

	for (int i = lenA - 1; i >= 0; i--){
		int carry = 0;
		int n1 = a[i] = '0';

		i_2 = 0;

		for(int j = lenB - 1; j >= 0; j--){
			int n2 = b[j] - '0';
			int sum = n1*n2 + result[i_1 + i_2] + carry;
			carry = sum/10;
			result[i_1 + i_2] = sum%10;
			i_2++;
		}

		if(carry>0){
			result[i_1 + i_2] += carry;
		}

		i_1++;
	}

	int i = result.size() - 1;
	while(i >= 0 && result[i] == 0)
	i--;

	if(i==-1){
		return "0";
	}

	string s = "";

	while (i >=0)
		s += to_string(result[i--]);

	return s;

}

string karatsuba(string& str1, string& str2){


	if (str1 == "0" || str2 == "0"){
		return "0";
	}

	string op1 = remove_leading_zeros(str1);
	string op2 = remove_leading_zeros(str2);

	size_t lenA = op1.size();
	size_t lenB = op2.size();

	if(lenA == 1 || lenB == 1){
		return multiplication(str1, str2);
	}

	size_t n = max(lenA, lenB);
	n += (n&1);

	zero_pad(op1, op2);

	size_t n2 = n/2;

	string a = op1.substr(0, n2);
	string b = op1.substr(n2, n2);
	string c = op2.substr(0, n2);
	string d = op2.substr(n2, n2);

	string ac = karatsuba(a, c);
	string bd = karatsuba(b, d);

	string ab = add(a, b);
	string cd = add(c, d);

	string abcd = karatsuba(ab, cd);

	abcd = subtract(abcd, ac);
	abcd = subtract(abcd, bd);

	zero_pad(ac, abcd);
	string result = add(ac, abcd);
	result = add(result, bd);
	return remove_leading_zeros(result);

}


int main(int argc, char* argv[]){
	string a = "12";
	string b = "12";

	cout << add(a, b) << endl;
	cout << subtract(a,b) << endl;
	cout << multiplication(a,b) << endl;

	return 0;
}


