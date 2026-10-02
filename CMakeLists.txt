cmake_minimum_required (VERSION 3.20)
project (fill_minimization LANGUAGES CXX)
add_executable (fillmin cpp/main.cpp cpp/graph.cpp cpp/ordering.cpp cpp/matrix_market.cpp)
target_compile_features(fillmin PRIVATE cxx_std_20)