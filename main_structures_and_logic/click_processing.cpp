#include "../main_structures_and_logic/Chess_Game.h"

std::optional<Coordinates> Game::getClicked(sf::Event& event, sf::RenderWindow& window, int cellSize)
{
    auto cords_click_mouse_x = event.mouseButton.x;
    auto cords_click_mouse_y = event.mouseButton.y;


    int x = cords_click_mouse_x / cellSize;
    int y = (640 - cords_click_mouse_y) / cellSize;

    while (window.pollEvent(event)) { //Отчистка буфера событий

    }

    if (this->lower_menu_buttons_bounds[Type_Castling::Long].contains(cords_click_mouse_x, cords_click_mouse_y)) {
        if (this->board.is_check(this->color_current_player)) {
            window.pollEvent(event);

            return std::nullopt;
        }

        if (this->color_current_player == Color::White && !this->board.castling_state.white_king_move && !this->board.castling_state.left_white_rook_move) {

            if (this->board.matrix_pieces[0][1].is_empty && this->board.matrix_pieces[0][2].is_empty && this->board.matrix_pieces[0][3].is_empty) {

                bool status = this->board.make_castling(Type_Castling::Long, this->color_current_player);
                if (!status) {
                    window.pollEvent(event);
                    return std::nullopt;
                }

                this->draw_board(window, event);
                window.display();
                window.pollEvent(event);

                this->change_player();

                return std::nullopt;
            }
        }

        else if (this->color_current_player == Color::Black && !this->board.castling_state.black_king_move && !this->board.castling_state.left_black_rook_move) {

            if (this->board.matrix_pieces[7][1].is_empty && this->board.matrix_pieces[7][2].is_empty && this->board.matrix_pieces[7][3].is_empty) {

                bool status = this->board.make_castling(Type_Castling::Long, this->color_current_player);
                if (!status) {
                    window.pollEvent(event);
                    return std::nullopt;
                }

                this->draw_board(window, event);
                window.display();
                window.pollEvent(event);

                this->change_player();

                return std::nullopt;
            }
        }

        window.pollEvent(event);
        return std::nullopt;
    }

    if (this->lower_menu_buttons_bounds[Type_Castling::Short].contains(cords_click_mouse_x, cords_click_mouse_y)) {

        if (this->color_current_player == Color::White && !this->board.castling_state.white_king_move && !this->board.castling_state.right_white_rook_move) {

            if (this->board.matrix_pieces[0][5].is_empty && this->board.matrix_pieces[0][6].is_empty) {

                bool status = this->board.make_castling(Type_Castling::Short, this->color_current_player);
                if (!status) {
                    window.pollEvent(event);
                    return std::nullopt;
                }

                this->draw_board(window, event);
                window.display();
                window.pollEvent(event);

                this->change_player();

                return std::nullopt;
            }
        }

        else if (this->color_current_player == Color::Black && !this->board.castling_state.black_king_move && !this->board.castling_state.right_black_rook_move) {

            if (this->board.matrix_pieces[7][5].is_empty && this->board.matrix_pieces[7][6].is_empty) {

                bool status = this->board.make_castling(Type_Castling::Short, this->color_current_player);
                if (!status) {
                    window.pollEvent(event);
                    return std::nullopt;
                }

                this->draw_board(window, event);
                window.display();
                window.pollEvent(event);

                this->change_player();

                return std::nullopt;
            }
        }
        window.pollEvent(event);
        return std::nullopt;
    }

    else if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        return Coordinates(y, x);
    }

    return std::nullopt;
}