#include "Matrix.hpp"

class TM : public Matrix<4,4>{
    private:
        Matrix<3,3> rotMat;
        Matrix<3,1> pos;
        void updateMatrix();
    public:
        TM(const double (&rotMat)[3][3] = {{1,0,0},{0,1,0},{0,0,1}}, 
            const double (&posMat)[3] = {0,0,0}) :
            rotMat(rotMat),
            pos(posMat){
                updateMatrix();
            }
        TM(const Matrix<3,3> &rotMat, 
            const Matrix<3,1> &posMat) :
            rotMat(rotMat),
            pos(posMat){
                updateMatrix();
            }
        TM(const Matrix<3,3> rotMat, 
            const Matrix<1,3> posMat) :
            rotMat(rotMat),
            pos(posMat.T()){
                updateMatrix();
            }

        TM inv();
        Matrix<3,3> getRotMat();
        Matrix<3,1> getPos();

        void setRotMat(Matrix<3,3> rotMat);
        void setRotMat(const double (&rotMat)[3][3]);
        void setPos(Matrix<3,1> pos);
        void setPos(const double (&pos)[3]);
};