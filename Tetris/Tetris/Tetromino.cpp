#include "Tetromino.h"


Tetromino::Tetromino(Game* aGame,const std::vector<Vector2D>& aShape)
{
	myGame = aGame;
	myShape = aShape;

	myPosition.SetX(gameData::SCREEN_WIDTH / 2);
	myPosition.SetY(gameData::SCREEN_HEIGHT / 5);
}


Tetromino::~Tetromino()
{
}

const Vector2D& Tetromino::GetPosition() {
	return myPosition;
}

void Tetromino::Gravity() {
	if (!myGrounded) {
		if (myGame->Timer(gravityMaxTime, gravityTime)) {
			if (CollisionCheck(Vector2D(0,1))) {
				myPosition += Vector2D(0, 1);
			}
			else
			{
				myGrounded = true;

			}
		}
	}
}

bool Tetromino::CollisionCheck(const Vector2D& aDirection) {
	int numberOfAcceptable = 0;
	for (int i = 0; i < 4; i++)
	{
		bool canCollide = true;
		Vector2D newPos = myPosition + aDirection + myShape[i];
		for (int j = 0; j < 4; j++)
		{
			if (newPos == (myPosition + myShape[j])) {
				canCollide = false;
				numberOfAcceptable++;
			}
		}

		if (canCollide) {
			if (!myGame->PositionIsTaken(newPos)) {
				numberOfAcceptable++;
			}
			else {
				return false;
			}
		}
	}
	if (numberOfAcceptable == 3) {
		return true;
	}
}

void Tetromino::Update() {
	Gravity();
}

void Tetromino::Draw() {
	for (int i = 0; i < myShape.size(); i++)
	{
		myGame->SetCharacter(myPosition + myShape[i], gameData::BOX, gameData::Blue);
	}
}