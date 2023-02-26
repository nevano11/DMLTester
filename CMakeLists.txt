cmake_minimum_required(VERSION 3.24)
project(DMLTester)

set(CMAKE_CXX_STANDARD 17)

add_executable(DMLTester main.cpp MathModel/Components/EstimateVector.cpp MathModel/Components/EstimateVector.h MathModel/Components/Criteria.cpp MathModel/Components/Criteria.h MathModel/Components/CriteriaRelation.cpp MathModel/Components/CriteriaRelation.h MathModel/MathModel.cpp MathModel/MathModel.h DecisionMakingMethod/DecisionMakingMethod.cpp DecisionMakingMethod/DecisionMakingMethod.h)
