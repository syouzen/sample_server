#include "message_handler/message_handler.h"
#include "protocol/message.h"

MessageHandler::MessageHandler() {}
MessageHandler::~MessageHandler() {}
bool MessageHandler::HandleMessage(Message* message) {}
void MessageHandler::HandleDefaultMessage(Message* message) {}
