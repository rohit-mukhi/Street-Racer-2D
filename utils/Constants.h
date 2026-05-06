#pragma once
extern int WIN_W;
extern int WIN_H;

const float ROAD_W  = 400.f;
extern float ROAD_LEFT;
extern float ROAD_RIGHT;
const int   NUM_LANES  = 4;
const float LANE_W     = ROAD_W / NUM_LANES;

const float DASH_H   = 30.f;
const float DASH_GAP = 30.f;
const float DASH_W   = 6.f;

const float PLAYER_W   = 40.f;
const float PLAYER_H   = 70.f;
const float PLAYER_SPD = 250.f;

const float ENEMY_W            = 40.f;
const float ENEMY_H            = 70.f;
const float INITIAL_ENEMY_SPD  = 200.f;
const float SPEED_INCREMENT    = 10.f;
const float SPAWN_INTERVAL     = 0.6f;
const float SPEED_BOOST_INTERVAL = 30.f;
const float SPEED_TIME_BOOST     = 50.f;
const float MAX_ENEMY_SPD        = 1200.f;

enum class GameState { Loading, Playing, GameOver };
