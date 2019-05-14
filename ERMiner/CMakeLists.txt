cmake_minimum_required(VERSION 3.13)
project(ERMiner)

set(CMAKE_CXX_STANDARD 14)

add_executable(ERMiner Sequence.cpp SequenceDatabase.cpp Occurence.cpp SparseMatrix.cpp LeftRule.cpp LeftEquivalenceClass.cpp RightRule.cpp RightEquivalenceClass.cpp ExpandLeftStore.cpp AlgoERMiner.cpp main.cpp)
