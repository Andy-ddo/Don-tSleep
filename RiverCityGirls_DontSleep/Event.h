#pragma once

class Video;
enum class VIDEOTYPE;
class Player;

/*====================================================================
	�̺�Ʈ Ŭ�����Դϴ�. �پ��� �̺�Ʈ���� ����ϰ� �ֽ��ϴ�.
====================================================================*/
class Event
{
protected:
	bool _isEnd;
	bool _isMovie;
	Player* _player;

public:
	virtual void enter() { _isEnd = false; _isMovie = false; }
	virtual bool update() = 0;
	virtual void exit() = 0;

	bool isMovie() { return _isMovie; }
	void setLinkPlyaer(Player* player) { _player = player; }
};

/*====================================================================
	ī�޶� �̵��� ���� ����
====================================================================*/
class cameraMove : public Event
{
private:
	vector3 _goal;
	float _moveSpeed;
	float _mag;
	float _magSpeed;

public:
	cameraMove(vector3 goal, float moveSpeed, float mag, float magSpeed);
	~cameraMove() {}

	virtual void enter();
	virtual bool update();
	virtual void exit();
};


/*====================================================================
	������ ���
====================================================================*/
class moviePlay : public Event
{
	VIDEOTYPE _videoName;
	Video* _video;

public:
	moviePlay(VIDEOTYPE fileName);

	virtual void enter();
	virtual bool update();
	virtual void exit();
};

/*====================================================================
	��ȭ
====================================================================*/
class dialogue : public Event
{
public:

	virtual void enter();
	virtual bool update();
	virtual void exit();
};


/*====================================================================
	���
====================================================================*/
class waitForSec : public Event
{
private:
	float _sec;
	float _endTime;

public:
	waitForSec(float sec);

	virtual void enter();
	virtual bool update();
	virtual void exit();
};