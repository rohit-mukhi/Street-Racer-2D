#pragma once

// Window — set at runtime from desktop resolution in main.cpp
extern int WIN_W;
extern int WIN_H;

// Road — ROAD_LEFT/RIGHT are computed at runtime in main.cpp after WIN_W is known
const float ROAD_W  = 400.f;   // fixed road width in pixels
extern float ROAD_LEFT;
extern float ROAD_RIGHT;
const int   NUM_LANES  = 4;
const float LANE_W     = ROAD_W / NUM_LANES;

// Lane divider dashes
const float DASH_H   = 30.f;
const float DASH_GAP = 30.f;
const float DASH_W   = 6.f;

// Player
const float PLAYER_W   = 40.f;
const float PLAYER_H   = 70.f;
const float PLAYER_SPD = 250.f;

// Enemy
const float ENEMY_W            = 40.f;
const float ENEMY_H            = 70.f;
const float INITIAL_ENEMY_SPD  = 200.f;
const float SPEED_INCREMENT    = 10.f;
const float SPAWN_INTERVAL     = 1.2f;
const float SPEED_BOOST_INTERVAL = 30.f;   // seconds between time-based speed boosts
const float SPEED_TIME_BOOST     = 50.f;   // px/s added every 30 seconds
const float MAX_ENEMY_SPD        = 600.f;  // speed is capped at this value

// Game states
enum class GameState { Loading, Playing, GameOver };
