/// @description Insert description here
// You can write your code in this editor
if (alarm[1] == -1)
{
	xspd = 0.7 * reverse ? -1 : 1;
	if (x<xSet[0])
	{
		sprite_index = Sprite9;
		alarm_set(0, 300);
		xspd = 0;
		reverse = false;
	}
	else if (x > xSet[1])
	{
		sprite_index = Sprite9;
		alarm_set(1,300);
		xspd = 0;
		reverse = true;
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

x+=xspd;
	
