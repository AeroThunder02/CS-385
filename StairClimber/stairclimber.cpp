/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Maciej Kowalczyk
 * Date        : 10/2/21
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my Honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

//Returns a vector of vectors which contains ALL of the possible ways to climb the stairs
vector< vector<int> > get_ways(int num_stairs) {
    vector<vector<int>> ways;
    vector<vector<int>> remaining;

    if(num_stairs <= 0){
    	ways.push_back({});
    }
    else{
    	for(int i = 1; i < 4; i++){
    		if (num_stairs >= i){
    			remaining = get_ways(num_stairs - i);
    			for (auto &result : remaining){
    				result.insert(result.begin(), i);   //the .begin sticks it at the beginning of the list. basically prepend
    			}
    			ways.insert(ways.end(), remaining.begin(), remaining.end());  //ways += result
    		}
    	}
    }
    return ways;

}
//Creates a nice, uniform display for the ways to climb stairs
void display_ways(const vector< vector<int> > &ways) {
    int max_width = ways.size();
    int digits = 0;

    //loop that gets the size of the largest digit
    while (max_width != 0){
    	max_width /= 10;
    	digits++;
    }
    if (ways[0].size() == 1){
    	cout << ways.size() << " way to climb " << ways[0].size() << " stair." << endl;
    }
    else{
    	cout << ways.size() << " ways to climb " << ways[0].size() << " stairs." << endl;
    }


    for(unsigned int i = 0; i < ways.size(); i++){
    	cout << setw(digits) << i+1 << ". [";
    	unsigned int j = 0;
    	while(j < ways[i].size()-1){
    		cout << ways[i][j] << ", ";
    		j++;
    	}
    	cout << ways[i][j] << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
	int m;
	if(argc != 2){
		cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}

	istringstream iss(argv[1]);
	if(!(iss >> m) || atoi(argv[1]) < 1){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	display_ways(get_ways(atoi(argv[1])));
	return 0;
}
