#include "client/sample_client.h"
#include "protocol/protocol.h"

int main() {
  Client::SampleClient sc;

  sc.ConnectServer();
  while (1)
    sc.SendPrintHelloWorld(true);
  sc.CloseClient();

  return 0;
}
