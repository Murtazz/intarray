#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string RESET = "\033[0m";

int main(int argc, char **argv) {
	if (argv[2]) { // incorrect arguments
		cout << "Incorrect number of arguments" << endl;
		return 0;
	} else if (!argv[1]) {
		cout << "Incorrect number of arguments" << endl;
                return 0;
	}
	string answer = argv[1];
	string guess;  // storing the user input guesses
	string b;     // stores the letters already gotten
	int numGuess = 0;
	int length = answer.length();  // length of the word
	int g;
	int countcorrect = 0;  // if == to length of word then correct
	while (true) {
		if (numGuess == 6) break; // break loop if numGuess == 6;
		cout << "Enter " << length << " length word as guess: ";  // ask for guess
		if (!(cin >> guess)) {
			if (cin.eof()) break; // EOF
		}
		while (guess.length() != answer.length()) {  // if guess length and answer length not equal then
			cout << "Incorrect guess size, please enter guess of length " << length << ": ";
			if (!(cin >> guess)) {  // keep asking for right sized word
                        	if (cin.eof()) break; // EOF
			}
		}
		string b = ""; 
		for (g = 0; g < length; ++g) { // collect all green words
			if (answer[g] == guess[g]) {
                                b += to_string(g);
			}
		}
		for (g = 0; g < length; ++g) {
			size_t letterInWord = answer.find(guess[g]); // if letter exists in answer
			if (letterInWord == string::npos) {  // if it does not
				cout << guess[g];
			} else if (answer[g] == guess[g]) {  // if it does in the right index
				cout << GREEN;
				cout << guess[g];
				cout << RESET;
				countcorrect += 1;
			} else if (answer[letterInWord] == guess[g]) {  // if it does but not in the right index
				if (b.find(to_string(letterInWord)) != string::npos) { // if that letter has 
										       //already been found
                                	cout << guess[g];
                        	} else {  // else that letter still exists and could be used
					cout << YELLOW;
					cout << guess[g];
					cout << RESET;
				}
				//letterInWord = answer.find(guess[g], letterInWord + 1);
			}
		}
		cout << '\n';
		if (countcorrect == length) {
			cout << "Congrats you found the word!" << endl;  // game has been won
			return 0;
		}
		countcorrect = 0; // if not won then reset correction count to 0 and restart loop
		++numGuess; // add one to numGuess
		
	}
	cout << "Out of guesses! The word was: " << answer << endl; // loop ends numGuess == 6
}
