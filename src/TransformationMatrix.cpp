#include "TransformationMatrix.hpp"

// find the inversee of the transformation matrix
TM TM::inv(){
    TM invtm(rotMat.T(), rotMat.T()*(pos*-1));
    return invtm;
}

// return the rotation matrix part of the transformation matrix
Matrix<3,3> TM::getRotMat(){
    return rotMat;
}

// return the position matrix part of the transformation matrix
Point TM::getPos(){
    return pos;
}

 // set the rotation and position matrices using a Matrix or an array
void TM::setRotMat(Matrix<3,3> rotMat){
    this->rotMat = rotMat;
    updateMatrix();
}
void TM::setRotMat(const double (&rotMat)[3][3]){
    Matrix<3,3> mat(rotMat);
    setRotMat(mat);
}

void TM::setPos(Matrix<3,1> pos){
    this->pos = pos;
    updateMatrix();
}
void TM::setPos(const double (&pos)[3]){
    Matrix<3> mat(pos);
    setPos(mat);
}

// use the rotation matrix and position vector to create or update the 4x4 transformation matrix
void TM::updateMatrix(){
    // Update the rotation matrix
    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 3; col++){
            matrix[row][col] = rotMat(row,col);
        }
    }
    // update the position matrix
    for(int row = 0; row < 3; row++){
        matrix[row][3] = pos(row);
    }
    // set the corner to be 1
    matrix[3][3] = 1;

    // matrix defaults to all 0, so the scaling vector does not need to be set or changed
}