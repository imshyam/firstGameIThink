#ifndef __CONFIG_H__
#define __CONFIG_H__

// #define DISPLAY_TIME_SPLASH_SCENE 2
// #define TRANSITION_TIME 0.5
// #define PIPE_SPAWN_FREQUENCY 0.005

// #define PIPE_GAP 10
// #define UPPER_SCREEN_PIPE_THRESHOLD 0.65
// #define LOWER_SCREEN_PIPE_THRESHOLD 0.35

// #define PIPE_MOVEMENT_SPEED 0.01

#define BALL_COLLISION_BITMASK 0x000001
#define GROUND_COLLISION_BITMASK 0x000002
#define CPU_P_COLLISION_BITMASK 0x000003
#define USER_P_COLLISION_BITMASK 0x000004

bool notTouchedLeft = true;
bool notTouchedRight  = true;

int ball_velocity_x = 500;
int ball_velocity_y = 500;
int ball_velocity_min_x = -1000;
int ball_velocity_max_x = 1000;

int cpu_paddle_velocity_x = 500;
int cpu_paddle_min_velocity_x = -700;
int cpu_paddle_max_velocity_x = 700;

int user_paddle_velocity_x ;
int user_paddle_velocity_min_x = -800;
int user_paddle_velocity_max_x = 800;

// #define BIRD_FALLING_SPEED 0.0025
// #define BIRD_FLYING_SPEED 0.00375
//#define BIRD_FLY_DURATION 0.25

#endif // __CONFIG_H__