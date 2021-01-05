#pragma once

enum class UITYPE;

/*====================================================================
						���� �̹��� UI
====================================================================*/
class UI
{
public:
	UITYPE _type;
	image* _img;

	vector3* _pos;
	vector3 _goal;
	float _speed;
	RECT _rc;

	bool _isActive;
	bool _isMove;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void setActive(bool active) { _isActive = active; }
};

/*====================================================================
						Progress Bar UI
====================================================================*/
class Bar : public UI
{
private:
	image* _back;
	image* _front;
	float _ratio;
	int* _current, *_max;

public:
	Bar(image* front, image* back, int* current, int* max);

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);


};

/*====================================================================
						�� �� �� ��
====================================================================*/
class Inventory : public UI
{
public:
	void render(HDC hdc);
};