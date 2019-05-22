// Hints
// 1. How many variables do you need to keep track?
// 2. Two variables is all you need. Try with x and y.
// 3. Beware of empty rows. It could be the first few rows.
// 4. To write correct code, think about the invariant to maintain. What is it?
// 5. The invariant is x and y must always point to a valid point in the 2d vector. Should you maintain your invariant ahead of time or right when you need it?
// 6. Not sure? Think about how you would implement hasNext(). Which is more complex?
// 7. Common logic in two different places should be refactored into a common method.


#include <iostream>
#include <vector>

using namespace std;

class Vector2D {

    int j = 0;
    vector<vector<int>>::iterator i, iEnd, ibegin;

    public:
        Vector2D(vector<vector<int>>& vec2d) {
            i = vec2d.begin();
            ibegin = vec2d.begin();
            iEnd = vec2d.end();
        }

        void restartRowCount(){
            j = 0;
            while(i != ibegin){
                i--;
            }
        }

        void next() {
            if(hasNext()){
                cout << (*i)[j++] << " ";
            }else{
                cout << "Out of bound! restart the iteration. " << endl;
                restartRowCount();
                next();
            }
        }

        bool hasNext() {
            if(j == (*i).size()){
                j = 0;
                if(i != iEnd){
                    i++;
                }
            }
            if(i != iEnd){
                return true;
            }else{
                return false;
            }
        }

};




int main(){
    vector<vector< int>> twoDVector = { {1,2},
                                        {3},
                                        {4,5,6}
                                      };
    Vector2D vect(twoDVector);

    for (int i = 0; i < twoDVector.size(); ++i)
    {
        for (int j = 0; j < twoDVector[i].size(); ++j)
        {
            vect.next();
        }
    }cout << endl;

    for (int i = 0; i < twoDVector.size(); ++i)
    {
        for (int j = 0; j < twoDVector[i].size(); ++j)
        {
            vect.next();
        }
    }cout << endl;
}




