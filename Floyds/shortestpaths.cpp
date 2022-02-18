/*******************************************************************************
 * Name        : shortestpaths.cpp	
 * Author      : George Carvellas | Maciej Kowalczyk
 * Version     : 1.0
 * Date        : 12/1/2021
 * Description : Implementation of Floyd's algorithm for finding the shortest paths in a graph from one point to another.
 * Pledge      : "I pledge my Honor that I have abided by the Stevens Honor System."
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

vector<vector<long>> floyd(vector<vector<long>> *weight_matrix, vector<vector<long>> *intermediate_vertices, long n){
    vector<vector<long>> distance_matrix;
    copy(weight_matrix->begin(), weight_matrix->end(), back_inserter(distance_matrix));
        for (int k = 0; k < n; k++){
            for (int i = 0; i < n ; i ++){
                for (int j = 0; j < n; j++){
                    if(distance_matrix.at(i).at(k) + distance_matrix.at(k).at(j) < distance_matrix.at(i).at(j) && !(distance_matrix.at(i).at(k) == numeric_limits<long>::max() || distance_matrix.at(k).at(j) == numeric_limits<long>::max())){
                        distance_matrix.at(i).at(j) = distance_matrix.at(i).at(k) + distance_matrix.at(k).at(j);
                        intermediate_vertices->at(i).at(j) = k;
                    }
                }
            }
        }
    return distance_matrix;
}

long len(long n){
    if (n==0)
        return 0;
    return 1 + len(n / 10);
}

void display_table(vector<vector<long>>  *matrix, long num_vertices, const string &label,
                   const bool use_letters = false) {
    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long cell = matrix->at(i).at(j);
            if (cell < numeric_limits<long>::max() && cell > max_val) {
                max_val = matrix->at(i).at(j);
            }
        }
    }

    int max_cell_width = use_letters ? len(max_val) :
                         len(max(static_cast<long>(num_vertices), max_val));
    if (max_cell_width == 0)
        max_cell_width = 1;
    cout << ' ';
    for (int j = 0; j < num_vertices; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++) {
            cout << " " << setw(max_cell_width);
            if (matrix->at(i).at(j) == numeric_limits<long>::max()) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>(matrix->at(i).at(j) + 'A');
            } else {
                cout << matrix->at(i).at(j);
            }
        }
        cout << endl;
    }
    cout << endl;
}

void display_paths_helper(vector<vector<long>> *intermediate_vertices, long i, long j){
    if (intermediate_vertices->at(i).at(j) == numeric_limits<long>::max()){
        cout << " -> " << static_cast<char>(j + 'A');
        return;
    }
    display_paths_helper(intermediate_vertices, i, intermediate_vertices->at(i).at(j));
    display_paths_helper(intermediate_vertices, intermediate_vertices->at(i).at(j), j);
}


void display_paths(vector<vector<long>> *distance_matrix, vector<vector<long>> *intermediate_vertices, vector<vector<long>> *path_matrix, long num_vertices){
    for(int i = 0; i < num_vertices; i++){
        for(int j = 0; j < num_vertices; j++){
            cout  << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A') << ", ";

            //if i = j
            if(i == j){
                cout << "distance: 0, path: " << static_cast<char>(i + 'A');
            }

            //intermediete verticies
            else if (intermediate_vertices->at(i).at(j) != numeric_limits<long>::max()){
                cout << "distance: " << static_cast<long>(path_matrix->at(i).at(j)) << ", path: "
                     << static_cast<char>(i +'A');

                display_paths_helper(intermediate_vertices, i, j);
            }

            //no intermediete vertecies
            else if(path_matrix->at(i).at(j) != numeric_limits<long>::max()){
                cout << "distance: " << static_cast<long>(path_matrix->at(i).at(j)) << ", path: "
                     << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A');
            }

            //if j is unreachable from i (hence infinite distance)
            else {
                cout << "distance: infinity, path: none";
            }
            cout << endl;
        }
    }
}

int main(int argc, const char *argv[]) {
    long n;
    vector<vector<long>> *matrix;

    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line)) {
            //cout << line_number << ":\t" << line << endl;
            istringstream iss;
            if(line_number == 1){
                iss.str(line);
                if (!(iss >> n) || n < 1 || n > 26){
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
                    return 1;
                }
                matrix = new vector<vector<long>>(n,std::vector<long>(n, std::numeric_limits<long>::max()));
                for(int i=0; i<n; i++){
                    matrix->at(i).at(i) = 0;
                }
            }
            else{
                //separates string into vector with different parts
                if(line.at(line.size()-1) == '\r')
                    line.erase(line.size() - 1); //remove /r
                vector<string> tokens;
                stringstream check1(line);
                string intermediate;
                while(getline(check1, intermediate, ' '))
                {
                    tokens.push_back(intermediate);
                }
                if (tokens.size() != 3){
                    cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
                    return 1;
                }
                else if(tokens.at(0).size() != 1 || (tokens.at(0).at(0) < 'A' || tokens.at(0).at(0) > 'A' + (n-1))){
                    cerr << "Error: Starting vertex '" << tokens.at(0) << "' on line " << line_number << " is not among valid values A-" << char('A' + (n-1)) << "." << endl;
                    return 1;
                }

                else if(tokens.at(1).size() != 1 || (tokens.at(1).at(0) < 'A' || tokens.at(1).at(0) > 'A' + (n-1))){
                    cerr << "Error: Ending vertex '" << tokens.at(1) << "' on line " << line_number << " is not among valid values A-" << char('A' + (n-1)) << "." << endl;
                    return 1;
                }

                long temp;

                iss.str(tokens.at(2));
                if (!(iss >> temp) || temp <= 0){
                    cerr << "Error: Invalid edge weight '" << tokens.at(2) << "' on line " << line_number << "." << endl;
                    return 1;
                }

                long i = tokens.at(0).at(0) - 'A';
                long j = tokens.at(1).at(0) - 'A';
                matrix->at(i).at(j) = temp;
            }
            iss.clear();
            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    auto *intermediate_vertices = new vector<vector<long>>(n,std::vector<long>(n, std::numeric_limits<long>::max()));

    vector<vector<long>> result = floyd(matrix, intermediate_vertices, n);
    display_table(matrix, n, "Distance matrix:");
    display_table(&result, n, "Path lengths:");
    display_table(intermediate_vertices, n, "Intermediate vertices:", true);
    display_paths(matrix, intermediate_vertices, &result, n);
    delete intermediate_vertices;
    delete matrix;
    return 0;
}
