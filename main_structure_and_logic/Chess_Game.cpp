#include "../main_structure_and_logic/Chess_Game.h"
#include "../visual_game/textures.h"

void Game::start_Game() {
    this->color_current_player = Color::White;
    this->first_click = true;
    this->textures = getTextures();

    sf::RenderWindow window(sf::VideoMode(640, 690), L"Шахматы", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;


        while (window.pollEvent(event)) { // Обработка пула событий
            if (event.type == sf::Event::Closed) window.close();

            if (event.key.code != sf::Mouse::Button::Left) {
                continue;
            }


            bool check = false;
            std::vector<Info_Move> possible_moves_with_check;

            if (board.is_check(this->color_current_player)) {
                check = true;
                possible_moves_with_check = board.is_mate(color_current_player);

                if (board.mate) {
                    draw_board(window, event);
                    break;
                }
            }



            if (first_click) {
                std::vector<Coordinates> possible_moves;

                auto cords_click_1 = getClicked(event, window, 80); //Обработка кликов


                if (!cords_click_1.has_value()) { // Клика по клеткам не было или клик по меню
                    continue;
                }

                // Отрисовка ходов (1 клик)
                Cell& cell_began_piece = this->board.matrix_pieces[cords_click_1->y][cords_click_1->x];

                if (!cell_began_piece.is_empty && (cell_began_piece.piece->get_color_piece() == color_current_player)) {

                    if (!check) {

                        for (Coordinates cord_move_piece : board.matrix_pieces[cords_click_1->y][cords_click_1->x].piece->get_possible_moves(board)) {
                            if (board.is_current_move(cell_began_piece.get_coordinates_cell(), cord_move_piece)) {
                                possible_moves.push_back(cord_move_piece);
                            }
                        }
                    }

                    if (check) {

                        std::vector<Coordinates> possible_moves_piece = board.matrix_pieces[cords_click_1->y][cords_click_1->x].piece->get_possible_moves(board);

                        for (Coordinates cord_move_piece : possible_moves_piece) {

                            for (Info_Move possible_move : possible_moves_with_check) {

                                if ((cord_move_piece.x == possible_move.move_pos.x) && (cord_move_piece.y == possible_move.move_pos.y) &&
                                    (cell_began_piece.get_coordinates_cell().x == possible_move.began_pos.x) && (cell_began_piece.get_coordinates_cell().y == possible_move.began_pos.y))
                                {
                                    possible_moves.push_back(cord_move_piece);
                                }
                            }
                        }
                    }

                    for (Coordinates possible_cord : possible_moves) {

                        if (board.matrix_pieces[possible_cord.y][possible_cord.x].is_empty) {
                            board.matrix_pieces[possible_cord.y][possible_cord.x].color = Color::Green; // Обычный ход
                        }

                        else {
                            board.matrix_pieces[possible_cord.y][possible_cord.x].color = Color::Red; // Взятие
                        }

                    }

                }
                // Если есть возможные ходы
                if (!possible_moves.empty()) {
                    this->rendering_coordinates = possible_moves;
                    this->first_click = false;
                    this->cords_select_piece = Coordinates(cords_click_1->y, cords_click_1->x);
                    continue;
                }

            }
            if (!first_click) {
                auto cord_click_2 = getClicked(event, window, 80);

                if (!cord_click_2.has_value()) { // Клика не было
                    continue;
                }

                if ((cord_click_2->x == cords_select_piece.x) && (cord_click_2->y == cords_select_piece.y)) {
                    continue;
                }

                if (is_valid_move(cord_click_2)) {
                    Piece_Type type_piece = this->board.matrix_pieces[cords_select_piece.y][cords_select_piece.x].piece->get_type();
                    Color color_piece = this->color_current_player;

                    if (type_piece == Piece_Type::Rook || type_piece == Piece_Type::King) {
                        this->board.update_state_castling(cords_select_piece);
                    }

                    this->board.move_piece(cords_select_piece, Coordinates(cord_click_2->y, cord_click_2->x));
                    this->first_click = true;

                    if (type_piece == Piece_Type::Pawn) {
                        if ((color_piece == Color::White && cord_click_2->y == 7) || (color_piece == Color::Black && cord_click_2->y == 0)) {
                            draw_menu_and_select_type_piece(Coordinates(cord_click_2->y, cord_click_2->x), window, event);
                        }
                    }

                    this->change_player();

                    clear_render_cells();
                }
                else {
                    // Если игрок после перового клика сделал клик не туда то он заново проводит выбор и ход
                    clear_render_cells();
                    this->first_click = true;
                    this->rendering_coordinates.clear();
                }
            }
        }
        draw_board(window, event);
        window.display();
    }
};


void Game::change_player() {
    if (color_current_player == Color::White) {
        color_current_player = Color::Black;
    }
    else {
        color_current_player = Color::White;
    }
}

void Game::clear_render_cells() {
    for (auto cord_cell : this->rendering_coordinates) {
        board.matrix_pieces[cord_cell.y][cord_cell.x].color = ((cord_cell.x + cord_cell.y) % 2 == 0)
            ? Color::Black   // чётные поля — чёрные
            : Color::White;  // нечётные — белые
    }

    this->rendering_coordinates.clear();
}

bool Game::is_valid_move(std::optional<Coordinates> cord_2_click) {
    if (cord_2_click.has_value()) {
        for (auto possible_cord : this->rendering_coordinates) {
            if ((cord_2_click->x == possible_cord.x) && (cord_2_click->y == possible_cord.y)) {
                return true;
            }
        }

    }
    return false;
}