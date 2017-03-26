#include "SoundManager.h"

namespace Sound
{
	LPSTR LaserShot = "Audio\\LaserShot.WAV";
	LPSTR Explosion = "Audio\\boom.WAV";
	LPSTR PlayerDead = "Audio\\playerDED.WAV";
	LPSTR Swoosh = "Audio\\swoosh.WAV";
}


namespace SoundManager
{
	using namespace Sound;

	void PlayHitSound() {
		PlaySound(TEXT(Explosion), NULL, SND_ASYNC);
	}

	void PlayPlayerHitSound() {
		PlaySound(TEXT(PlayerDead), NULL, SND_ASYNC);
	}
	void PlayGunShotSound() {
		PlaySound(TEXT(LaserShot), NULL, SND_ASYNC);
	}

}

