#ifndef TERMINO_HEADER
#define TERMINO_HEADER
#include "Game.h"
#include <string>
#include "Vector2D.h"


class Tetromino
{
public:
	Tetromino(Game* aGame,const std::vector<Vector2D>& aShape);
	~Tetromino();
	const Vector2D& GetPosition();	
	void Draw();
	void Update();

private:
	void Gravity();
	bool CollisionCheck(const Vector2D& aDirection);
	bool myGrounded;
	Game* myGame;

	float gravityTime;
	float gravityMaxTime = 0.5f;
	std::vector<Vector2D> myShape;
	Vector2D myPosition;
};
#endif
