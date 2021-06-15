#pragma once
#include "Matrix.hpp"
#include "Point.hpp"

class TM : public Matrix<4,4>{
    private:
        //Rotation matrix and position matrix parts of the transformation matrix
        Matrix<3,3> rotMat;
        Point pos;

        // use the rotation matrix and position vector to create or update the 4x4 transformation matrix
        void updateMatrix();
    public:
        //constructor for rotation matrix and position as arrays
        TM(const double (&rotMat)[3][3] = {{1,0,0},{0,1,0},{0,0,1}}, 
            const double (&posMat)[3] = {0,0,0}) :
            rotMat(rotMat),
            pos(posMat){
                updateMatrix();
            }
        // constructor using Matrix objects
        TM(const Matrix<3,3> &rotMat, 
            const Matrix<3,1> &posMat) :
            rotMat(rotMat),
            pos(posMat){
                updateMatrix();
            }
        // constructor using Matrix objects with transposed vector input
        TM(const Matrix<3,3> rotMat, 
            const Matrix<1,3> posMat) :
            rotMat(rotMat),
            pos(posMat.T()){
                updateMatrix();
            }

        // find the inversee of the transformation matrix
        TM inv();
        // return the rotation matrix part of the transformation matrix
        Matrix<3,3> getRotMat();
        // return the position matrix part of the transformation matrix
        Point getPos();

        // set the rotation and position matrices using a Matrix or an array
        void setRotMat(Matrix<3,3> rotMat);
        void setRotMat(const double (&rotMat)[3][3]);
        void setPos(Matrix<3,1> pos);
        void setPos(const double (&pos)[3]);
};