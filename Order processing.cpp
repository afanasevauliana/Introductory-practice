#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

void PrintMenu();
void FixStreamState();
int GetCorrectValue();


int main() {
    setlocale(LC_ALL, "RU");

    int command{};

    do {
        PrintMenu();
        command = GetCorrectValue();
        switch (command) {
        case 1: cout << "one" << endl; break;
        case 2: cout << "two" << endl; break;
        case 0: cout << "Программа окончена. До свидания!" << endl; break;
        default: cout << "Недопустимая команда. Попробуйте еще раз." << endl;
        }

    } while (command);

    return 0;
}

void PrintMenu() {
    cout << "1-\n2-";
}

void FixStreamState() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int GetCorrectValue() {
    int n{};
    bool isNotOk{};

    do {
        isNotOk = false;
        if ((cin >> n).fail()) {
            FixStreamState();
            cout << "Неправильный ввод!\nВведите команду еще раз:\n";
            isNotOk = true;
        }
    } while (isNotOk);

    return n;
}