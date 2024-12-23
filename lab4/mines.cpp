#include <algorithm>  // Для std::all_of
#include <iostream>
#include "Board.hpp"

void main_game() {
  int rows, cols, mines_count;
  std::cin >> rows >> cols >> mines_count;

  std::vector<std::pair<int, int>> mines_coords(mines_count);
  for (int i = 0; i < mines_count; ++i) {
    std::cin >> mines_coords[i].first >> mines_coords[i].second;
  }

  Board board(rows, cols, mines_coords);

  while (true) {
    board.print(std::cout);
    std::string command;
    std::cin >> command;

    if (command == "exit") {
      break;
    } else if (command == "open") {
      int row, col;
      std::cin >> row >> col;
      board.open(row, col);
      if (board.has_mine(row, col)) {
        board.print(std::cout);
        std::cout << "You lose!" << '\n';
        break;
      }
      // Проверьте, выиграл ли игрок
      if (std::all_of(board.get_cells().begin(), board.get_cells().end(),
                      [](const std::vector<Cell>& row) {
                        return std::all_of(
                            row.begin(), row.end(), [](const Cell& cell) {
                              return cell.is_opened_ || cell.has_mine_;
                            });
                      })) {
        board.print(std::cout);
        std::cout << "You win!" << '\n';
        break;
      }
    } else if (command == "flag") {
      int row, col;
      std::cin >> row >> col;
      board.flag(row, col);
    }
  }
}

int main() {
  main_game();
  return 0;
}