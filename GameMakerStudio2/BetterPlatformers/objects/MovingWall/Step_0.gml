/// @description Insert description here
// You can write your code in this editor
event_inherited()

for (i =0; i< sprite_width;i++)
{
	if (position_meeting(x+i,y, player) and yMove<0)
	{
		player.y+=yMove;
		break;
	}
}
if (timer < 150)
{
	y+=yMove;
}
else
{
	yMove = -yMove;
	timer = 0;
}
timer += 1