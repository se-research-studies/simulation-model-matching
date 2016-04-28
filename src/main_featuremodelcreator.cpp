#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " -in=SIMULATION" << std::endl;
      exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
