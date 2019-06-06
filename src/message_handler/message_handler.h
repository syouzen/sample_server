#pragma once

namespace Protocol {

struct Message;

}

namespace Handler {

class MessageHandler {
 public:
  MessageHandler();
  ~MessageHandler();

 public:
  bool HandleMessage(Protocol::Message* message);

 private:
  void HandlePrintHelloWorld(Protocol::Message* message);
};

}  // namespace Handler
