#include "sample_server.h"

int main(int argc, char* argv[]) {
  SampleServer ss;

  ss.OpenServer();

  while (1) {
    ss.ReceiveMessage();
    // ss.CloseCurrentClient();
  }

  return 0;
}
