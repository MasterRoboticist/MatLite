add_executable(Matrix_Test matrix_test.cpp)
add_library(matlite TransformationMatrix.cpp Matrix.hpp)
target_link_libraries(Matrix_Test matlite)