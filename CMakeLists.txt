cmake_minimum_required (VERSION 2.8.11)
project (CTRANSLATE2_DEMO)

#set(CMAKE_PREFIX_PATH "ctranslate2/lib/cmake/ctranslate2")
#find_package(ctranslate2)
#set(CMAKE_C_COMPILER "/usr/local/Cellar/llvm/5.0.1/bin/clang")
#set(CMAKE_CXX_COMPILER "/usr/local/Cellar/llvm/5.0.1/bin/clang++")
#set(OPENMP_LIBRARIES "/opt/homebrew/opt/llvm//lib/clang/17/lib")
#set(OPENMP_INCLUDES "/opt/homebrew/opt/llvm//lib/clang/17/include")

OPTION (USE_OpenMP "Use OpenMP to enamble <omp.h>" ON)


# Find OpenMP
if(APPLE AND USE_OpenMP)
  message(STATUS "set env var")
  set(ENV{CC} "/usr/local/opt/llvm/bin/clang")
  set(ENV{CXX} "/usr/local/opt/llvm/bin/clang++")
  set(ENV{LDFLAGS} "-L/opt/homebrew/opt/libomp/lib")
  set(ENV{CPPFLAGS} "-I/opt/homebrew/opt/libomp/include")
endif()

#if(USE_OpenMP)
#  find_package(OpenMP REQUIRED)
#endif(USE_OpenMP)

if (OPENMP_FOUND)
    include_directories("${OPENMP_INCLUDES}")
    link_directories("${OPENMP_LIBRARIES}")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    # set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif(OPENMP_FOUND)



add_subdirectory(sentencepiece)
include_directories(sentencepiece/src)

add_subdirectory(ctranslate2)
include_directories(ctranslate2/include)


set(CMAKE_CXX_STANDARD 17)

add_executable (main main.cpp)
target_link_libraries(main sentencepiece-static ctranslate2)

