#pragma once
#include "Stuff.h"
#include "tileNode.h"
class tileMap;

class Bomb :
	public Stuff
{
	static tagTile* _tiles;

public:
	virtual HRESULT init();				//void로 써도되는데 초기화에 문제가 생기면 바로 알려줌
	virtual void render();

	static void setLinkTileMap(tagTile * tiles) { _tiles = tiles; }

	virtual bool collide(Actor * a, vector<Enemy*>& em);
	virtual bool collide(Actor * a);
	virtual bool checkAttack() { return true; }

	virtual bool damaged(Actor * a, vector<Enemy*>& em);

	void collideStuff(vector<Enemy*>& em);

	Bomb() {}
	Bomb(Image * img, POINT renderPos);
	~Bomb() {}


};

