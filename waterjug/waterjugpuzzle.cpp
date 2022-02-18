/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Maciej Kowalczyk
 * Partner     : Jamie Rollins
 * Date        : October 14, 2021
 * Description : Using Breadth First Search Solve the Water Jug problem.
 * Pledge      : I pledge my Honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <tuple>
#include <queue>
#include <stdlib.h>
#include <algorithm>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { } // @suppress("Symbol is not resolved")
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

bool compare(int a, int b, int c, int gA, int gB, int gC){
    if(a == gA && b == gB && c == gC){
        return true;
    }
    return false;
}

void bfs(int a, int b, int c, int gA, int gB, int gC, int maxA, int maxB, int maxC){
    State *start = new State(a, b, c, "Initial state.");
    State *goal = new State(gA,gB,gC,"\0");
    queue<State*> Q; //queue of pointers to states
    vector<State*> answer;//the vector we'll eventually backtrack w/ the quickest way to the goal
    vector<State*> garbageCollector;
    Q.push(start);


    //2D Array
    bool **outer = new bool*[maxA+1]; //creates an array of an array of States of length: a+1
    //For every row make an array of size b+1 States
    for(int i = 0; i< maxA+1; i++){//for every element in outer
        outer[i] = new bool[maxB+1]; //fills every element of outer array w/ an array
        //Initialize new row
        fill(outer[i], outer[i]+(maxB+1), false);
    }
    

    //initial state = goal state
    bool check = compare(a, b, c, gA, gB, gC);
        if(check==true){ //placeholder
            cout << start->directions + " " + (start->to_string());

            //cleanup
            delete start;
            delete goal;
            //Delete each row of the 2D array
            for(int i = 0; i< maxA+1; i++){
                delete [] outer[i];
            }
            delete [] outer;
            return;//end the program 
        }

    //while queue is not empty
    while(!(Q.empty())){
        State *current = Q.front();
        int nA = current -> a;
        int nB = current -> b;
        int nC = current -> c;
        Q.pop(); //remove current from queue, DOESN'T delete current


        //check if current = goal
        if(compare(nA, nB ,nC, gA, gB, gC)){
            //print back tracked solutions
            while(current->parent != nullptr){
                answer.push_back(current);
                current = current->parent;
            }
            answer.push_back(current);
            reverse(answer.begin(),answer.end());
            for(size_t k = 0; k<answer.size();k++){
                cout << answer[k]->directions << " " << answer[k]->to_string() << endl;
            }


            delete goal;
            delete start;
            //Delete each row of the 2D array
            for(int i = 0; i< maxA+1; i++){
                delete [] outer[i];
            }
            delete [] outer;

            for(size_t l = 0; l < garbageCollector.size(); l++){
            	delete garbageCollector[l];
            }

            return;
        }

        //if current has been seen
        if(outer[nA][nB] == true){
        	continue;
        }


        outer[nA][nB] = true;

        //C to A
        if(nA < maxA && nC > 0){ //can anything be added to a
            int spaceLeft = maxA - nA;
            if(spaceLeft >= nC){
                spaceLeft = nC;
                nC = 0;
                nA += spaceLeft;
            }
            else{
                nC -= spaceLeft;
                nA += spaceLeft;
            }

            if(spaceLeft == 1){
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallon from C to A.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
            else{
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallons from C to A.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
        }

        nA = current -> a;
        nB = current -> b;
        nC = current -> c;
        //B to A
        if(nA < maxA && nB>0){
            int spaceLeft = maxA - nA;
            if(spaceLeft >= nB){
                spaceLeft = nB;
                nB = 0;
                nA += spaceLeft;
            }
            else{
                nB -= spaceLeft;
                nA += spaceLeft;
            }

            if(spaceLeft == 1){
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallon from B to A.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
            else{
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallons from B to A.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
            
        }

        nA = current -> a;
        nB = current -> b;
        nC = current -> c;
        //C to B
        if(nB < maxB && nC > 0){
            int spaceLeft = maxB - nB;
            if(spaceLeft >= nC){
                spaceLeft = nC;
                nC=0;
                nB += spaceLeft;
            }
            else{
                nC -= spaceLeft;
                nB += spaceLeft;
            }

            if(spaceLeft == 1){
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallon from C to B.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
            else{
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallons from C to B.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
            
        }

        nA = current -> a;
        nB = current -> b;
        nC = current -> c;
        //A to B
        if(nB < maxB && nA > 0){
            int spaceLeft = maxB - nB;
            if(spaceLeft >= nA){
                spaceLeft = nA;
                nA=0;
                nB += spaceLeft;
            }
            else{
                nA -= spaceLeft;
                nB += spaceLeft;
            }

            if(spaceLeft == 1){
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallon from A to B.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
            else{
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallons from A to B.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
            
        }

        nA = current -> a;
        nB = current -> b;
        nC = current -> c;
        //B to C
        if(nC < maxC && nB >0){
            int spaceLeft = maxC - nC;
            if(spaceLeft >= nB){
                spaceLeft = nB;
                nB=0;
                nC += spaceLeft;
            }
            else{
                nB -= spaceLeft;
                nA += spaceLeft;
            }

            if(spaceLeft == 1){
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallon from B to C.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
            else{
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallons from B to C.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
            
        }

        nA = current -> a;
        nB = current -> b;
        nC = current -> c;
        //A to C
        if(nC < maxC && nA > 0){
            int spaceLeft = maxC - nC;
            if(spaceLeft >= nA){
                spaceLeft = nA;
                nA=0;
                nC += spaceLeft;
            }
            else{
                nA -= spaceLeft;
                nC += spaceLeft;
            }

            if(spaceLeft == 1){
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallon from A to C.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
            else{
                State *nState = new State(nA,nB,nC, "Pour "+to_string(spaceLeft)+" gallons from A to C.");
                nState -> parent = current;
                Q.push(nState);
                State *garbage = nState;
                garbageCollector.push_back(garbage);
            }
            
        }

    }

    cout << "No solution.";



    delete start;
    delete goal;
    //Delete each row of the 2D array
    for(int i = 0; i< maxA+1; i++){
        delete [] outer[i];
    }
    delete [] outer;

    for(size_t l = 0; l < garbageCollector.size(); l++){
    	delete garbageCollector[l];
    }

    return;
}

int main(int argc, char * const argv[]){
    int x;//just an int to make sure the inputs are ints
    int jugA, jugB, jugC, goalA, goalB, goalC, goalSum;
    istringstream iss;

    //given too many or too few arguments
    if(argc != 7){
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
        return 1;
    }

    for(int i = 1; i<=3; i++){
        iss.str(argv[i]);
        if((!(iss >> x)) || (x <= 0)){
            if(i==1){
                cerr << "Error: Invalid capacity '"<< argv[i] << "' for jug A.";
                return 1;
            }
            else if(i==2){
                cerr << "Error: Invalid capacity '"<< argv[i] << "' for jug B.";
                return 1;
            }
            else if(i==3){
                cerr << "Error: Invalid capacity '"<< argv[i] << "' for jug C.";
                return 1;
            }
        }
        iss.clear();
    }
    for(int i = 4; i <= 6; i++){
        iss.str(argv[i]);
        if((!(iss >> x)) || (x<0)){
            if(i==4){
                cerr << "Error: Invalid goal '"<< argv[i] << "' for jug A.";
                return 1;
            }
            else if(i==5){
                cerr << "Error: Invalid goal '"<< argv[i] << "' for jug B.";
                return 1;
            }
            else if(i==6){
                cerr << "Error: Invalid goal '"<< argv[i] << "' for jug C.";
                return 1;
            }
        }
        iss.clear();
    }

    jugA = atoi(argv[1]);
    jugB = atoi(argv[2]);
    jugC = atoi(argv[3]);
    goalA = atoi(argv[4]);
    goalB = atoi(argv[5]);
    goalC = atoi(argv[6]);
    goalSum = goalA + goalB + goalC;

    if(jugA < goalA){
        cerr << "Error: Goal cannot exceed capacity of jug A.";
        return 1;
    }
    if(jugB < goalB){
        cerr << "Error: Goal cannot exceed capacity of jug B.";
        return 1;
    }
    if(jugC < goalC){
        cerr << "Error: Goal cannot exceed capacity of jug C.";
        return 1;
    }
    if(goalSum != jugC){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
        return 1;
    }
    bfs(0,0,jugC,goalA,goalB,goalC, jugA,jugB,jugC);
    return 0;
}  
