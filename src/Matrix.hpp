#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

template <int nrow, int ncol=1> class Matrix {
    protected:
        // the data in the matrix
        double matrix[nrow][ncol];

    public:
        Matrix(){
            double mat[nrow][ncol];
        }

        // take input in the form {{1,2,3},{4,5,6}} of arbitrary size
        Matrix(double (&&mat)[nrow][ncol]) : Matrix(mat){}

        Matrix(double (&mat)[nrow][ncol]){
            for(int row = 0; row < nrow; row++){
                for(int col = 0; col < ncol; col++){
                    matrix[row][col] = mat[row][col];
                }
            }
        }

        Matrix(const std::vector< std::vector<double> > mat){
            for(int row = 0; row < nrow; row++){
                for(int col = 0; col < ncol; col++){
                    matrix[row][col] = mat[row][col];
                }
            }
        }

        // returns the element at x, y in the matrix
        double& operator ()(int a, int b);

        // multiplies two matrices together and returns a new matrix of their product
        template<int otherncol>
            Matrix<nrow, otherncol> operator *(Matrix<ncol, otherncol>& mat2);
            //Matrix<nrow, otherncol> operator *(Matrix<nrow, ncol>& mat1, Matrix<ncol, otherncol>& mat2);

        // multiplies two matrices together and updates this matrix to be their product
        // other matrix must be a square matrix
        void operator *=(Matrix<ncol, ncol>& otherMat);

        void operator *=(double num);


        // adds two matrices together and returns a new matrix of their elementwise sum
        Matrix<nrow, ncol> operator +(Matrix<nrow, ncol>& mat2);

        // adds two matrices together and updates this matrix to be their elementwise sum
        void operator +=(Matrix<nrow, ncol>& otherMat);
        


        // friend std::ostream& operator <<(std::ostream& os, Matrix<nrow, ncol>& mat);

        // returns the transpose of the matrix
        Matrix<ncol, nrow> T();

    private:
        // multiplies the two matrices together and stores the result in the given return matrix
        template<int otherncol>
            static void matMult(Matrix<nrow, ncol>& mat1, Matrix<ncol, otherncol>& mat2, Matrix<nrow, otherncol>& returnMat);

        // adds two matrices together and returns a new matrix of their elementwise sum
        static void matAdd(Matrix<nrow, ncol>& mat1, Matrix<nrow, ncol>& mat2, Matrix<nrow, ncol>& returnMat);

};


// returns the element at x, y in the matrix
template <int nrow, int ncol>
double& Matrix<nrow, ncol>::operator ()(int a, int b){
    // check if a and b are in bounds
    if(0 <= a && a < nrow){
        if(0 <= b && b < ncol){
            return matrix[a][b];
        }
        else throw std::out_of_range("In Matrix[a,b] index 'b' out of bounds");
    }
    else throw std::out_of_range("In Matrix[a,b] index 'a' out of bounds");
}

// multiplies two matrices together and returns a new matrix of their product
template <int nrow, int ncol>
template <int otherncol>
    Matrix<nrow, otherncol> Matrix<nrow, ncol>::operator *(Matrix<ncol, otherncol>& mat2){
        Matrix<nrow, otherncol> newMat;
        Matrix<nrow, ncol>::matMult(*this, mat2, newMat);
        return newMat;
    }

// multiplies two matrices together and updates this matrix to be their product
// other matrix must be a square matrix
template <int nrow, int ncol>
void Matrix<nrow, ncol>::operator *=(Matrix<ncol, ncol>& otherMat){
    Matrix<nrow, ncol> thisMatCopy = *this;
    matMult(thisMatCopy, otherMat, *this);
}

template <int nrow, int ncol>
void Matrix<nrow, ncol>::operator *=(double num){
    double* start = &(*this)(0,0);
    for(double* element = start; element < start + ncol*nrow; element++)
        *element *= num;
}


// adds two matrices together and returns a new matrix of their elementwise sum
template <int nrow, int ncol>
Matrix<nrow, ncol> Matrix<nrow, ncol>::operator +(Matrix<nrow, ncol>& mat2){
    Matrix<nrow, ncol> returnMat;
    matAdd(*this, mat2, returnMat);
    return returnMat;
}

// adds two matrices together and updates this matrix to be their elementwise sum
template <int nrow, int ncol>
void Matrix<nrow, ncol>::operator +=(Matrix<nrow, ncol>& otherMat){
    Matrix<nrow, ncol> thisMatCopy = *this;
    matAdd(thisMatCopy, otherMat, *this);
}


// returns the transpose of the matrix
template <int nrow, int ncol>
Matrix<ncol, nrow> Matrix<nrow, ncol>::T(){
    Matrix<ncol, nrow> tmat;
    for(int row = 0; row < nrow; row++){
        for(int col = 0; col < ncol; col++){
            tmat(col, row) = (*this)(row, col);
        }
    }
    return tmat;
}

// multiplies the two matrices together and stores the result in the given return matrix
template <int nrow, int ncol>
template <int otherncol>
    void Matrix<nrow, ncol>::matMult(Matrix<nrow, ncol>& mat1, Matrix<ncol, otherncol>& mat2, Matrix<nrow, otherncol>& returnMat){
        for(int row = 0; row < nrow; row++){
            for(int col = 0; col < otherncol; col++){
                double dotProd = 0;
                for(int numVal = 0; numVal < ncol; numVal++){
                    dotProd += mat1(row, numVal) * mat2(numVal, col);
                }
                returnMat(row, col) = dotProd;
            }
        }
    }

template <int nrow, int ncol>
std::ostream& operator <<(std::ostream& os, Matrix<nrow, ncol>& mat){
    if(nrow == 1) os << "[";
    else os << "[[";
    
    for(int row = 0; row < nrow; row++){
        for(int col = 0; col < ncol; col++){
            os << mat(row, col);
            if (col < ncol-1) os << ", ";
        }
        if(row < nrow-1) os << "]\n[";
        else if (nrow == 1) os <<"]";
        else os << "]]\n";
    }
    return os;
}

template <int nrow, int ncol>
std::ostream& operator <<(std::ostream& os, Matrix<nrow, ncol>&& mat){
    Matrix<nrow, ncol> matlval = mat;
    os << matlval;
    return os;
}

// adds two matrices together and returns a new matrix of their elementwise sum
template <int nrow, int ncol>
void Matrix<nrow, ncol>::matAdd(Matrix<nrow, ncol>& mat1, Matrix<nrow, ncol>& mat2, Matrix<nrow, ncol>& returnMat){
    for(int row = 0; row < nrow; row++){
        for(int col = 0; col < ncol; col++){
            returnMat(row, col) = mat1(row, col) + mat2(row,col);
        }
    }
}