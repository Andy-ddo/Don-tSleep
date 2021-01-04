#include "stdafx.h"
#include "playGround.h"

/*====================================================================
	playGround����, �̹����� �߰��ϴ� �Լ��Դϴ�.
	���� ������ ���̴� ��� �̹����� �� ������ �߰��մϴ�.
====================================================================*/

void playGround::setImage()
{
	//================= �� �̹��� =================
	IMG_M->addImage("start_background", "source/image/ui/scene/StartScene_Background.bmp", 1280, 720, true, MAGENTA);
	IMG_M->addImage("start_title", "source/image/ui/scene/StartScene_Title.bmp", 537, 308, true, MAGENTA);
	IMG_M->addImage("start_kyoko", "source/image/ui/scene/StartScene_Kyoko.bmp", 550, 828, true, MAGENTA);

	//================= UI =================
	IMG_M->addImage("shadow", "source/image/character/shadow.bmp", 128, 38, true, MAGENTA, true);


	//================= �������� =================
	IMG_M->addImage("easyStage", "source/image/stage/easy.bmp", 2704, 904, false, MAGENTA);
	IMG_M->addImage("normalStage", "source/image/stage/normal.bmp", 3820, 1116, false, MAGENTA);
	IMG_M->addImage("hardStage", "source/image/stage/hard.bmp", 3104, 1904, false, MAGENTA);
	IMG_M->addImage("bossStage", "source/image/stage/boss1.bmp", 2769, 1080, false, MAGENTA);
	IMG_M->addImage("bossStage2", "source/image/stage/boss2.bmp", 2769, 1080, false, MAGENTA);

	//================= �÷��̾� =================
	IMG_M->addFrameImage("kyoko", "source/image/character/player/idle.bmp", 1440, 450, 12, 2,true, MAGENTA, true);

	//================= ���ʹ� =================
	IMG_M->addFrameImage("schoolGirl", "source/image/character/enemy/schoolGirl/idle.bmp", 1170, 354, 10,2,true, MAGENTA, true);

	//================= ������Ʈ =================
	IMG_M->addImage("desk", "source/image/object/desk.bmp", 98, 108, true, MAGENTA, true);

	//================= ������ =================
	IMG_M->addImage("meat", "source/image/item/meat.bmp", 60, 51, true, MAGENTA, true);
}