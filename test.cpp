#include <iostream>

using namespace std;

int main(){
    int numRows = 5;
    int numCols = 6;
    int userArray[numRows][numCols]; 
    int num = 5;
    cout << &num;

    for (int i = 0; i < numRows; ++i) { 
        for (int j = 0; j < numCols; ++j) { 
            cout << "Element [" << i << "][" << j << "]: "; 
            userArray[i][j] = i * j; 
        } 
    }

    for (int i = 0; i < numRows; ++i) { 
        cout << "memory: "<< &userArray[i]<<endl;
        for (int j = 0; j < numCols; ++j) { 
            cout << userArray[i][j] << " "; 
        } 
        cout << endl;
    }

    cout << &userArray[0];
}