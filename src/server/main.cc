#include <unistd.h>
#include "sample_server.h"

int main(int argc, char* argv[]) {
  Server::SampleServer ss;

  while (1) {
    ss.OpenServer();
    ss.ReceiveMessage();
    ss.CloseCurrentClient();
    sleep(1);
  }

  return 0;
}
