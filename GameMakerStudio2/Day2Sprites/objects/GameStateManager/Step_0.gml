/// @description Insert description here
// You can write your code in this editor

if (keyboard_check_pressed(vk_space))
{
	if (room == rm_end)
	{
		room_goto(1);
	}
	else if (room == rm_start)
	{
		room_goto_next();
	}
} 
