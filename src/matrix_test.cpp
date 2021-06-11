#include "Matrix.hpp"
#include "TransformationMatrix.hpp"
#include <iostream>
#include <vector>

using namespace std;  

//TODO: get Google Test to work and do these tests automatically
void tryAllTM(){
    // Test constructors
    TM tm;
    cout << tm << endl;

    TM tm2({{1,2,3},{4,5,6},{7,8,9}},{1,2,3});
    cout << tm2 << endl;

    // test inverse
    cout << tm2.inv() << endl;

    //test getters and setters
    tm.setPos({10,20,30});
    tm.setRotMat({{3,3,3},{3,3,3},{3,3,3}});
    cout << tm.getRotMat() << endl;
    cout << tm.getPos() << endl;
    cout << tm << endl;
}

//TODO: get Google Test to work and do these tests automatically
void tryAllMatrix(){
    // Test constructors
    Matrix<4,3> emptymat;
    cout << emptymat << endl;
    double arr[3][4];
    Matrix<3,4> emptyFromArr(arr);
    cout << emptyFromArr << endl;
    double vec[5];
    Matrix<5> emptyFromVec(vec);
    cout << emptyFromVec << endl;
    vector<double> vectorVec = {1,2,3};
    Matrix<3> vec2(vectorVec);
    cout << vec2 << endl;
    vector<vector<double>> vectorArr = {{1,2,3},{4,5,6}};
    Matrix<2,3> mat1(vectorArr);
    Matrix<2,3> mat2({{1,2,3},{4,5,6}});
    Matrix<3,3> sqrMat({{1,2,3},{4,5,6},{7,8,9}});

    // test retreiving and setting operator in matrix
    cout << mat1(0,0) << endl;
    mat1(0,0) = 10;
    cout << mat1(0,0) << endl;
    cout << vec2(0,0) << endl;
    vec2(0,0) = 10;
    cout << vec2(0,0) << endl;

    //Test + and += operators and associated functions
    cout << mat1+mat2 << endl;
    mat1+=mat2;
    cout << mat1 << endl;

    //Test * and *= operators and associated functions
    cout << mat1*mat2.T() << endl;
    mat1 *= sqrMat;
    cout << mat1 << endl;
    cout << mat1*5 << endl;
    mat1 *= 5;
    cout << mat1 << endl;

    //Test = operator
    mat1 = {{1,2,3},{4,5,10}};
    cout << mat1;

    // Test transpose
    cout << mat2 << mat2.T() << endl;
}

int main(){
    // tryAllMatrix();
    tryAllTM();
};


