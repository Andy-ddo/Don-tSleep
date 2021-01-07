#pragma once

class Video;
enum class VIDEOTYPE;

enum class DIALOGLIST;
class Player;

/*====================================================================
	�̺�Ʈ Ŭ�����Դϴ�. �پ��� �̺�Ʈ���� ����ϰ� �ֽ��ϴ�.
====================================================================*/
class Event
{
protected:
	bool _isEnd;
	bool _isMovie;
	bool _isCameraMove;
	Player* _player;

public:
	virtual void enter(bool playerControl);
	virtual bool update() = 0;
	virtual void exit();
	virtual void render(HDC hdc) {}

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

	virtual void enter(bool playerControl);
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

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();
};

/*====================================================================
	��ȭ
====================================================================*/
class dialogue : public Event
{
private:
	vector<string>	_vScript;		//��ũ��Ʈ
	int				_scriptIndex;	//��ũ��Ʈ �ε���

	string			_txt;			//�ؽ�Ʈ
	int				_txtIndex;		//�ؽ�Ʈ �ε���

	DIALOGLIST		_list;		//��ȭ ����Ʈ
	string			_file;		//�ؽ�Ʈ ����


public:

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();

	dialogue(DIALOGLIST file);
	~dialogue() {}

	void render(HDC hdc);
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

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();
};