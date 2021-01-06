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
	virtual void render() {}

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
private:
	struct tagInfo
	{
		image* portrait;		//ĳ���� �ʻ�ȭ
		image* name;			//ĳ���� �̸�
		vector3 pos;			//��ġ
		vector3 goal;			//��ǥ ����
	};

	struct tagSkip
	{
		//UI* bar;				//��ŵ ���α׷��� ��
		float curGauge;			//���� ������
		float maxGauge;			//�ִ� ������
		bool isStayDown;		//������ ��
	};

	enum class curDialogue
	{
		ENTER,	//�̹����� ȭ������ ��������
		WRITE,	//��縦 ��� �ϱ�
		EXIT,	//�̹����� ȭ�� ������ ����
	};

	enum class DIALOGUELIST
	{
		INTRO,
		BOSS_BEFORE,
		BOSS_AFTER,
	};

	queue<string>	_qMsg;		//���
	queue<tagInfo>	_qInfo;		//����
	tagSkip			_skip;		//��ŵ
	string			_writeText;	//���� ���
	curDialogue		_curDia;	//

	bool			_isPlay;	//���� ���� ��
	float			_imgSpeed;	//�̹��� �ӵ�
	float			_textSpeed;	//�ؽ�Ʈ �ӵ�
	float			_elpaSec;	//�ð� ���
	int				_stringNum;	//����� ���� ��ġ
	float			_textTerm;	//�ؽ�Ʈ ��� �� ȭ�� �Ѿ�� ��
	float			_textY;		//�ؽ�Ʈ ���� �� Y�� ��ġ ����

public:

	virtual void enter();
	virtual bool update();
	virtual void exit();

	dialogue(DIALOGUELIST chapter, float textSpeed);
	~dialogue() {}

	HRESULT init(float textSpeed);
	void render();

	void startChapter(DIALOGUELIST chapter);
	bool getIsPlay() { return _isPlay; }

	bool textUpdate(float elapsedTime);
	bool findNameImg(string src, string name);
	void keyReaction();
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