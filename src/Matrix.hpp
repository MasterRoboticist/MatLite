#pragma once
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

        // take input in the form {{1,2,3},{4,5,6}} or a matrix of arbitrary size
        Matrix(const double (&mat)[nrow][ncol]){
            for(int row = 0; row < nrow; row++){
                for(int col = 0; col < ncol; col++){
                    matrix[row][col] = mat[row][col];
                }
            }
        }

        // Matrix(const Matrix<nrow, ncol> &mat){
        //     for(int row = 0; row < nrow; row++){
        //         for(int col = 0; col < ncol; col++){
        //             matrix[row][col] = mat(row, col);
        //         }
        //     }
        // }

        Matrix(const double (&mat)[nrow]){
            for(int row = 0; row < nrow; row++){
                matrix[row][0] = mat[row];
            }
        }

        Matrix(const std::vector< std::vector<double> > mat){
            for(int row = 0; row < nrow; row++){
                for(int col = 0; col < ncol; col++){
                    matrix[row][col] = mat[row][col];
                }
            }
        }

        Matrix(const std::vector<double> mat){
            for(int row = 0; row < nrow; row++){
                matrix[row][0] = mat[row];
            }
        }

        void operator =(const double (&arr)[nrow][ncol]);

        // returns the element at x, y in the matrix
        double& operator ()(const int &a, const int &b);
        double get(const int &a, const int &b) const;

        // returns the element at x in a vector
        // a matrix is a vector if nrow or ncol is 1
        double& operator ()(const int &a);

        // multiplies two matrices together and returns a new matrix of their product
        template<int otherncol>
            Matrix<nrow, otherncol> operator *(const Matrix<ncol, otherncol> &mat2) const;

        // multiplies a matrix by a value and returns a new matrix
        Matrix<nrow, ncol> operator *(const double &num) const;

        // multiplies two matrices together and updates this matrix to be their product
        // other matrix must be a square matrix
        void operator *=(const Matrix<ncol, ncol>& otherMat);

        void operator *=(double num);


        // adds two matrices together and returns a new matrix of their elementwise sum
        Matrix<nrow, ncol> operator +(const Matrix<nrow, ncol>& mat2) const;

        // adds two matrices together and updates this matrix to be their elementwise sum
        void operator +=(const Matrix<nrow, ncol>& otherMat);
        
        // returns the transpose of the matrix
        Matrix<ncol, nrow> T() const;

    private:
        // multiplies the two matrices together and stores the result in the given return matrix
        template<int otherncol>
            static void matMult(const Matrix<nrow, ncol>& mat1, const Matrix<ncol, otherncol>& mat2, Matrix<nrow, otherncol>& returnMat);

        // adds two matrices together and returns a new matrix of their elementwise sum
        static void matAdd(const Matrix<nrow, ncol>& mat1, const Matrix<nrow, ncol>& mat2, Matrix<nrow, ncol>& returnMat);
};

// allows setting of matrix contents using =
template <int nrow, int ncol>
void Matrix<nrow, ncol>::operator =(const double (&arr)[nrow][ncol]){
    for(int row = 0; row < nrow; row++){
        for(int col = 0; col < ncol; col++){
            matrix[row][col] = arr[row][col];
        }
    }
}

// returns the element at x, y in the matrix
template <int nrow, int ncol>
double& Matrix<nrow, ncol>::operator ()(const int &a, const int &b){
    // check if a and b are in bounds
    if(0 <= a && a < nrow){
        if(0 <= b && b < ncol){
            return matrix[a][b];
        }
        else throw std::out_of_range("In Matrix(a,b) index 'b' out of bounds");
    }
    else throw std::out_of_range("In Matrix(a,b) index 'a' out of bounds");
}

template <int nrow, int ncol>
double Matrix<nrow, ncol>::get(const int &a, const int &b) const{
    // check if a and b are in bounds
    if(0 <= a && a < nrow){
        if(0 <= b && b < ncol){
            return matrix[a][b];
        }
        else throw std::out_of_range("In Matrix(a,b) index 'b' out of bounds");
    }
    else throw std::out_of_range("In Matrix(a,b) index 'a' out of bounds");
}

// returns the element at x in a vector
// a matrix is a vector if nrow or ncol is 1
template <int nrow, int ncol>
double& Matrix<nrow, ncol>::operator ()(const int &a){
    // check if a is in bounds
    if(ncol == 1){
        if(a > nrow){
            throw std::out_of_range("In Matrix(a), vector index out of bounds");
        }
        return matrix[a][0];
    }
    if(nrow == 1){
        if(a > ncol){
            throw std::out_of_range("In Matrix(a), vector index out of bounds");
        }
        return matrix[0][a];
    }
    else throw std::out_of_range("Matrix is not a vector, but was indexed like one. Did you mean Matrix(a,b)?");
}

// multiplies two matrices together and returns a new matrix of their product
template <int nrow, int ncol>
template <int otherncol>
    Matrix<nrow, otherncol> Matrix<nrow, ncol>::operator *(const Matrix<ncol, otherncol> &mat2) const{
        Matrix<nrow, otherncol> newMat;
        Matrix<nrow, ncol>::matMult(*this, mat2, newMat);
        return newMat;
    }

// multiplies a matrix by a value and returns a new matrix
template <int nrow, int ncol>
Matrix<nrow, ncol> Matrix<nrow, ncol>::operator *(const double &num) const{
    Matrix<nrow, ncol> newMat = *this;
    double* start = &newMat(0,0);
    for(double* element = start; element < start + ncol*nrow; element++)
        *element *= num;
    return newMat;
}

// multiplies two matrices together and updates this matrix to be their product
// other matrix must be a square matrix
template <int nrow, int ncol>
void Matrix<nrow, ncol>::operator *=(const Matrix<ncol, ncol>& otherMat){
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
Matrix<nrow, ncol> Matrix<nrow, ncol>::operator +(const Matrix<nrow, ncol>& mat2) const{
    Matrix<nrow, ncol> returnMat;
    matAdd(*this, mat2, returnMat);
    return returnMat;
}

// adds two matrices together and updates this matrix to be their elementwise sum
template <int nrow, int ncol>
void Matrix<nrow, ncol>::operator +=(const Matrix<nrow, ncol>& otherMat){
    Matrix<nrow, ncol> thisMatCopy = *this;
    matAdd(thisMatCopy, otherMat, *this);
}


// returns the transpose of the matrix
template <int nrow, int ncol>
Matrix<ncol, nrow> Matrix<nrow, ncol>::T() const{
    Matrix<ncol, nrow> tmat;
    for(int row = 0; row < nrow; row++){
        for(int col = 0; col < ncol; col++){
            tmat(col, row) = this->get(row, col);
        }
    }
    return tmat;
}

// multiplies the two matrices together and stores the result in the given return matrix
template <int nrow, int ncol>
template <int otherncol>
    void Matrix<nrow, ncol>::matMult(const Matrix<nrow, ncol>& mat1, const Matrix<ncol, otherncol>& mat2, Matrix<nrow, otherncol>& returnMat){
        for(int row = 0; row < nrow; row++){
            for(int col = 0; col < otherncol; col++){
                double dotProd = 0;
                for(int numVal = 0; numVal < ncol; numVal++){
                    dotProd += mat1.get(row, numVal) * mat2.get(numVal, col);
                }
                returnMat(row, col) = dotProd;
            }
        }
    }

// adds two matrices together and returns a new matrix of their elementwise sum
template <int nrow, int ncol>
void Matrix<nrow, ncol>::matAdd(const Matrix<nrow, ncol>& mat1, const Matrix<nrow, ncol>& mat2, Matrix<nrow, ncol>& returnMat){
    for(int row = 0; row < nrow; row++){
        for(int col = 0; col < ncol; col++){
            returnMat(row, col) = mat1.get(row, col) + mat2.get(row,col);
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



template<int dim>
using Vector = Matrix<dim>;