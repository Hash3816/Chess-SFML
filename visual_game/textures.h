#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "../base_structures/piece_type.h"
#include "../base_structures/colors.h"


std::string textureName(Piece_Type type, Color color);
std::unordered_map<std::string, sf::Texture>& getTextures();
