#pragma once

#define CAMERA_VELOCITY 1000
#define CAMERA_ACCELERATION_DECAY 3000

#define GAME_WIDTH 2000
#define GAME_HEIGHT 2000
#define DECELERATE_RANGE 40

#define FPS (1.f / 64)

#define SPACE_STATION_PRICE 100

// -----------------------------------------
//    Game stations (buidling types)
// -----------------------------------------
enum STATION_TYPES {
	SOLAR_STATION,
	LASER_STATION,
	MISSILE_STATION,
};
