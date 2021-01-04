#pragma once
#include "singletonBase.h"
#include <map>

#include "Plugins/inc/fmod.hpp"
#pragma comment(lib, "Plugins/lib/fmodex64_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

enum tagVolumeType
{
    MUSIC,
    SFX,
    DIALOGUE
};
//===============================channel �ε��� ����===============================//
// 0 �� ä��------------------->BGM (���)
// 1 �� ä��------------------->DIALOGUE (��ȭ)
//================================================================================//

//===============================SFX Channel�� ���� ����°� ���� ��?===============================//
// 0 �� ä�κ���~~ ------------------->SFX (ȿ����)
//================================================================================//

class soundManager : public singletonBase<soundManager>
{
private:
    typedef map<string, Sound**>                    arrSounds;
    typedef map<string, Sound**>::iterator          arrSoundsIter;

    typedef map<string, Channel**>                  arrChannels;
    typedef map<string, Channel**>::iterator        arrChannelsIter;
private:
    System*                 _system;
    Sound**                 _sound;

    Channel**               _channel;
    Channel**               _sfxChannel;
    arrSounds               _mTotalSounds;
    arrChannels             _mTotalChannels;

	float _masterVolume;
	float _musicVolume;
	float _dialogueVolume;
	float _sfxVolume;
	
public:         
    soundManager();
    ~soundManager();

    HRESULT init();
    void release();
    void update();

    void addSound(string keyName, string soundName, tagVolumeType volumeType, bool loop);

                                // volume 0.0f ~ 1.0f
    void play(string keyName, float volume = 1.0f);

	//============����?============//
    void playMusic(string keyName, float volume = 1.0f); // �갡 ��� ���
    void playDialogue(string keyName, float volume = 1.0f); // �갡 ��ȭ ���
    void playSFX(string keyName, float volume = 1.0f); // �갡 ȿ���� ���

	void setVolumeMaster(float volume); // ������ ����
    void setVolumeMusic(float volume);
    void setVolumeDialogue(float volume);
    void setVolumeSFX(float volume);

    void stop(string keyName);
    void pause(string keyName);
    void resume(string keyName);

    bool isPlaySound(string keyName);
    bool isPauseSound(string keyName);

};

