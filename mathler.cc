#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstring>
#include <numeric>
#include <map>
#include <cmath>
#include <cfloat>

using namespace std;

int guessesLeft = 6;

int callRand = 0;


vector<string> splitString(string inputEquation) {
    // Splits string into a vector of strings containing different components of the given equation, e.g: 15 + 5 would be split into: ["15", "+", "5"]

    vector<vector<string>> resultVects;
    vector<string> stringVect;
    vector<string> charVect;


    string num = "";
    for (auto letter : inputEquation) {
        string strLetter;
        strLetter = letter;
        charVect.push_back(strLetter);

        string letterString(1, letter);
        if (isdigit(letter)) {
            num += letterString;
        }
        else {
            stringVect.push_back(num);
            stringVect.push_back(letterString);
            num = "";
        }
    }
    stringVect.push_back(num);


    return stringVect;
}

void printVector(vector<string> incomingVector) {
    cout << "Printing out the vector: " << endl;

    for (auto i : incomingVector)
        cout << i << endl;
}


double calculate(double num1, string operation, double num2) {
    if (operation == "+") {
        return num1 + num2;
    }
    else if (operation == "-") {
        return num1 - num2;
    }
    else if (operation == "*") {
        return num1 * num2;
    }
    else {
        return num1 / num2;
    }
}


double solveEquation(vector<string> expression) {
    double num1 = DBL_MAX;      // Essentially, infinity
    unsigned start = 0;
    string sign = "+";
    int addOnToInt = 0;

    string currentOperation;

    if ((expression[1] == "+" || expression[1] == "-") && (expression[3] == "*" || expression[3] == "/")) {
        addOnToInt = stod(expression[0]);
        sign = expression[1];
        start = 2;
    }

    for (unsigned int i = start; i < expression.size(); i ++) {

        if (expression[i] == "+" || expression[i] == "-" || expression[i] == "*" | expression[i] == "/" ) {
            currentOperation = expression[i];
        }
        else {
            if (num1 == DBL_MAX) {
                num1 = stod(expression[i]);
            }
            else {
                num1 = calculate(num1, currentOperation, stod(expression[i]));
            }
        }

    }

    num1 = calculate(addOnToInt, sign, num1);

    return num1;
}

void checkDifferences(vector<string> rightAnswer, vector<string> guess) {
    // Convert vectors of strings to strings
    string answerString = accumulate(rightAnswer.begin(), rightAnswer.end(), string{});
    string guessString = accumulate(guess.begin(), guess.end(), string{});

    // Count how many of each character is found in the user's guess, and put it in a map (like dictionary)
    map<char, int> guessFrequencies;
    for (auto character : guessString) {
        if (guessFrequencies.find(character) == guessFrequencies.end()) {
            guessFrequencies.insert({character, 1});
        }
        else {
            int count = guessFrequencies[character];
            count++;
            guessFrequencies[character] = count;
        }
    }

    map<char, int> newGuessFrequencies;
    newGuessFrequencies = guessFrequencies;

    cout << endl << "Correct characters that are in the right positions: " << endl;

    for (int unsigned i = 0; i < answerString.size(); i ++) {
        if (guessFrequencies.count(answerString[i])) {                  // Ensure that the character in the correct string answer is found in the frequency list (i.e: it's also in the guess)
            if (guessFrequencies[answerString[i]] > 0) {                // If there are still more of that character to cross off
                int count = newGuessFrequencies[answerString[i]];
                count--;
                newGuessFrequencies[answerString[i]] = count;

                if (answerString[i] == guessString[i]) {
                    int count = guessFrequencies[answerString[i]];      // Only change guessFrequencies when characters match at exact positions, this way, we know that if there are any more
                    count--;                                            // characters that are found in both strings, but not at the same spot, we can trace it by comparing with
                    guessFrequencies[answerString[i]] = count;          // the frequency from guessFrequences

                    cout << answerString[i] << " at position " << i << endl;
                }
            }
        }
    }

    map<string, int>::iterator it;

    cout << endl << "Correct characters in the wrong positions: " << endl;
    
    for (const auto& elem : guessFrequencies) {

        // The correct characters in the wrong positions are those that have newGuessFrequency < guessFrequency
        if (newGuessFrequencies[elem.first] < guessFrequencies[elem.first]) {
            cout << elem.first << endl;
        }
    }

}

bool evaluateGuess(vector<string> rightAnswer, vector<string> userGuess) {
    if (rightAnswer == userGuess) {
        cout << "Guess is correct!" << endl << endl;
        return true;
    }
    else {
        // Check if user's solution evaluates to the target value
        if (solveEquation(userGuess) == solveEquation(rightAnswer)) {
            cout << "Solution incorrect, but does evaluate to correct answer" << endl << endl;
            checkDifferences(rightAnswer, userGuess);
            guessesLeft--;
        }
        else {
            cout << "Equation does not evaluate to right answer" << endl;
        }

        return false;
    }
}

string cleanString(string initialGuess) {
    string returnString = "";

    for (auto character : initialGuess) {       // Return string without spaces
        if (character != ' ') {
            returnString += character;
        }
    }

    return returnString;
}

bool checkGuessValid(string userGuess) {
    if (userGuess.size() == 6 && (isdigit(userGuess[0]) && isdigit(userGuess.back()))) {        // Guess must be 6 characters and first and last characters must be digits

        bool charIsOperator = false;

        for (auto character : userGuess) {
            if (isdigit(character)) {
                charIsOperator = false;
            }
            else if (character == '+' || character == '-' || character == '/' || character == '*') {
                if (charIsOperator == false) {
                    charIsOperator = true;
                }
                else {
                    cout << "Two operators cannot be consecutively written" << endl;
                    return false;
                }
            }
            else {
                cout << "Inputted characters must be operators and digits only" << endl;
                return false;
            }

        }
    }
    else {
        cout << "The equation must have 6 character components (not including spaces) !" << endl;
        return false;
    }

    return true;
}

string generateRand(int choice = 0) {
    srand((unsigned int)time(NULL) + callRand);
    callRand ++;

    if (choice == 0) {
        string op[4] = {"+", "-", "/", "*"};
        return op[rand() % 4];
    }
    else {
        if (choice == 1) {
            return to_string(rand() % 9 + 1);
        }
        else {
            return to_string(rand() % 90 + 10);
        }
    }
}


vector<string> generateQuestion() {
    vector<string> question;      // Creating the random target equation

    question.push_back(generateRand(2));        // Choose a 2 digit number
    question.push_back(generateRand());         // Choose an operator
    question.push_back(generateRand(1));        // Choose a 1 digit number
    question.push_back(generateRand());         // Choose an operator
    question.push_back(generateRand(1));        // Choose a 1 digit number


    return question;
}

void gameWelcome() {
    cout << "Welcome to Mathler!" << endl << endl;
    cout << "Goal: Try to find the hidden calculation in 6 guesses that will evaluate to a stated answer" << endl << endl;

    cout << string(20, '-') << "RULES" << string(20, '-') << endl << endl;

    cout << "----------Rules in regards to the guess format:" << endl;
    cout << "1. Your guess must be in the format of: A 2 digit number, operator, 1 digit number, operator, 1 digit number" << endl;
    cout << "Example: If you were given a target answer of 980, a valid guess would be 98 * 5 * 2" << endl << endl << endl;

    cout << "----------Rules in regards to counting:" << endl << endl;
    cout << "-------Character count:" << endl;
    cout << "1. Your guess must contain 6 characters -- no more, no less" << endl;
    cout << "2. What kinds of characters will count towards the count? Digits and operators (i.e: +, -, *, /, and not including =)." << endl;
    cout << "3. Spaces do not count towards the character count (i.e: you can include as many spaces as you like" << endl << endl;
    cout << "-------Guess count:" << endl;
    cout << "1. Repeated valid guesses also count towards the guess count" << endl << endl<< endl << endl << endl;

    cout << "Press [ENTER] to play" << endl;

    string play;
    getline(cin, play);                 // Get user line input (wait for enter key)
}

int main() {
    // Initial variable setup
    string userGuess;
    double targetAnswer;
    vector<string> targetEquation;      // Creating the random target equation (the answer expected from the user)

    // Display welcome text and game rules
    gameWelcome();

    // Create a valid random target equation
    bool questionGenerated = false;
    while (!questionGenerated) {
        targetEquation = generateQuestion();
        targetAnswer =  solveEquation(targetEquation);
        
        double intpart;
        if (modf(targetAnswer, &intpart) == 0.0) {      // Target equation must evaluate to an integer answer (game requirements)
            questionGenerated = true;
        }
    }

    // Allow user to keep guessing until they have guessed right answer or max guesses is reached
    bool endGame = false;
    while (!endGame && guessesLeft > 0) {
        bool guessValid = false;

        cout << endl << string(100, '-') << endl << endl;
        cout << "You have " << guessesLeft << " guesses left!" << endl;
        while (!guessValid) {
            cout << "Please provide a valid equation guess that evaluates to " << targetAnswer << endl << endl;

            getline(cin, userGuess);                            // Get user guess

            userGuess = cleanString(userGuess);                 // Get rid of spaces

            cout << "Your guess: " << userGuess << endl << endl;

            guessValid = checkGuessValid(userGuess);                         // Ensure that the guess is valid
        }

        vector<string> splittedStrings = splitString(userGuess);     // Splitting guess into a string vector

        endGame = evaluateGuess(targetEquation, splittedStrings);
    }

    return 0;
}
