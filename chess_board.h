#pragma once
#include "cell.h"
#include "info_move.h"

class Chess_Board {
public:
    std::vector<std::vector<Cell>> matrix_pieces;

    Coordinates cords_white_king;
    Coordinates cords_black_king;
    bool mate;

    bool is_check(Color color_current_player);
    bool is_current_move(Coordinates began_pos, Coordinates move_pos);//Отсечение ходов, которые приводят к мату
    std::vector<Info_Move> is_mate(Color color_current_player); // Возращает массив возможных ходов во время шаха, или возращает пустой массив и ставит this->mate = true
    void move_piece(Coordinates began_pos, Coordinates move_pos);

    Chess_Board();
    ~Chess_Board();

    Chess_Board(const Chess_Board&) = delete;
    Chess_Board& operator=(const Chess_Board&) = delete;

    void set_default_placement();
    void set_default();
};
