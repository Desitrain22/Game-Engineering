function init_movement(){
	xspd = 0;
	yspd = 0;
	jump_str = 5;
	
	accel = .18;
	grav = .098;
	xbump = false;
	max_spd = 10;
}


function do_movement()
{
	for (var i = 0; i < abs(xspd); i++)
	{
		if (not place_meeting(x+sign(xspd), y, wall))
		{
			x += sign(xspd);
		}
		else
		{			
			xspd = sign(xspd) * 0.00001;
			xbump = true;
			break;
		}
	}
	
	for (var j = 0; j < abs(yspd); j++)
	{
		if (not place_meeting(x, y+sign(yspd), wall))
		{
			y += sign(yspd);
		}
		else
		{
			yspd = 0;
			break;
		}
	}
}