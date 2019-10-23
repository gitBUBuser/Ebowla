#ifndef  BOARD_HEADER
#define BOARD_HEADER
class Game;

class Board
{
public:
	Board(const int& width,const int& height, const int& middleX, const int& middleY, Game* aGame);
	void Draw();
	~Board();
private:
	int myStartX;
	int myStartY;

	int myEndX;
	int myEndY;

	Game* myGame;
};

#endif 