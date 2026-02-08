#pragma once
#include "../main_structure_and_logic/Chess_Game.h"
#include "../visual_game/textures.h"
#include <iostream>



void Game::draw_board (sf::RenderWindow& window, sf::Event& event) {
    const int windowSize = 640;
    const int tiles = 8;
    const float tileSize = static_cast<float>(windowSize) / tiles;

    static sf::Font font;
    font.loadFromFile("assets/DejaVuSans.ttf");

    draw_under_menu(window, font);

    sf::RectangleShape square(sf::Vector2f(tileSize - 1, tileSize - 1));
    square.setOutlineThickness(1.0f);//Чёрные границы разделяющие клетки
    square.setOutlineColor(sf::Color::Black);

    sf::CircleShape circle(float(tileSize / 3), 4);

    circle.setFillColor(sf::Color(128, 128, 128));

    for (int y = 0; y < tiles; ++y) {
        for (int x = 0; x < tiles; ++x) {
            Cell& cell = this->board.matrix_pieces[y][x];

            if (cell.get_color_cell() == Color::White) {
                square.setFillColor(sf::Color(240, 217, 181));

                square.setPosition(x * tileSize, (7 - y) * tileSize);
                window.draw(square); // отрисовка клетки
            }

            else if (cell.get_color_cell() == Color::Black) {
                square.setFillColor(sf::Color(181, 136, 99));

                square.setPosition(x * tileSize, (7 - y) * tileSize);
                window.draw(square); // отрисовка клетки
            }

            else if (cell.get_color_cell() == Color::Green) {
                circle.setFillColor(sf::Color(0, 128, 0, 50));
                circle.setPosition(x * tileSize + 14, (7 - y) * tileSize + 14);
                window.draw(circle);
            }
            else if (cell.get_color_cell() == Color::Red) {
                square.setFillColor(sf::Color(200, 100, 100, 50));
                square.setPosition(x * tileSize, (7 - y) * tileSize);
                window.draw(square);
            }

            // Отрисовка фигуры
            if (!cell.is_empty && cell.piece) {
                Piece_Type type_piece = cell.piece->get_type();
                Color piece_color = cell.piece->get_color_piece();
                std::string key = textureName(type_piece, piece_color);

                auto it = textures.find(key);
                if (it != textures.end()) {
                    const sf::Texture& tex = it->second;

                    sf::Sprite sprite;
                    sprite.setTexture(tex, true);

                    sf::Vector2u texSize = tex.getSize();
                    if (texSize.x > 0 && texSize.y > 0) {
                        float scaleX = tileSize / static_cast<float>(texSize.x);
                        float scaleY = tileSize / static_cast<float>(texSize.y);
                        float scale = std::min(scaleX, scaleY) * 0.9f;
                        sprite.setScale(scale, scale);

                        float spriteW = texSize.x * sprite.getScale().x;
                        float spriteH = texSize.y * sprite.getScale().y;
                        float posX = x * tileSize + (tileSize - spriteW) / 2.0f;
                        float posY = (7 - y) * tileSize + (tileSize - spriteH) / 2.0f;
                        sprite.setPosition(posX, posY);

                        window.draw(sprite);
                    }
                }
            }
        }
    }


    if (this->board.mate) {

        Color winner = (this->color_current_player == Color::White) ? Color::Black : Color::White;
        std::string winnerText = (winner == Color::White) ? "White wins!\nPress R to restart" : "Black wins!\nPress R to restart";

        sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(windowSize) * 0.8f, static_cast<float>(windowSize) * 0.3f));
        overlay.setFillColor(sf::Color(0, 0, 0, 160));
        overlay.setOutlineColor(sf::Color::White);
        overlay.setOutlineThickness(2.f);
        overlay.setPosition(windowSize * 0.1f, windowSize * 0.35f);


        sf::Text text;
        text.setFont(font);
        text.setString(winnerText);
        text.setCharacterSize(40);
        text.setStyle(sf::Text::Bold);

        sf::FloatRect txtRect = text.getLocalBounds();
        text.setOrigin(txtRect.left + txtRect.width / 2.0f, txtRect.top + txtRect.height / 2.0f);
        text.setPosition(windowSize / 2.0f, windowSize * 0.5f);

        window.draw(overlay);
        window.draw(text);

        if (event.key.code == sf::Keyboard::R) {
            board.set_default();
            window.clear();
            window.close();

            start_Game();
        }
    }
}
void Game::draw_menu_and_select_type_piece(Coordinates coord_pawn, sf::RenderWindow& window, sf::Event& event) {
    sf::RectangleShape background(sf::Vector2f(320, 90));
    background.setPosition(162.5, 275);
    background.setFillColor(sf::Color(50, 50, 50, 200));

    sf::RectangleShape knight_button(sf::Vector2f(80, 80));
    sf::RectangleShape bishop_button(sf::Vector2f(80, 80));
    sf::RectangleShape rook_button(sf::Vector2f(80, 80));
    sf::RectangleShape queen_button(sf::Vector2f(80, 80));

    knight_button.setPosition(160, 280);
    bishop_button.setPosition(240, 280);
    rook_button.setPosition(320, 280);
    queen_button.setPosition(400, 280);

    sf::FloatRect knight_button_bounds = knight_button.getGlobalBounds();
    sf::FloatRect bishop_button_bounds = bishop_button.getGlobalBounds();
    sf::FloatRect rook_button_bounds = rook_button.getGlobalBounds();
    sf::FloatRect king_button_bounds = queen_button.getGlobalBounds();

    knight_button.setFillColor(sf::Color::White);
    bishop_button.setFillColor(sf::Color::White);
    rook_button.setFillColor(sf::Color::White);
    queen_button.setFillColor(sf::Color::White);

    sf::Texture texture_knight = this->textures[textureName(Piece_Type::Knight, this->color_current_player)];
    sf::Texture texture_bishop = this->textures[textureName(Piece_Type::Bishop, this->color_current_player)];
    sf::Texture texture_rook = this->textures[textureName(Piece_Type::Rook, this->color_current_player)];
    sf::Texture texture_queen = this->textures[textureName(Piece_Type::Queen, this->color_current_player)];

    knight_button.setTexture(&texture_knight, true);
    bishop_button.setTexture(&texture_bishop, true);
    rook_button.setTexture(&texture_rook, true);
    queen_button.setTexture(&texture_queen, true);

    window.draw(background);
    window.draw(knight_button);
    window.draw(bishop_button);
    window.draw(rook_button);
    window.draw(queen_button);

    window.display();
    window.clear();

    while (window.isOpen()) {//Ожидание клика по нужной области
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.key.code != sf::Mouse::Button::Left) {
                continue;
            }

            auto cords_click_mouse_x = event.mouseButton.x;
            auto cords_click_mouse_y = event.mouseButton.y;



            if (knight_button_bounds.contains(cords_click_mouse_x, cords_click_mouse_y)) {
                this->board.matrix_pieces[coord_pawn.y][coord_pawn.x].del_piece();
                this->board.matrix_pieces[coord_pawn.y][coord_pawn.x].set_piece(Piece_Type::Knight, this->color_current_player);
                return;
            }

            else if (bishop_button_bounds.contains(cords_click_mouse_x, cords_click_mouse_y)) {
                this->board.matrix_pieces[coord_pawn.y][coord_pawn.x].del_piece();
                this->board.matrix_pieces[coord_pawn.y][coord_pawn.x].set_piece(Piece_Type::Bishop, this->color_current_player);
                return;
            }

            else if (rook_button_bounds.contains(cords_click_mouse_x, cords_click_mouse_y)) {
                this->board.matrix_pieces[coord_pawn.y][coord_pawn.x].del_piece();
                this->board.matrix_pieces[coord_pawn.y][coord_pawn.x].set_piece(Piece_Type::Rook, this->color_current_player);
                return;
            }
            else if (king_button_bounds.contains(cords_click_mouse_x, cords_click_mouse_y)) {
                this->board.matrix_pieces[coord_pawn.y][coord_pawn.x].del_piece();
                this->board.matrix_pieces[coord_pawn.y][coord_pawn.x].set_piece(Piece_Type::Queen, this->color_current_player);
                return;
            }
        }
    }
}
void Game::draw_under_menu(sf::RenderWindow& window, static sf::Font& font) { //Отрисовка кнопок для создания 2 рокировок(левая-длинная и правая-короткая)
    sf::Text text_castling;
    text_castling.setFont(font);
    text_castling.setString("Castling:");
    text_castling.setCharacterSize(20);
    text_castling.setStyle(sf::Text::Bold);
    text_castling.setPosition(370, 650);

    sf::Text text_long_castling;
    text_long_castling.setFont(font);
    text_long_castling.setString("Long");
    text_long_castling.setCharacterSize(20);
    text_long_castling.setStyle(sf::Text::Bold);
    text_long_castling.setPosition(487, 650);

    sf::Text text_short_castling;
    text_short_castling.setFont(font);
    text_short_castling.setString("Short");
    text_short_castling.setCharacterSize(20);
    text_short_castling.setStyle(sf::Text::Bold);
    text_short_castling.setPosition(560, 650);

    sf::RectangleShape upper_line(sf::Vector2f(640, 2));
    sf::RectangleShape background(sf::Vector2f(640, 48));

    sf::RectangleShape long_castling_button(sf::Vector2f(64, 40));
    sf::RectangleShape short_castling_button(sf::Vector2f(69, 40));

    upper_line.setPosition(0, 640);
    upper_line.setFillColor(sf::Color(44, 62, 44));

    background.setPosition(0, 642);
    background.setFillColor(sf::Color(10, 50, 10));

    long_castling_button.setPosition(480, 645);
    short_castling_button.setPosition(555, 645);

    long_castling_button.setFillColor(sf::Color(40, 53, 147));
    short_castling_button.setFillColor(sf::Color(40, 53, 147));

    window.draw(background);
    window.draw(upper_line);

    window.draw(long_castling_button);
    window.draw(short_castling_button);

    window.draw(text_castling);
    window.draw(text_long_castling);
    window.draw(text_short_castling);

    this->lower_menu_buttons_bounds[Type_Castling::Long] = long_castling_button.getGlobalBounds();
    this->lower_menu_buttons_bounds[Type_Castling::Short] = short_castling_button.getGlobalBounds();
}
