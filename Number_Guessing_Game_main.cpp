#include <iostream>
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()

using namespace std;

int main() {
    srand(time(0));
    int secretNumber = (rand() % 100) + 1;
    int userGuess = 0;
    int attempts = 0;
    cout << "=======================================" << endl;
    cout << "Welcome to the Number Guessing Game!" << endl;
    cout << "I have chosen a number between 1 and 100." << endl;
    cout << "Can you guess what it is?" << endl;
    cout << "=======================================" << endl;
    while (userGuess != secretNumber) {
        cout << "\nEnter your guess: ";
        cin >> userGuess;
        attempts++;
        if (userGuess > secretNumber) {
            cout << "Too high! Try a lower number.";
        }
        else if (userGuess < secretNumber) {
            cout << "Too low! Try a higher number.";
        }
        else {
            cout << "\nCongratulations! You guessed it right!";
            cout << "\nTotal attempts: " << attempts << endl;
        }
    }

    return 0;
}