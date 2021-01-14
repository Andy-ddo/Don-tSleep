#include "stdafx.h"
#include "soundManager.h"

soundManager::soundManager()
    : _system(nullptr),
    _channel(nullptr),
    _sound(nullptr)
{
}

soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
    // FMOD ���� �ʱ�ȭ
    System_Create(&_system);

    // system �ʱ�ȭ
    _system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

    // ���� ä�� ����
    _sound = new Sound*[TOTALSOUNDBUFFER];
    _channel = new Channel*[2]; // ������ �迭
    _sfxChannel = new Channel*[TOTALSOUNDBUFFER];

    // �޸� ���� �Ҵ�
    memset(_sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
    memset(_channel, 0, sizeof(Channel*) * 2);
    memset(_sfxChannel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);

	_masterVolume = 1.0f;
	_musicVolume = 1.0f;
	_dialogueVolume = 1.0f;
	_sfxVolume = 1.0f;
    return S_OK;
}

void soundManager::release()
{
    if (_system != nullptr)
    {
        _system->release();
        _system->close();
    }

    /*
	delete[] _sound;
    delete[] _channel;
    delete[] _sfxChannel;
	*/
}

void soundManager::update()
{
    _system->update();
}

void soundManager::addSound(string keyName, string soundName, tagVolumeType volumeType, bool loop)
{
    if (loop)
    {
        switch (volumeType)
        {
		case tagVolumeType::SFX:
            _system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
            break;
        case tagVolumeType::DIALOGUE: case  tagVolumeType::MUSIC: default:
            _system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
            break;
        }
    }
    else
    {
        switch (volumeType)
        {
        case  tagVolumeType::SFX:
            _system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
            break;
        case  tagVolumeType::DIALOGUE: case tagVolumeType::MUSIC: default:
            _system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
            break;
        }
    }
    _mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()])); // ������ �迭�� ����ִ� �ش� �������� �ּҰ�
    
}


void soundManager::play(string keyName, float volume)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            // ���尡 ��� ����Ϸ��µ� ����� �ȳ��´� ������ FMOD_CHANNEL_FREE�� �ٲ㼭!
            _system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

            _channel[count]->setVolume(volume);
            break;
        }
    }
}

void soundManager::playMusic(string keyName, float volume)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    for (iter; iter != _mTotalSounds.end(); ++iter)
    {
        if (keyName == iter->first)
        {
            _channel[0]->stop();
            // ���尡 ��� ����Ϸ��µ� ����� �ȳ��´� ������ FMOD_CHANNEL_FREE�� �ٲ㼭!
            _system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[0]);
            _channel[0]->setVolume(volume);
            break;
        }
    }
}

void soundManager::playDialogue(string keyName, float volume)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    for (iter; iter != _mTotalSounds.end(); ++iter)
    {
        if (keyName == iter->first)
        {
            _channel[1]->stop();
            // ���尡 ��� ����Ϸ��µ� ����� �ȳ��´� ������ FMOD_CHANNEL_FREE�� �ٲ㼭!
            _system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[1]);
            _channel[1]->setVolume(volume);
            break;
        }
    }
}

void soundManager::playSFX(string keyName, float volume)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            // ���尡 ��� ����Ϸ��µ� ����� �ȳ��´� ������ FMOD_CHANNEL_FREE�� �ٲ㼭!
            _system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_sfxChannel[count]);
            _sfxChannel[count]->setVolume(volume);
            break;
        }
    }
}

void soundManager::setVolumeMaster(float volume)
{
	_masterVolume = volume;
	

	setVolumeMusic(_musicVolume);
	setVolumeDialogue(_dialogueVolume);
	setVolumeSFX(_sfxVolume);
}

void soundManager::setVolumeMusic(float volume)
{
	_musicVolume = volume;
    _channel[0]->setVolume(_masterVolume * _musicVolume);
}

void soundManager::setVolumeDialogue(float volume)
{
	_dialogueVolume = volume;
    _channel[1]->setVolume(_masterVolume * _dialogueVolume);
}

void soundManager::setVolumeSFX(float volume)
{
	_sfxVolume = volume;
    for (int i = 0; i < TOTALSOUNDBUFFER; ++i)
    {
        _sfxChannel[i]->setVolume(_masterVolume * _sfxVolume);
    }
}

void soundManager::stopMusic(string keyName)
{
	_channel[0]->stop();
}

void soundManager::pauseMusic(string keyName)
{
	_channel[0]->setPaused(true);
}

void soundManager::resumeMusic(string keyName)
{
	_channel[0]->setPaused(false);
}

void soundManager::stop(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->stop();
            break;
        }
    }
}

void soundManager::pause(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();
    int count = 0;
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->setPaused(true);
            break;
        }
    }
}

void soundManager::resume(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->setPaused(false);
            break;
        }
    }
}

bool soundManager::isPlaySound(string keyName)
{
    bool isPlay;
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->isPlaying(&isPlay);
            break;
        }
    }
    return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
    bool isPause;
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->getPaused(&isPause);
            break;
        }
    }
    return isPause;

}
