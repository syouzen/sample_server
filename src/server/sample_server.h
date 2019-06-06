#pragma once

namespace Handler {

class MessageHandler;

}

namespace Server {

class SampleServer {
 public:
  SampleServer();
  ~SampleServer();

 public:
  void OpenServer();

  void ReceiveMessage();

  void CloseCurrentClient();

 private:
  int server_fd;
  int client_fd;
  Handler::MessageHandler* message_handler;
};

}  // namespace server
