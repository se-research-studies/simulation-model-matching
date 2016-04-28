#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {  
  if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " -sim=SIMULATION -rounds=ROUNDS" << std::endl;
      exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
