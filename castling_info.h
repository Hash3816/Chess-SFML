#pragma once

class Castling_Info{
public:
	bool white_king_move;
	bool black_king_move;

	bool left_white_rook_move;
	bool right_white_rook_move;

	bool left_black_rook_move;
	bool right_black_rook_move;

	Castling_Info() : white_king_move(false), black_king_move(false), left_white_rook_move(false), right_white_rook_move(false), left_black_rook_move(false),
		right_black_rook_move(false) {
	};

	Castling_Info(bool white_king_move, bool black_king_move, bool left_white_rook_move, bool right_white_rook_move, bool left_black_rook_move, bool right_black_rook_move)
		: white_king_move(white_king_move), black_king_move(black_king_move), left_white_rook_move(left_white_rook_move), right_white_rook_move(right_white_rook_move), left_black_rook_move(left_black_rook_move), right_black_rook_move(right_black_rook_move)
	{
	}
};

enum class Type_Castling {
	Long,
	Short,
};