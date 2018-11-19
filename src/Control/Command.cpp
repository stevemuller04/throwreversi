#include "Command.h"

Command const Command::Empty = {
	.selected_tile = Tile::Undetermined,
	.selected_player = Player::None,
	.has_changed = true,
	.is_complete = false,
};
