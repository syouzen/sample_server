#include "protocol/protocol_utils.h"

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

namespace Protocol {

const int MAX_FD_COUNT = 16;

typedef union ControlMessageFD {
  struct cmsghdr cmsg;
  char data[CMSG_SPACE(sizeof(int) * MAX_FD_COUNT)];
} ControlMessageFD;

int ReceiveMsg(int sender_fd, int* fds, size_t fds_size, void* buf, size_t buf_size) {
  struct iovec vec;
  struct msghdr msghdr;
  ControlMessageFD cmsg;

  vec.iov_base = buf;
  vec.iov_len = buf_size;

  msghdr.msg_name = NULL;
  msghdr.msg_namelen = 0;
  msghdr.msg_iov = &vec;
  msghdr.msg_iovlen = 1;

  msghdr.msg_control = &cmsg;
  msghdr.msg_controllen = sizeof(cmsg.cmsg) + fds_size;
  msghdr.msg_flags = 0;

  if (recvmsg(sender_fd, &msghdr, 0) == -1) {
    printf("[Protocol] Failed to attach client.\n");
    return -1;
  }

  if (fds) {
    const struct cmsghdr* ctrl = (CMSG_FIRSTHDR(&msghdr));
    if (ctrl == NULL) {
      printf("[Protocol] No control message header.\n");
      return -1;
    }

    if (ctrl->cmsg_level != SOL_SOCKET || ctrl->cmsg_type != SCM_RIGHTS) {
      printf("[Protocol] Invalid control message.\n");
      return -1;
    }

    memcpy(fds, CMSG_DATA(ctrl), fds_size);
  }

  return 0;
}

int SendMsg(int receiver_fd, int* fds, size_t fds_size, void* buf, size_t buf_size) {
  struct iovec vec;
  struct msghdr msghdr;
  ControlMessageFD cmsg;

  vec.iov_base = buf;
  vec.iov_len = buf_size;

  msghdr.msg_name = NULL;
  msghdr.msg_namelen = 0;
  msghdr.msg_iov = &vec;
  msghdr.msg_iovlen = 1;

  msghdr.msg_control = &cmsg;
  msghdr.msg_controllen = sizeof(cmsg.cmsg) + fds_size;
  msghdr.msg_flags = 0;

  struct cmsghdr* ctrl = CMSG_FIRSTHDR(&msghdr);
  if (ctrl == NULL) return -1;

  ctrl->cmsg_len = CMSG_LEN(fds_size);
  ctrl->cmsg_level = SOL_SOCKET;
  ctrl->cmsg_type = SCM_RIGHTS;

  memcpy(CMSG_DATA(ctrl), fds, fds_size);

  if (sendmsg(receiver_fd, &msghdr, 0) == -1) {
    printf("[Protocol] Failed to send message.\n");
    return -1;
  }

  return 0;
}

}  // namespace Protocol
