#pragma once

namespace Protocol {

struct MessagePrintHelloWorld;

}

namespace Service {

class MessageService {
 public:
  static MessageService& GetInstance() {
    static MessageService instance_;
    return instance_;
  }

 public:
  void PrintHelloWorld(Protocol::MessagePrintHelloWorld* msg);

 private:
  MessageService();
  ~MessageService();
  MessageService(const MessageService& copy);
  MessageService& operator=(const MessageService&);
};

}  // namespace Service
