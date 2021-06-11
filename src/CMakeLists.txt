add_executable(matrixTest matrix_test.cpp)
add_library(matlite TransformationMatrix.cpp Matrix.hpp)
target_link_libraries(matrixTest matlite)