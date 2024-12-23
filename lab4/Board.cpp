#include "Board.hpp"

Cell::Cell()
    : is_opened_(false), has_flag_(false), has_mine_(false), mines_count_(0) {}

Board::Board(int rows,
             int cols,
             const std::vector<std::pair<int, int>>& mines_coords)
    : rows(rows), cols(cols), cells(rows, std::vector<Cell>(cols)) {
  place_mines(mines_coords);
  calculate_mines_count();
}

void Board::open(int row, int col) {
  if (cells[row][col].is_opened_ || cells[row][col].has_flag_)
    return;
  cells[row][col].is_opened_ = true;

  if (cells[row][col].has_mine_)
    return;

  if (cells[row][col].mines_count_ == 0) {
    for (int r = std::max(0, row - 1); r <= std::min(rows - 1, row + 1); ++r) {
      for (int c = std::max(0, col - 1); c <= std::min(cols - 1, col + 1);
           ++c) {
        if (!(r == row && c == col)) {
          open(r, c);
        }
      }
    }
  }
}

void Board::flag(int row, int col) {
  if (!cells[row][col].is_opened_) {
    cells[row][col].has_flag_ = !cells[row][col].has_flag_;
  }
}

void Board::print(std::ostream& output_stream) {
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      Cell& cell = cells[row][col];
      if (cell.is_opened_) {
        if (cell.has_mine_) {
          output_stream << '*';
        } else if (cell.mines_count_ > 0) {
          output_stream << cell.mines_count_;
        } else {
          output_stream << '.';
        }
      } else if (cell.has_flag_) {
        output_stream << 'F';
      } else {
        output_stream << '#';
      }
    }
    output_stream << '\n';
  }
}

bool Board::has_mine(int row, int col) const {
  return cells[row][col].has_mine_;
}

bool Board::is_opened(int row, int col) const {
  return cells[row][col].is_opened_;
}

const std::vector<std::vector<Cell>>& Board::get_cells() const {
  return cells;
}

void Board::place_mines(const std::vector<std::pair<int, int>>& mines_coords) {
  for (const auto& coord : mines_coords) {
    cells[coord.first][coord.second].has_mine_ = true;
  }
}

void Board::calculate_mines_count() {
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      if (cells[row][col].has_mine_)
        continue;

      size_t count = 0;
      for (int r = std::max(0, row - 1); r <= std::min(rows - 1, row + 1);
           ++r) {
        for (int c = std::max(0, col - 1); c <= std::min(cols - 1, col + 1);
             ++c) {
          if (cells[r][c].has_mine_) {
            count++;
          }
        }
      }
      cells[row][col].mines_count_ = count;
    }
  }
}