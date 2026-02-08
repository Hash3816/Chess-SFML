#include "../visual_game/textures.h"
#include <iostream>

 std::string textureName(Piece_Type type, Color color) {
    std::string color_name = (color == Color::White) ? "white" : "black";
    switch (type) {
    case Piece_Type::Pawn:   return color_name + "_pawn";
    case Piece_Type::Knight: return color_name + "_knight";
    case Piece_Type::Bishop: return color_name + "_bishop";
    case Piece_Type::Rook:   return color_name + "_rook";
    case Piece_Type::Queen:  return color_name + "_queen";
    case Piece_Type::King:   return color_name + "_king";

    default: return "error";
    }
};

std::unordered_map<std::string, sf::Texture>& getTextures() {
    static std::unordered_map<std::string, sf::Texture> textures;
    static bool initialized = false;
    if (!initialized) {
        initialized = true;

        const std::string base = "assets/";

        std::vector<std::string> names = {
            "white_pawn","white_knight","white_bishop","white_rook","white_queen","white_king",
            "black_pawn","black_knight","black_bishop","black_rook","black_queen","black_king"
        };

        for (const auto& name : names) {
            sf::Texture texture;
            std::string path = base + name + ".png";
            if (!texture.loadFromFile(path)) {
                std::cerr << "Warning: cannot load texture: " << path << std::endl;
                texture.create(1, 1);
            }

            textures.emplace(name, std::move(texture));
        }
    }
    return textures;
};