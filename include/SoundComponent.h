#pragma once
#ifndef SOUND_COMPONENT_H
#define SOUND_COMPONENT_H

#include "SDL.h"
#include <string>

class SoundComponent
{
public:
	SoundComponent(std::string filepath);
	~SoundComponent();

	void playSound();
	void stopSound();
	void setupDevice();
	bool isPlaying();

private:
	SDL_AudioDeviceID _device;

	SDL_AudioSpec _audioSpec;
	uint8_t* _waveBuffer;
	uint8_t* _currBuffer;
	uint32_t _waveSize;
	bool _isPlaying;
};

#endif // !SOUND_COMPONENT_H
