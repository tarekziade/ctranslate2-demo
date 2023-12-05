cmake_minimum_required (VERSION 2.8.11)
project (CTRANSLATE2_DEMO)

find_package(ctranslate2)
add_subdirectory(sentencepiece)
include_directories(sentencepiece/src)

set(CMAKE_CXX_STANDARD 17)

add_executable (main main.cpp)
target_link_libraries(main CTranslate2::ctranslate2 sentencepiece-static)
