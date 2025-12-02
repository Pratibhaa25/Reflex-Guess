#include <iostream>
#include <vector>
#include <cstdlib>   // rand, srand
#include <ctime>     // time()
#include <cmath>     // abs
#include <algorithm> // transform
#include <string>
using namespace std;

// Function to check if input means "yes"
bool isYes(const string& input) {
    string temp = input;
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    return temp == "y" || temp == "yes" || temp == "yeah" || temp == "haa"||temp=="huuu"||temp=="hmm";
}

// Function to check if input means "no"
bool isNo(const string& input) {
    string temp = input;
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    return temp == "n" || temp == "no" || temp == "nah" || temp == "nahi"||temp=="nope"||temp=="not at all";
}

// Function to choose difficulty
int chooseDifficulty() {
    string level;
    cout << "\nChoose difficulty level (Easy/Medium/Hard): ";
    cin >> level;

    transform(level.begin(), level.end(), level.begin(), ::tolower);

    if (level == "easy") return 50;
    else if (level == "medium") return 100;
    else if (level == "hard") return 200;
    else {
        cout << "Invalid level! Defaulting to Medium.\n";
        return 100;
    }
}

// Function to provide approximate difference feedback
string getApproxDiff(int diff) {
    if (diff <= 5) return "1-5";
    else if (diff <= 10) return "6–10";
    else if (diff <= 20) return "11–20";
    else return "more than 20";
}

int main() {
    cout << "🎯 Welcome to Guess-Piss-Pause 🎯\n\n";

    string playNow;
    cout << "Do you want to play the game? ";
    cin >> playNow;

    // Continue playing as long as user says yes
    while (isYes(playNow)) {
        int maxRange = chooseDifficulty();

        // Generate secret number
        srand(time(0));
        int secret = rand() % maxRange + 1;

        vector<int> history;
        int attempts = 0;
        int maxAttempts = 10;

        cout << "\nGuess a number between 1 and " << maxRange << ":\n\n";

        while (true) {
            int guess;

            if (!(cin >> guess)) {
                cout << "⚠️ Invalid input! Please enter a number.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            attempts++;
            history.push_back(guess);

            if (guess == secret) {
                cout << "🎉 Correct! You win!\n";
                break;
            }

            // Approximate difference feedback
            int diff = abs(guess - secret);
            string approxDiff = getApproxDiff(diff);

            // Feedback based on closeness
            if (diff <= 5) cout << "🔥 Super close!\n";
            else if (diff <= 10) cout << "🔥 Close!\n";
            else if (diff <= 20) cout << "🌡️ Warm\n";
            else cout << "❄️ Ice cold!\n";

            cout << "You are approximately " << approxDiff << " away from the secret number.\n\n";

            if (attempts >= maxAttempts) {
                cout << "💥 Maximum attempts reached!\n";
                cout << "The secret number was: " << secret << "\n";
                break;
            }

            cout << "Try again!\n\n";
        }

        // Summary
        cout << "\nYour Guess History: ";
        for (int num : history) cout << num << " ";

        cout << "\nWrong Guesses: ";
        int wrongCount = 0;
        for (int num : history) {
            if (num != secret) {
                cout << num << " ";
                wrongCount++;
            }
        }

        cout << "\nTotal Wrong Guesses: " << wrongCount;
        cout << "\nTotal Attempts: " << attempts;

        // Score
        int score = (maxAttempts - attempts + 1) * 10;
        if (score < 0) score = 0;
        cout << "\nYour Score: " << score;

        // Ask if they want to play again
        cout << "\n\nDo you want to play again? ";
        cin >> playNow;

        if (isNo(playNow)) {
            break; // exit the game politely
        }
    }

    cout << "\n👌 Okay! Will meet soon. Bye! 🌟\n";
    return 0;
}
