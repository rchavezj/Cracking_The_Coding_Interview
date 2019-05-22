#include <vector>
#include <iostream>

using namespace std;


unsigned int fib(int n) {
    static vector<int> table; // our cache

    if (n <= 1) {
        return n;
    }
    else if (n >= table.size()) {
        table.resize(n+1);
    }

    if (table[n] == 0) {
        // only recalc if we don't have a value
        table[n] = fib(n-1) + fib(n-2);
    }
    return table[n];
}

int main (){
	cout << fib(4) << endl;
}