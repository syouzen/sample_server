#include "server/sample_server.h"
#include "message_handler/message_handler.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

static const char* SOCKET_PATH = "/tmp/sample_server.socket";
const int BUFFER_SIZE = 128;

SampleServer::SampleServer() : server_fd(-1), client_fd(-1) {
  message_handler = new MessageHandler;
}
SampleServer::~SampleServer() {
  delete message_handler;
}

void SampleServer::OpenServer() {
  bool res;
  struct sockaddr_un server_addr, client_addr;

  server_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
  if (server_fd == -1) {
    printf("[Server] Can't open stream socket.\n");
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr = {.sun_family = AF_LOCAL};
  strcpy(server_addr.sun_path, SOCKET_PATH);

  res = bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (res == -1) {
    printf("[Server] Failed to bind.\n");
  }

  res = listen(server_fd, 5);
  if (res == -1) {
    printf("[Server] Failed to listen.\n");
  }

  printf("[Server] Wait connection.\n");
  socklen_t client_addr_len = sizeof(client_addr);
  memset(&client_addr, 0, sizeof(client_addr));
  client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);

  if (client_fd == -1) {
    printf("[Server] Accept failed.\n");
  } else {
    printf("[Server] Client connected.\n");
  }
}

void SampleServer::ReceiveMessage() {
  int msg_size;
  int buffer[BUFFER_SIZE];

  msg_size = read(client_fd, buffer, 1024);
  write(client_fd, buffer, msg_size);
}

void SampleServer::CloseCurrentClient() {
  if (client_fd != -1) {
    close(client_fd);
    client_fd = -1;
    printf("[Server] Client closed.\n");
  }
}
