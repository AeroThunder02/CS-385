/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Maciej Kowalczyk
 * Date        : 9/10/21
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my Honor that I have abided by the stevens honor system.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
    num_primes_ = count_num_primes();
}


//Displays the primes in a grid format with strict spacing and a line limit of 80 characters
void PrimesSieve::display_primes() const {
	cout << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
	const int max_prime_width = num_digits(max_prime_), primes_per_row = 80/(max_prime_width + 1);
	int primes_in_row = 0;
	int last_prime = max_prime_;

    if(num_primes_ < primes_per_row){

    	for(int i = 2; i <= limit_; i++){

    		if(is_prime_[i] == true){
    			cout << i;

    			if(i != last_prime){   //Loop to check if the current prime isnt the last one. This is to make sure no additional spaces or line skips are done after the final prime number
					if(i < max_prime_ && (primes_in_row + 1) % primes_per_row != 0){  //Check that reads 1 step ahead to see if it is the last prime of the row. If not, print a space
						cout << " ";
					}

					primes_in_row++;

					if(primes_in_row % primes_per_row == 0){
						cout << endl;
						primes_in_row = 0;
					}
    			}
    		}
    	}
    }

    else{
    	for(int i = 2; i <= limit_; i++){
    		if(is_prime_[i] == true){
    			cout << setw(max_prime_width) << i;
    			primes_in_row++;

    			if(i < last_prime){	//Another check to keep any freak accidents from occurring
					if(primes_in_row % primes_per_row == 0){
						cout << endl;
					}
					else{
					    			    cout << " ";
					    			}
    			}

    		}

    	}
    }
}



//Counts all the primes in up to the limit
int PrimesSieve::count_num_primes() const {
	int primes = 0;

    for(int i = 2; i <= limit_; i++){
    	if(is_prime_[i] == true){
    		primes++;
    	}
    }
	return primes;
}

//The actual sieve that searches for the primes. It starts by setting all the values to true. Then it takes the prime value, starting with 2, and sets all multiples of it to false, such that only prime numbers remain
void PrimesSieve::sieve() {
	is_prime_[0] = false;
	is_prime_[1] = false;

	for(int i = 2; i <= limit_; i++){
		is_prime_[i] = true;
	}

	for(int i = 2; i <= sqrt(limit_); i++){
		if(is_prime_[i] == true){
			for(int j = i*i; j <= limit_; j += i){
				is_prime_[j] = false;
			}
		}
	}

	for(int i = limit_; i >= 2; i--){
		if(is_prime_[i] == true){
			max_prime_ = i;
			break;
		}
	}



}

//Grabs the digit of the highest number. This is done to format the display correctly later on
int PrimesSieve::num_digits(int num) {
    int digits = 0;
    num = abs(num);

    if(num == 0){
    	return 1;
    }

    while (num != 0){
    	num /= 10;
    	digits++;
    }

    return digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve sieve(limit);
    cout << endl;
    sieve.display_primes();
    return 0;
}
