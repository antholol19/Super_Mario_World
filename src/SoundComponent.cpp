#include "SoundComponent.h"

SoundComponent::SoundComponent(std::string filepath)
{
	_isPlaying = false;
	if (SDL_LoadWAV(filepath.c_str(), &_audioSpec, &_waveBuffer, &_waveSize) == nullptr)
	{
		printf("SDL could not load sound, SDL_Error: %s\n", SDL_GetError());
	}
	_currBuffer = _waveBuffer;
}

SoundComponent::~SoundComponent()
{
	SDL_FreeWAV(_waveBuffer);
	SDL_CloseAudioDevice(_device);
}

void SoundComponent::playSound()
{
	// Queue the audio
	int status = SDL_QueueAudio(_device, _waveBuffer, _waveSize);
	SDL_PauseAudioDevice(_device, 0);
	_isPlaying = true;
}

void SoundComponent::stopSound()
{
	SDL_PauseAudioDevice(_device, 1);
	_isPlaying = false;
}

void SoundComponent::setupDevice()
{
	_device = SDL_OpenAudioDevice(nullptr, 0, &_audioSpec, nullptr, 0);

	if (0 == _device)
	{
		printf("SDL could not setup sound device, SDL_Error: %s\n", SDL_GetError());
	}
}

bool SoundComponent::isPlaying()
{
	return _isPlaying;
}