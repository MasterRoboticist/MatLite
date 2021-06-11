#include "TransformationMatrix.hpp"


TM TM::inv(){
    TM invtm(rotMat.T(), rotMat.T()*(pos*-1));
    return invtm;
}

Matrix<3,3> TM::getRotMat(){
    return rotMat;
}

Matrix<3,1> TM::getPos(){
    return pos;
}

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

void TM::updateMatrix(){
    for(int row = 0; row < 3; row++){
        for(int col = 0; col < 3; col++){
            matrix[row][col] = rotMat(row,col);
        }
    }
    for(int row = 0; row < 3; row++){
        matrix[row][3] = pos(row);
    }
    matrix[3][3] = 1;
}