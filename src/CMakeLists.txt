cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(TARGET sample_server)
set(SOURCES 
  server/main.cc
  server/sample_server.cc  
)
set(OUTPUT_DIR )

add_compile_options(-Wall)
add_executable(${TARGET} ${SOURCES})
