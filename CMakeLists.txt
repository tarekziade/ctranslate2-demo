cmake_minimum_required (VERSION 2.8.11)
project (CTRANSLATE2_DEMO)

#set(CMAKE_PREFIX_PATH "ctranslate2/lib/cmake/ctranslate2")
#find_package(ctranslate2)

add_subdirectory(sentencepiece)
include_directories(sentencepiece/src)

add_subdirectory(ctranslate2)
include_directories(ctranslate2/include)


set(CMAKE_CXX_STANDARD 17)

add_executable (main main.cpp)
target_link_libraries(main sentencepiece-static ctranslate2)

