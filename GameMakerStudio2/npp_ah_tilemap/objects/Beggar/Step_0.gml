/// @description Insert description here
// You can write your code in this editor
if place_meeting(x,y+sign(yspd),Wall)
{
	yspd = -yspd;
}

if place_meeting(x+sign(xspd),y,Wall)
{
	xspd *= -1;
}

if place_meeting(x,y,Player)
{
	if (sprite_index!=Sprite11)
	{
		sprite_index = Sprite11;
	}
}
else
{
	if (sprite_index!=Sprite10)
	{
		sprite_index = Sprite10;
	}
	x+=xspd;
	y+=yspd;
}
image_xscale = -sign(xspd);