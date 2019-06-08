cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(SERVER sample_server)
set(SERVER_SRC 
  server/main.cc
  server/sample_server.cc

  message_handler/message_handler.cc

  protocol/protocol_utils.cc

  service/message_service.cc
)
set(OUTPUT_DIR )

add_compile_options(-Wall -g)
add_executable(${SERVER} ${SERVER_SRC})


set(CLIENT sample_client)
set(CLIENT_SRC 
  client/main.cc
  client/sample_client.cc

  protocol/protocol_utils.cc
)
set(OUTPUT_DIR )

add_compile_options(-Wall -g)
add_executable(${CLIENT} ${CLIENT_SRC})
