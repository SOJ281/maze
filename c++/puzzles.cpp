#include <string>
using namespace std;
#include <iostream>
#include <cmath>

#include <vector>


void fibonacci(int num1, int num2, int itersLeft) {
    cout << num1 + num2 << endl;

    if (itersLeft > 0) {
        fibonacci(num2, num1 + num2, itersLeft-1);
    }
}

int palindromeChecker(string stringyVal) {
    for (int i = 0; i < stringyVal.size(); i++) {
        if (stringyVal[i] != stringyVal[stringyVal.size()-i-1]) {
            return 0;
        }
    }
    return 1;
}

void insertionSort(int array[], int size) {
    int found = 0;
    for (int i = 0; i < size-1; i++) {
        found = 0;
        for (int l = 0; l < size-1; l++) {
            if (array[l] > array[l+1]) {
                int temp = array[l];
                array[l] = array[l+1];
                array[l+1] = temp;
                found = 1;
            }
        }
        if (!found) {break;}
    }
}


void code(int a, int b) {
    int smallest = min(a, b);

    for (int i = 1; i < smallest; i++) {
        if (((b % i) == 0) && ((a % i) == 0)) {
            cout << i;
        }
    }
}

int binarySearch(int array[], int size, int searchItem) {
    int found = 0;
    int start = 0;
    int end = size-1;
    int midpoint = 304;

    while ((end+start)/2 != midpoint) {
        midpoint = (end+start)/2;

        if (array[midpoint] == searchItem) {
            return midpoint;
        } else if (searchItem < array[midpoint]) {
            end = midpoint;
        } else if (searchItem > array[midpoint]) {
            start = midpoint;
        }

    }
    return 0;

}


vector<int> primesFinder(int upperLimit) {

    vector<int> primes;
    primes.push_back(2);
    int prime = 1;

    for (int i = 3; i < upperLimit; i +=2) {
        prime = 1;
        for (int l = 0; l < primes.size(); l++) {
            //cout << primes[l] << ","<<i<<","<< (primes[l] % i) << endl;
            if ((i % primes[l]) == 0) {
                //cout << i;
                prime = 0;
                break;
            }
        }
        if (prime) {
            primes.push_back(i);
        }
    }

    return primes;
}




int main() {

    //fibonacci(0, 1, 14);

    //cout << palindromeChecker("HEHE") << endl;
    //cout << palindromeChecker("HEH") << endl;
    //cout << palindromeChecker("TARAT") << endl;
    //cout << palindromeChecker("TAROT") << endl;

    int array[40];
    cout << "SIZE" << sizeof(array) << endl;

    for (int i = 0; i < 40; i++) {
        array[i] = rand() % 1000;
        cout << array[i] << endl;
    }
    insertionSort(array, 40);

    for (int i = 0; i < 40; i++) {
        cout << array[i] << endl;
    }

    //cout << binarySearch(array, 40, 490) <<endl;

    vector<int> primes = primesFinder(100000);
    cout << "SIZE" << primes.size() << endl;
    primes.erase(primes.begin() + 2);
    std::vector<int> vec = {1, 2, 3, 4, 5};
    primes.pop_back();
    cout << "SIZE" << primes.size() << endl;

    
    return 1;
}