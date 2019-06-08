#pragma once

namespace Protocol {

struct Message;

}

namespace Client {

class SampleClient {
 public:
  SampleClient();
  ~SampleClient();

 public:
  void ConnectServer();
  void CloseClient();
  void SendPrintHelloWorld(bool flag);

 private:
  void SendMessage(Protocol::Message* msg);
  Protocol::Message* ReceiveMessage();

 private:
  int sock_fd;
};

}  // namespace Client
