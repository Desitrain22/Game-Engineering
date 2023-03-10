/// @description Insert description here
// You can write your code in this editor

path_x = target.x;
path_y = target.y;

if (mp_grid_path(MAINGRID, dog_path, x, y, path_x, path_y, true)) {
	path_start(dog_path, mspd, path_action_stop, false);
}