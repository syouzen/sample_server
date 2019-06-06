#include "service/message_service.h"
#include "protocol/protocol.h"

#include <cstdio>

namespace Service {

MessageService::MessageService() {}
MessageService::~MessageService() {}

void MessageService::PrintHelloWorld(Protocol::MessagePrintHelloWorld* msg) {
  if (msg->flag) {
    printf("[Message Service] Print Hello World ! Flag is True.\n");
  } else {
    printf("[Message Service] Print Hello World ! Flag is False.\n");
  }
}

}  // namespace Service
