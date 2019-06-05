#pragma once

struct Message;
class MessageHandler {
 public:
  MessageHandler();
  ~MessageHandler();

 public:
  bool HandleMessage(Message* message);

 private:
  void HandleDefaultMessage(Message* message);
};
