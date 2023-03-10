/// @description Insert description here
// You can write your code in this editor

// Inherit the parent event
event_inherited();

if(dead != true)
{
	if (keyboard_check(vk_left) and acceltimer == 0)
	{
		moveL();
	}
	else if (keyboard_check(vk_right) and acceltimer == 0)
	{
		moveR();
	}
	else if (keyboard_check_pressed(vk_space))
	{
		flap();
		//sprite_index = PlayerFlapHold;
		flapGrav = true;
		audio_play_sound(Flap, 1, false);
	}
	else if (keyboard_check_released(vk_space))
	{
		//sprite_index = PlayerFlap;
		flapGrav = false;
	}		
	if abs(xspd) < 0.001
	{
		sprite_index = PlayerIdle;
	}
}

if (flapGrav and yspd > 0)
{
	yspd -= .07;
}


acceltimer -= 1/60;
acceltimer = max(acceltimer, 0);

global.playerX = x;
global.playerY = y;