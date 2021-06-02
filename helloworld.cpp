#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/*
g++ -o helloworld helloworld.cpp
./helloworld

or (using compile and run)

ctrl + 6
*/

int main() {
    // hello world
    cout << "Hello World! \n";
    cout << "I am learning C++" << endl;

    // variables
    int age = 20;
    cout << "I am " << age << " years old." << endl;
    
    // user input
    int x;
    cout << "Give a number:" << endl;
    cin >> x;
    cout << "Your number squared is: " << (x * x) << endl;

    // datatypes
    float f = 5.5;
    double d = 5.61354151;
    bool b = true;
    char c = 'A';
    string hello = "Hello!";
    cout << f << ", " << d << ", " << b << ", " << c << ", " << hello << endl;

    // basic ops
    int p = 10;
    int q = 10;
    p += 5;
    ++q;
    cout << p << ", " << q << endl;

    // strings
    string text = "Whether we wanted it or not, we've stepped into a war with the Cabal on Mars. "
                  "So let's get to taking out their command, one by one. Valus Ta'aurc. "
                  "From what I can gather he commands the Siege Dancers from an Imperial Land Tank outside of Rubicon.";
    cout << text.length() << ", " << text[0] << endl;

    // string inputs
    string name;
    cout << "What is your name?" << endl;
    cin >> name;
    cout << "Your name is : " << name << endl;

    // maths
    cout << max (5, 10) << ", " << min (5, 10) << ", " << sqrt(64) << ", " << round(2.6) << ", " << log(2) << endl;

    // booleans
    cout << (5 < 10) << ", " << (5 == 10) << ", " << (5 <= 10) << endl;

    // ifs
    int y = 65;
    if (y > 70) {
        cout << "1";
    } else if (y > 60) {
        cout << "2-1";
    } else if (y > 50) {
        cout << "2-2";
    } else if (y > 40) {
        cout << "3";
    } else {
        cout << "fail";
    }

    return 0;
}