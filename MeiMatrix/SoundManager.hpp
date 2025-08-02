#pragma once
#include <miniaudio.h>
#include <string>
namespace MEI
{
	class SoundManager
	{
	private:
		ma_engine engine;

	public:
		SoundManager();
		~SoundManager();
		int init();
		void playMusic(const std::string& filePath);
	};
}