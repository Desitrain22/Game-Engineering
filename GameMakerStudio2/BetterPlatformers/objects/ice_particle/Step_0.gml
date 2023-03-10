/// @description Insert description here
// You can write your code in this editor
//yspd += grav;

x += xspd;
y += yspd;

image_angle += rot_spd;

image_xscale -= shrink_rate;
image_yscale = image_xscale;

if (image_xscale <= 0)
{
	instance_destroy();
}