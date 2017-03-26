#pragma once
#include <windows.h>
#include <mmsystem.h>
//#include <string>


namespace SoundManager
{
	void PlayHitSound();
	void PlayGunShotSound();
	void PlayPlayerHitSound();
}

namespace Sound
{
	extern LPSTR LaserShot;
	extern LPSTR Explosion;
	extern LPSTR PlayerDead;
	extern LPSTR Swoosh;

}