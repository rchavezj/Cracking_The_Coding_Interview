#include <iostream>
#include <vector>

using namespace std;

unsigned int fib(int n) 
{
    if (n <= 1)
        return n;

    vector<int> table(n + 1);

    table[0] = table[1] = 1;

    for (int i = 2; i <= n; ++i) {
        table[i] = table[i-1] + table[i-2];
    }    
    
    return table.back();
}


int main (){
	cout << fib(48000000) << endl;
}