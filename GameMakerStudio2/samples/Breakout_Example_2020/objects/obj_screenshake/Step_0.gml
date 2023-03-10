/// @description Insert description here
// You can write your code in this editor
if (shake_timer >0)
{
	shake_x = random_range(-shake_amt, shake_amt);
	shake_y = random_range(-shake_amt, shake_amt);
	
	shake_timer -=1;
}
else
{
	shake_x = 0;
	shake_y = 0;
}

camera_set_view_pos(view_camera[view_current], shake_x, shake_y);