#include "Grid.h"

Grid::Grid( ALLEGRO_BITMAP* bmpImgIn )
: grid( 20, std::vector<Block>( 10, Block( bmpImgIn ) ) ) {
	bmpImg = bmpImgIn;
}

Grid::~Grid() {

}

void Grid::set( int x, int y, Block blockIn ) {
	grid[x][y] = blockIn;
	rowCount[x] += 1;

	if( rowCount[x] >= 10 ) {
		deleteRow( x );
	}
}

Block* Grid::get( int x, int y ) {
	return &grid[x][y];
}

void Grid::deleteRow( int row ) {
	grid.erase( grid.begin() + row );
	grid.insert( grid.begin(), std::vector<Block>( 10, Block(bmpImg)));

	rowCount.erase( rowCount.begin() + row );
	rowCount.insert( rowCount.begin(), 0 );
}