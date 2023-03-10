/// @description Insert description here
// You can write your code in this editor
if (!vert)
{
	if (alarm[1] == -1)
	{
		yspd = 0;
		xspd = 0.7 * reverse ? -1 : 1;
		if (x<xSet[0])
		{
			sprite_index = Sprite3;
			alarm_set(1, 300);
			xspd = 0;
			reverse = false;
		}
		else if (x > xSet[1] and x < xSet[1]+5) and xspd>0
		{
			vert = true;
		}
		else if (x > xSet[2])
		{
			
			sprite_index = Sprite3;
			alarm_set(1,300);
			xspd = 0;
			reverse = true;
		}
	}
	else
	{
		xspd = 0;
		yspd = 0;
	}
	backDown = false;
}
else
{
	xspd = 0;
	yspd = 0.7 * backDown ? 1 : -1;
	
	if (alarm[0] == -1)
	{		
		if (y < ySet[0])
		{
			yspd = 0;
			alarm[0] = 300;
			sprite_index = Sprite3;
			backDown = true;
		}
		else if (y > ySet[1])
		{
			yspd = 0;
			vert = false;
		}
	}
	else
	{		
		yspd = 0;
	}
}
if xspd != 0
{
	image_xscale = sign(xspd);
}
else
{
	image_xscale = 1;
}
x+=xspd
y+=yspd