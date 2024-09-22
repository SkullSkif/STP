#include <fstream>
#include <iomanip>
#include <iostream>

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);
  auto &in = file.is_open() ? file : std::cin;
  char out;
  std::string mass;
  int out_count = 0;
  int x_counter = 0;
  for (; out != EOF; x_counter++) {
    if (x_counter % 16 == 0) {
      if (x_counter != 0) {
        std::cout << '|' << mass << '|' << '\n';
        mass.clear();
      }
      std::cout << std::setw(8) << std::setfill('0') << std::hex << x_counter
                << std::setfill('0') << "  ";
    }
    out = in.get();
    if (out != EOF) {
      mass.push_back((std::isprint(out)) ? out : '.');
      std::cout << std::setw(2) << std::setfill('0') << std::hex
                << static_cast<int>(out) << " ";
      out_count++;
      if (out_count % 8 == 0) {
        std::cout << " ";
        out_count = 0;
      }
    }
  }
  std::cout << std::setw((16 - x_counter % 16) * 3 +
                         (x_counter % 16 <= 8 ? 6 : 5))
            << std::setfill(' ');
  std::cout << '|' << mass << std::setw(17 - mass.size()) << std::setfill(' ')
            << '|' << '\n';
  std::cout << std::setw(8) << std::setfill('0') << std::hex << --x_counter
            << '\n';
  (void)argc;
  return 0;
}