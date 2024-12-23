// Board.hpp
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <utility>  // для std::pair
#include <vector>

class Cell {
 public:
  bool is_opened_;
  bool has_flag_;
  bool has_mine_;
  size_t mines_count_;

  Cell();
};

class Board {
 public:
  Board(int rows,
        int cols,
        const std::vector<std::pair<int, int>>& mines_coords);
  void open(int row, int col);
  void flag(int row, int col);
  void print(std::ostream& output_stream);

  // Методы доступа
  bool has_mine(int row, int col) const;
  bool is_opened(int row, int col) const;
  const std::vector<std::vector<Cell>>& get_cells() const;

 private:
  int rows, cols;
  std::vector<std::vector<Cell>> cells;

  void place_mines(const std::vector<std::pair<int, int>>& mines_coords);
  void calculate_mines_count();
};

#endif  // BOARD_HPP