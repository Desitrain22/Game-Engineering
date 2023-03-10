/// @description Insert description here
// You can write your code in this editor

if (keyboard_check_pressed(vk_space))
{
	if (room == EndGame)
	{
		room_goto(0);
	}
	else if (room == StartScreen)
	{
		
	global.DEAD = false;
	global.LAVAY = 704;
	global.TIME = 0;
		room_goto_next();
	}
}
if (room == Game)
{
	if !(audio_is_playing(bgmusic))
	{
		audio_play_sound(bgmusic, 1, true);
	}
	TIME += 1/60;
	if (TIME > nextTime)
	{
		for (var i = 0; i < 1366; i += 64)
		{
			instance_create_depth(i, global.LAVAY ,0, Lava);
		}
		nextTime += 4;
	}
}
if (room == EndGame)
{
	if (audio_is_playing(bgmusic))
	{
		audio_stop_sound(bgmusic);
	}
	
	if (global.DEAD == true)
	{
		if !(audio_is_playing(downbad))
		{
			audio_play_sound(downbad, 1, false);
		}
	}
	else
	{
		if !(audio_is_playing(dub))
		{
			audio_play_sound(dub, 1, false);
		}
	}
}
