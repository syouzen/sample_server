#include "message_handler/message_handler.h"
#include "protocol/protocol.h"
#include "service/message_service.h"

namespace Handler {

MessageHandler::MessageHandler() {}
MessageHandler::~MessageHandler() {}
bool MessageHandler::HandleMessage(Protocol::Message* message) {
  switch (message->type) {
    case Protocol::MESSAGE_PRINT_HELLO_WORLD:
      HandlePrintHelloWorld(message);
      return true;
  }

  return false;
}

void MessageHandler::HandlePrintHelloWorld(Protocol::Message* message) {
  Service::MessageService& message_service = Service::MessageService::GetInstance();
  Protocol::MessagePrintHelloWorld* msg = reinterpret_cast<Protocol::MessagePrintHelloWorld*>(message);

  message_service.PrintHelloWorld(msg);
}

}  // namespace Handler
