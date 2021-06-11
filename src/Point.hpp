#include "Matrix.hpp"

// a matrix that is a 3 long vector representing x,y,z coordinates
class Point : public Matrix<3>{
    public:
        Point(const double (&point)[3] = {0,0,0}) : Matrix(point){}
        Point(const Matrix &point) : Matrix(point){}

        inline double getX() {return matrix[0][0];}
        inline double getY() {return matrix[1][0];}
        inline double getZ() {return matrix[2][0];}

};