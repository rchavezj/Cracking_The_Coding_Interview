#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;
 
void printPowerSet(char *set){

    /*set_size of power set of a set with set_size
      n is (2**n -1)*/
    unsigned int pow_set_size = pow(2, strlen(set));
    int counter, j;
 
    /*Run from counter 000..0 to 111..1*/
    for(counter = 0; counter < pow_set_size; counter++)
    {
      for(j = 0; j < strlen(set); j++)
       {
          /* Check if jth bit in the counter is set
             If set then pront jth element from set */
          // cout << "j: " << j << endl;
          // cout << "counter: "<< counter << endl;
          // cout << "(1<<j): " << (1<<j) << endl; //1 = 1, 10 = 2, 100 = 4
          // cout << "counter & (1<<j): " << (counter & (1<<j)) << endl;
          // cout << endl;
          if(counter & (1<<j))
           printf("%c", set[j]);
       }
       printf("\n");
    }
}
 
/*Driver program to test printPowerSet*/
int main()
{
    char set[] = {'a','b','c'};
    printPowerSet(set);
 
    getchar();
    return 0;
}