#pragma once

namespace Protocol {

struct Message {
  int size;
  int type;
};

struct MessagePrintHelloWorld {
  Message msg;
  bool flag;
};

enum message_type {
  MESSAGE_PRINT_HELLO_WORLD,
};

const int MAX_MESSAGE_SIZE = sizeof(MessagePrintHelloWorld);

}  // namespace Protocol
