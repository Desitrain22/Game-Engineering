/// @description Insert description here
// You can write your code in this editor
if (room == Start)
{
	if (keyboard_check(vk_space))
	{
		global.tries = 3;
		global.dead = false;
		room_goto(Level1);
	}
	else if (keyboard_check(ord("1")))
	{
		global.tries = 3;
		global.dead = false;
		room_goto(Level1);
	}
	else if (keyboard_check(ord("2")))
	{
		global.tries = 3;
		global.dead = false;
		room_goto(Level2);
	}
	else if (keyboard_check(ord("3")))
	{
		global.tries = 3;
		global.dead = false;
		room_goto(Level3);
	}
		
}
else if (room == End || room == End2)
{
	if (keyboard_check(vk_enter))
	{
		global.tries = 3;
		global.dead = false;
		room_goto(Start);
	}
}
else
{
	if !(global.enemyActive)
	{
		countdown -= 1/60;
	}
	else
	{
		countdown = 10;
	}
}