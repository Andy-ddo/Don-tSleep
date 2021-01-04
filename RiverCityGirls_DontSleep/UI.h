#pragma once

enum class UITYPE;

/*====================================================================
						���� �̹��� UI
====================================================================*/
class UI
{
public:
	UITYPE type;
	image* img;
	vector3 pos;
	vector3 goal;
	float speed;

	void update();
	void render(HDC hdc);
	bool isActive;
	bool isMove;
	void move(vector3 point, float speed);
	void setActive(bool active) { isActive = active; }
};

/*====================================================================
						Progress Bar UI
====================================================================*/
class Bar : public UI
{
	float ratio;
public:
	void render(HDC hdc);
};

/*====================================================================
						�� �� �� ��
====================================================================*/
class Inventory : public UI
{
public:
	void render(HDC hdc);
};