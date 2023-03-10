/// @description Insert description here
// You can write your code in this editor


if (deathtimer > 0)
{
	deathtimer -= 1/60;
	if deathtimer <= 0
	{
		respawn();
	}
}

if (y < 65)
{
	yspd = 4;
}

yspd+=grav;

flapCoolDown -= 1/60;


if (x > room_width or x < 0)
{
	x -= sign(x) * room_width;
	y -= 2;
}

do_movement();