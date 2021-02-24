cmake_minimum_required(VERSION 3.0.0)
project(BlackJack VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(range_v3 INTERFACE IMPORTED)
set_target_properties(range_v3 PROPERTIES 
    INTERFACE_INCLUDE_DIRECTORIES C:/Users/edwar/Projects/BlackJack/range-v3/include)

add_executable(
    BlackJack 
    source/card.cpp
    source/dealer.cpp
    source/game.cpp 
    source/main.cpp
    source/person.cpp 
    )

target_link_libraries(BlackJack PUBLIC range_v3)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
