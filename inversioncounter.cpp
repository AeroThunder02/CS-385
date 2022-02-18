/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Maciej Kowalczyk
 * Version     : 1.0
 * Date        : 10/27/2021
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my Honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;
    for(int i = 0; i < length; i++){
    	for(int j = i + 1; j < length; j++){
    		if(array[i] > array[j]){
    			count++;
    		}
    	}
    }
    return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int* scratch = new int[length]; //we need another array to copy into when we do mergesort
    long inversions = mergesort(array, scratch, 0, length-1);
    delete[] scratch;
    return inversions;
}

//Adapted from Dr. B's psuedocode on canvas.
static long mergesort(int array[], int scratch[], int low, int high) {
    long inversion_count = 0;  //Mergesort will follow standard implementation, we just need to add to this counter
    if (low < high){
    	int mid = low + (high - low) / 2;
    	inversion_count += mergesort(array, scratch, low, mid); //must add to total count for each recursion
    	inversion_count += mergesort(array, scratch, mid+1, high);
    	int L = low;
    	int H = mid + 1;
    	for(int k = low; k <= high; k++){
    		if((L <= mid) && ((H > high) || (array[L] <= array[H]))){ //Here is the comparison of array[i] <= array[j]
    			scratch[k] = array[L];
    			L++;
    		}
    		else{ //Thus we count inversions here
    			scratch[k] = array[H];
    			H++;
    			inversion_count += mid - L + 1;
    		}
    	}
    	for(int k = low; k <= high; k++){
    		array[k] = scratch[k];
    	}

    }
    return inversion_count;
}


int main(int argc, char *argv[]) {
    if(argc > 2){
    	cerr << "Usage: ./inversioncounter [slow]" << endl;
    	return 1;
    }

    //Check if user picks correct option
    if(argc == 2){
    	string option = argv[1];
    	if(option != "slow"){
    		cerr << "Error: Unrecognized option '" << option << "'.";
    		return 1;
    	}
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if(values.empty()){
    	cerr << "Error: Sequence of integers not received.";
    	return 1;
    }

    //if user picks 'slow' option
    if(argc == 2){
    	cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size());
    }
    //otherwise, use fast
    else{
    	cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size());
    }
    return 0;
}
