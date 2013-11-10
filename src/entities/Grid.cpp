#include "Grid.h"

Grid::Grid( ALLEGRO_BITMAP* bmpImgIn )
: grid( 10, std::vector<Block>( 20, Block( bmpImgIn ) ) ) {

}

Grid::~Grid() {

}

void Grid::set( int x, int y, Block blockIn ) {
	grid[x][y] = blockIn;
}

Block* Grid::get( int x, int y ) {
	return &grid[x][y];
}