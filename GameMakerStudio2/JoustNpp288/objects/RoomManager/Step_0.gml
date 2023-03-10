/// @description Insert description here
// You can write your code in this editor


if (global.playerLives == 0)
{
	lose();
}

if (room == Start)
{
	if (keyboard_check(vk_space))
	{
		room_goto(Room1);
	}
}

if (room == Room2)
{
	if (keyboard_check(vk_enter))
	{
		room_goto(Start);
	}
}

if (keyboard_check(ord("R")))
{
	room_goto(Start);
}