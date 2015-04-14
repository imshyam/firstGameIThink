#ifndef __CONFIG_H__
#define __CONFIG_H__


#define BALL_COLLISION_BITMASK 0x000001
#define GROUND_COLLISION_BITMASK 0x000002
#define CPU_P_COLLISION_BITMASK 0x000003
#define USER_P_COLLISION_BITMASK 0x000004

bool notTouchedLeft = true;
bool notTouchedRight  = true;

int ball_velocity_x_initial = 800;
int ball_velocity_y_initial = 700;
int ball_velocity_x = ball_velocity_x_initial;
int ball_velocity_y = ball_velocity_y_initial;
int ball_velocity_min_x = -1700;
int ball_velocity_max_x = 1700;

int cpu_paddle_velocity_x = 500;
int cpu_paddle_min_velocity_x = -1000;
int cpu_paddle_max_velocity_x = 1000;

int user_paddle_velocity_x ;
int user_paddle_velocity_min_x = -1000;
int user_paddle_velocity_max_x = 1000;

bool userWon = false;
bool gamePaused = false;

int gameType=1;


int scoreCpu,scoreUser;


#endif // __CONFIG_H__