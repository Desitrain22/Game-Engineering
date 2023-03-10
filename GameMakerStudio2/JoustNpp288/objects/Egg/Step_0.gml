/// @description Insert description here
// You can write your code in this editor
timer -= 1/60;

if timer <= 0
{
	instance_create_depth(x,y-20,1,Enemy);
	instance_destroy();
}

yspd += grav;
do_movement()