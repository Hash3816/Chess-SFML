#pragma once
#include <SFML/Graphics.hpp>
#include<optional>
#include <unordered_map>
#include "../main_structures_and_logic/chess_board.h"

class Game {
private:
    Chess_Board board;

    Color color_current_player;
    bool first_click;

    std::unordered_map<Type_Castling, sf::FloatRect> lower_menu_buttons_bounds;

    Coordinates cords_select_piece;
    std::vector<Coordinates> rendering_coordinates;

public:
    std::unordered_map<std::string, sf::Texture> textures;

    std::optional<Coordinates> getClicked(sf::Event& event, sf::RenderWindow& window, int cellSize);
    void draw_board(sf::RenderWindow& window, sf::Event& event);
    void draw_menu_and_select_type_piece(Coordinates coord_pawn, sf::RenderWindow& window, sf::Event& event);
    void draw_under_menu(sf::RenderWindow& window, static sf::Font& font);
    void start_Game();
    void change_player();
    void clear_render_cells();
    bool is_valid_move(std::optional<Coordinates> cord_2_click);
};
