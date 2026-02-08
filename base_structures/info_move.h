#pragma once
#include "../base_structures/coordinates.h"

class Info_Move {
public:
	Coordinates began_pos;
	Coordinates move_pos;

	Info_Move(Coordinates be_pos, Coordinates mov_pos) :began_pos(be_pos), move_pos(mov_pos) {
	};
};