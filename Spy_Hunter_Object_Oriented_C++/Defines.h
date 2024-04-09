#pragma once

#define BUFFER 100

#define FPS_CAP 60
#define FRAME_DELAY 1000/FPS_CAP

#define TITLE	"Kamil Cwynar 193377 Spy Hunter"
#define INDEX -1

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define SCREEN_DEPTH	32

#define NOT_TURNING 0
#define MOVE_LEFT -4
#define MOVE_RIGHT 4

#define RED_DRAWING_VALUE 255
#define GREEN_DRAWING_VALUE 255
#define BLUE_DRAWING_VALUE 255
#define ALPHA_DRAWING_VALUE 255

#define MIN_SPEED 1
#define DEFAULT_SPEED 2
#define MAX_SPEED 4

#define GRASS 1
#define ROAD 2
#define BORDER 3
#define LINE 4 
#define FLAGS 0
#define OBSTACLE 5

#define LEFT_BORDER 5
#define RIGHT_BORDER 34
#define TILE_SIZE 16
#define LINE_LENGTH 40
#define LINE_START_MIN 3
#define LINE_START_MAX LINE_LENGTH - LINE_START_MIN
#define LINE_START 0
#define NEW_LINE 0
#define LAYOUT_LINES_COUNT 29
#define INIT_ROAD_START 8
#define INIT_ROAD_WIDTH 20
#define CAR_FRONT 18
#define CAR_REAR 24
#define RANDOM_INT_FROM_NEGATIVE_ZERO_TO_TEN ((rand() % 100) % 11)
#define MIN_ROAD_WIDTH 16
#define MAX_ROAD_WIDTH 26

#define MIN_OBSTACLE_RESPAWN_TIME 10

#define LASER_SPEED 10

#define MAX_AMMO 3
#define RELOAD_TIME 60
#define AMMO_INTERFACE_X 520
#define AMMO_INTERFACE_Y 440

#define INCREASE 1
#define DECREASE -1
#define SPAWN_POINT_X	(roadStartFront + (roadWidthFront + roadStartFront))/2 * TILE_SIZE - CAR_SIZE_X / 2
#define SPAWN_POINT_Y	300
#define CAR_BORDER_LEFT   destR.x
#define CAR_BORDER_RIGHT  destR.x + 64
#define CAR_SIZE_Y 128
#define CAR_SIZE_X 64

#define KEY 0x000000
#define RGB_BLACK 0x00, 0x00, 0x00
#define RGB_RED 0xFF, 0x00, 0x00
#define RED_MASK 0x00FF0000
#define GREEN_MASK 0x0000FF00
#define BLUE_MASK 0x000000FF
#define ALPHA_MASK 0xFF000000 

#define RECT_DEST_Y 0
#define RECT_DEST_X 0
#define RECT_SIZE_Y 80
#define RECT_SIZE_X 640

#define INFO_RECT_DEST_Y 420
#define INFO_RECT_DEST_X 460
#define INFO_RECT_SIZE_Y 60
#define INFO_RECT_SIZE_X 180

#define GAME_TIME timeCount / 60, (timeCount / 6) % 10

#define GAME_INFO_AFTER_IMMUNITY "time - %d,%d score - %d, lifes - %d, +life in %d points"
#define GAME_INFO_BEFORE_IMMUNITY "time - %d,%ds score - %d, lifes - infinite for %d,%ds"
#define GAME_OVER_MESSAGE "GAME OVER"
#define GAME_OVER_INFO "final score - %d, time - %d,%ds"
#define GAME_OVER_INSTRUCTIONS "Esc - exit, N - new game"
#define INPUT_INSTRUCTION_1 "Esc - exit, N - new game, F - end game, P - pause, E - Shoot "
#define INPUT_INSTRUCTION_2 "\030 - speeding up, \031 - slowing down, \032 - moving left, \033 - moving right"
#define IMPLEMENTED_ELEMNETS_TEXT_1 "implemented elements:"
#define IMPLEMENTED_ELEMNETS_TEXT_2 "all mandatory + i) m)"

#define INPUT_INSTRUCTION_X 10
#define INPUT_INSTRUCTION_Y 20
#define GAME_INFO_X 10
#define GAME_INFO_Y 60
#define IMPLEMENTED_ELEMENTS_INFO_X 460
#define IMPLEMENTED_ELEMENTS_INFO_Y 440
#define SPACE_BETWEEN_LINES 20

#define SCORE_NEEDED_FOR_EXTRA_LIFE 50000
#define IMMUNITY_TIME 300 
#define IMMUNITY_TIME_LEFT player->immunityTimeLeft() / 60, (player->immunityTimeLeft() / 6) % 10
#define LIFES_CAP 3
#define TENTH_OF_A_SECOND_HAS_PASSED !(timeCount % 6)

#define CHARSET_PATH "./cs8x8.bmp"
#define CAR_IMAGE_PATH "car.bmp"