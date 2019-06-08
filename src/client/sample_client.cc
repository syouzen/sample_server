#include "client/sample_client.h"
#include "protocol/protocol.h"
#include "protocol/protocol_utils.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

namespace Client {

static const char* SOCKET_PATH = "/tmp/sample_server.socket";

SampleClient::SampleClient() : sock_fd(-1) {
}

SampleClient::~SampleClient() {
}

void SampleClient::ConnectServer() {
  struct sockaddr_un client_addr;

  sock_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    printf("[Client] Can't open stream socket.\n");
  }

  memset(&client_addr, 0, sizeof(client_addr));
  client_addr = {.sun_family = AF_LOCAL};
  strcpy(client_addr.sun_path, SOCKET_PATH);

  if (connect(sock_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)) == -1) {
    printf("[Client] Failed to connect server.\n");
    return;
  }
  printf("[Client] Server connected.\n");
}

void SampleClient::SendPrintHelloWorld(bool flag) {
  Protocol::MessagePrintHelloWorld msg;

  msg.msg.type = Protocol::MESSAGE_PRINT_HELLO_WORLD;
  msg.msg.size = sizeof(Protocol::MessagePrintHelloWorld);
  msg.flag = flag;

  SendMessage((Protocol::Message*)&msg);
}

void SampleClient::SendMessage(Protocol::Message* msg) {
  if (Protocol::SendMsg(sock_fd, nullptr, 0, (void*)msg, msg->size) == -1) {
    printf("[Client] Failed to send message.\n");
  }
  printf("[Client] Send message.\n");
}

Protocol::Message* SampleClient::ReceiveMessage() {
}

void SampleClient::CloseClient() {
  if (sock_fd != -1) {
    close(sock_fd);
    sock_fd = -1;
    printf("[Client] Client closed.\n");
  }
}

}  // namespace Client
