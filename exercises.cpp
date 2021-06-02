#include <iostream>
#include <cctype>

using namespace std;

void fib();
void fib(int num1, int num2);
void fizzbuzz();
void isPali(string text);
string toLower(string text);
string reverse(string text);

int main() {
    fib();
    fizzbuzz();
    isPali("racecar");
    return 0;
}

// fibonacci sequence
void fib() {
    fib(0, 1);
}

void fib(int num1, int num2) {
    if (num2 < 1000000) {
        cout << num1 << ", ";
        fib(num2, (num1 + num2));
    } else {
        cout << num1 << ", " << num2 << endl;
    }
}

// fizzbuzz
void fizzbuzz() {
    for (int i = 1; i < 30; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            cout << "FizzBuzz, ";    
        } else if (i % 3 == 0) {
            cout << "Fizz, ";
        } else if (i % 5 == 0) {
            cout << "Buzz, ";
        } else {
            cout << i << ", ";
        }
    }
    cout << "Buzz" << endl;
}

// palindrome check
void isPali(string text) {
    string lowerText = toLower(text);
    int length = lowerText.length();

    if (length % 2 == 0) {
        if (lowerText.substr(0, length / 2) == reverse(lowerText.substr(length / 2))) {
            cout << true;
        } else {
            cout << false;
        }
    } else {
        if (lowerText.substr(0, length / 2) == reverse(lowerText.substr((length / 2) + 1))) {
            cout << true;
        } else {
            cout << false;
        }
    }
}

// converts a string to lowercase
string toLower(string text) {
    string lower;
    for (char c : text) {
        lower += tolower(c);
    }
    return lower;
}

// reverses a string
string reverse(string text) {
    string reverseText;
    for (int i = text.length() - 1; i >= 0; i--) {
        reverseText += text[i];
    }
    return reverseText;
}