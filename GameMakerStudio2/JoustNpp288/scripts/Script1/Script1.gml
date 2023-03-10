// Script assets have changed for v2.3.0 see
// https://help.yoyogames.com/hc/en-us/articles/360005277377 for more information
function init_movement(){
	xspd = 0;
	yspd = 0;
	flapacc = -2.5;
	accel = 1.5;
	grav = .098;
	xbump = false;
	max_spd = 6;
	
	decel  = false;
	acceltimer = 0;
	isEgg = false;
}


function do_movement()
{
	if (isEgg and place_meeting(x, y+2, Wall))
	{
		//bounce
		//I probably could've just made this a seperate script for the egg
		//whoops
		//anyway here's wonderwall:
		if (yspd <= .5)
		{
			yspd = 0;
		}
		else
		{
			yspd *= -0.5;
		}
		if (abs(xspd) > 0.25)
		{
			xspd -= sign(xspd) * 0.5;
		}
		else
		{
			xspd = 0;
		}
	}

	for (var i = 0; i < abs(xspd); i++)
	{
		if (not place_meeting(x+sign(xspd), y, Wall))
		{
			x += sign(xspd);
		}
		else
		{			
			xspd = sign(xspd) * 0.00001;
			xbump = true;
			break;
		}
		
		if (decel)
		{
			xspd *= 0.9;
		}
		
		xspd = clamp(xspd, -max_spd, max_spd);
	}
	
	for (var j = 0; j < abs(yspd); j++)
	{
		if (not place_meeting(x, y+ 2*sign(yspd), Wall))
		{
			y += sign(yspd);
		}
		else
		{
			if (!isEgg)
			{
				yspd = 0;
			}
			break;
		}
	}
}