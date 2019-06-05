#pragma once

class MessageHandler;
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
  MessageHandler* message_handler;
};
