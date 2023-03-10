/// @description Insert description here
// You can write your code in this editor

// Inherit the parent event
event_inherited();

xPos=x;
yPos=y;
if(dead and deathtimer <= 1/60)
{
	egg();
}

if (place_meeting(x,y+1, Wall))
{
	//sprite_index = EnemySprite;
	if (xspd > 0)
	{
		image_xscale = -1;
	}
	else
	{
		image_xscale = 1;
	}
}

if place_meeting(x,y+2, Wall)
{
	sprite_index = EnemySprite;
}
else
{
	sprite_index = EnemyFlap;
}

acceltimer -= 1/60;
acceltimer = max(acceltimer, 0);