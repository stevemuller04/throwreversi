#include "Board.h"

Board::Board(coord_t width, coord_t height)
{
	_width = width;
	_height = height;
	_owners = new Player[width * height];
	memset(_owners, 0, width * height * sizeof(Player));
}

Board::~Board()
{
	delete[] _owners;
}

coord_t Board::getWidth() const
{
	return _width;
}

coord_t Board::getHeight() const
{
	return _height;
}

bool Board::contains(Tile const &tile) const
{
	return
		tile.x >= 0 && tile.x < _width &&
		tile.y >= 0 && tile.y < _height;
}

Player Board::getTileOwner(Tile const &tile) const
{
	return _owners[tile.y * _height + tile.x];
}

void Board::setTileOwner(Tile const &tile, Player owner)
{
	_owners[tile.y * _height + tile.x] = owner;
}
