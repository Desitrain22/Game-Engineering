/// @description Insert description here
// You can write your code in this editor
if (dead)
{
	dead_timer += 1;
	if dead_timer > dead_timer_max
	{
		dead_timer = 0;
		dead = false;
		x = room_width/2;
		y = room_height*0.75;
		with(Rock)
		{
			y = random_range(-room_height, 0);
			veloc = 0;
			x = random_range(0, room_width);
		}
	}
}
else if !(place_meeting(x,y, Rock))
{
	SCORE += (1/60);
	if (keyboard_check(vk_right) && x < room_width)
	{
		x+=mspeed;
	}
	if (keyboard_check(vk_left) && x > 0)
	{
		x-=mspeed;
	}
	if (keyboard_check(vk_up)&& y > 0)
	{
		y-=mspeed;
	}
	if (keyboard_check(vk_down) && y < room_height)
	{
		y+= mspeed;
	}
}
else
{
	dead = true;
	LIFE -= 1;
		if (LIFE == 0)
		{
			room_goto_next();
		}
}

