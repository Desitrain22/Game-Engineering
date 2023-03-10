/// @description Insert description here
// You can write your code in this editor
sprite_index = Sprite3_moving;
if (place_meeting(x,y, goal))
{
	audio_play_sound(dub, 1, false);
	room_goto_next();
}

else if !(place_meeting(x,y, Lava))
{
	global.TIME += (1/60);
	if (keyboard_check(vk_right) && x < room_width)
	{
		x+=xspeed;
		if (image_xscale < 0)
		{
			image_xscale *= -1;
		}		
		
	}
	if (keyboard_check(vk_left) && x > 0)
	{
		x-=xspeed;
		if (image_xscale >0)
		{
			image_xscale *= -1;
		}
	}
	if !(keyboard_check(vk_left) || keyboard_check(vk_right))
	{
		sprite_index = Sprite3_Idle;
	}
	
	yspeed += grav;
	
	if !(place_meeting(x,y+1, Floor))
	{
		y += yspeed;
	}
	else
	{
		yspeed = 0;
		var grnd = (instance_place(x, y+1, Floor));
		y = grnd.y;// - 128;
		
		if (keyboard_check(vk_space))
		{
			yspeed = -10;
			audio_play_sound(bounce, 1, false);
		}
		y += yspeed;
	}
}
else
{
	global.DEAD = true;
	room_goto_next();
	audio_play_sound(downbad,1,false);
}

