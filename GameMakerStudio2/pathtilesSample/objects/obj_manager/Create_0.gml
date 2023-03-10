/// @description Insert description here
// You can write your code in this editor

globalvar TILESIZE;
TILESIZE = 16;

globalvar GRID_WIDTH;
globalvar GRID_HEIGHT;

GRID_WIDTH = room_width / TILESIZE;
GRID_HEIGHT = room_height / TILESIZE;

globalvar MAINGRID;
MAINGRID = mp_grid_create(0, 0, GRID_WIDTH, GRID_HEIGHT, TILESIZE, TILESIZE);
alarm[0] = 1;