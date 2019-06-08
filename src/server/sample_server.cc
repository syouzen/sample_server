#include "server/sample_server.h"
#include "message_handler/message_handler.h"
#include "protocol/protocol.h"
#include "protocol/protocol_utils.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

namespace Server {

static const char* SOCKET_PATH = "/tmp/sample_server.socket";

SampleServer::SampleServer() : server_fd(-1), client_fd(-1) {
  message_handler = new Handler::MessageHandler;
}
SampleServer::~SampleServer() {
  delete message_handler;
}

void SampleServer::OpenServer() {
  struct sockaddr_un server_addr, client_addr;

  unlink(SOCKET_PATH);

  server_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
  if (server_fd == -1) {
    printf("[Server] Can't open stream socket.\n");
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr = {.sun_family = AF_LOCAL};
  strcpy(server_addr.sun_path, SOCKET_PATH);

  if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    printf("[Server] Failed to bind.\n");
  }

  if (listen(server_fd, 5) < 0) {
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
  Protocol::Message msg;
  if (Protocol::ReceiveMsg(client_fd, nullptr, 0, (void*)&msg, Protocol::MAX_MESSAGE_SIZE) == -1) {
    printf("[Server] Failed to receive message.\n");
    return;
  }

  if (!message_handler->HandleMessage(&msg)) {
    printf("[Server] Invaild receive message.\n");
  }
}

void SampleServer::CloseCurrentClient() {
  if (client_fd != -1) {
    close(client_fd);
    client_fd = -1;
    printf("[Server] Client closed.\n");
  }
}

}  // namespace Server
