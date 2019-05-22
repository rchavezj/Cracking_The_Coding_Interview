#include <iostream>

using namespace std;

int recursiveMultiply(int num1, int num2){
	if (num1 == 0 || num2 == 0) {
	        return 0;
	}

	else if( num2 < 0 ) {
	    return - num1 + recursiveMultiply(num1, num2 + 1);
	}

	else {
	    return num1 + recursiveMultiply(num1, num2 - 1);
	}
}

int main (){
	cout << recursiveMultiply(-2, 3) << endl;
}