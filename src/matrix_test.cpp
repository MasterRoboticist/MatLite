#include "Matrix.hpp"
#include <iostream>
#include <vector>

using namespace std;  

int main(){
    // make matrix
    Matrix<2,3> mat1({{1,2,3},{4,5,6}});
    //print matrix
    cout << mat1 << endl;
    //print transform of matrix
    cout << mat1.T() << endl;
};


