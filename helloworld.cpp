#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

/*
g++ -o helloworld helloworld.cpp
./helloworld

or (using compile and run)

ctrl + 6
*/


// functions
void myWhile() {
    int count = 0;
    while (count < 10) {
        cout << count;
        ++count;
    }
    cout << endl;
}

void myDo() { 
    int count = 0;
    do {
        cout << count;
        ++count;
    } while (count < 10);
    cout << endl;
}

void myFor() {
    for (int i = 0; i < 10; i++) {
        cout << i;
    }
    cout << endl;
}

void myBreak() {
    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            break;
        }
        cout << i;
    }
    cout << endl;
}

void myContinue() {
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            continue;
        }
        cout << i;
    }
    cout << endl;
}

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
        cout << "1" << endl;
    } else if (y > 60) {
        cout << "2-1" << endl;
    } else if (y > 50) {
        cout << "2-2" << endl;
    } else if (y > 40) {
        cout << "3" << endl;
    } else {
        cout << "fail" << endl;
    }

    // loops
    myWhile();
    myDo();
    myFor();
    myBreak();
    myContinue();

    // arrays
    string days[] = {"mon", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
    cout << days[3] << endl;
    days[0] = "MON";

    for (string day : days) {
        if (day != days[sizeof(days)/sizeof(days[0]) - 1]) {
            cout << day << ", ";
        } else {
            cout << day << endl;
        }
    }

    // references and pointers
    string food = "Pizza";
    string &meal = food;
    string* ptr = &food;

    cout << food << ", " << meal << ", ";
    food = "Burger";
    cout << food << ", " << meal << ", ";
    meal = "Chips";
    cout << food << ", " << meal << endl;
    cout << &food << ", " << &meal << ", " << ptr << endl;

    // files
    ofstream MyWriteFile("test.txt");
    MyWriteFile << "Hello World!";
    MyWriteFile.close();

    string fileText;
    ifstream MyReadFile("test.txt");
    while (getline (MyReadFile, fileText)) {
        cout << fileText;
    }
    MyReadFile.close();

    return 0;
}