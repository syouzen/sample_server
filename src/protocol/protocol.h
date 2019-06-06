#pragma once

namespace Protocol {

struct Message {
  char* raws;
  int type;
};

struct MessagePrintHelloWorld {
  Message msg;
  bool flag;
};

enum message_type {
  MESSAGE_PRINT_HELLO_WORLD,
};

}  // namespace Protocol
