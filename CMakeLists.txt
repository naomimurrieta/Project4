cmake_minimum_required(VERSION 3.27)
project(Project4)

set(CMAKE_CXX_STANDARD 17)

add_executable(supersearch main.cpp
        AVLTree.h
        InHan.cpp
        InHan.h
        porter2_stemmer.cpp
        porter2_stemmer.h
        DocuPar.cpp
        DocuPar.h
        QueryEngine.cpp
        QueryEngine.h
        userIn.cpp
        userIn.h)
