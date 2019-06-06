#pragma once

#include <stddef.h>

namespace Protocol {

int ReceiveMsg(int sender_fd, int* fds, size_t fds_size, char* buf, size_t buf_size);
int SendMsg(int receiver_fd, int* fds, size_t fds_size, const char* buf, size_t buf_size);

}  // namespace protocol
