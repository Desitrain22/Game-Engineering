/// @description Insert description here
// You can write your code in this editor
if (global.key == true)
{
	visible = true;
}

if (place_meeting(x,y,player))
{
	if(global.key)
	{
		IceParticles(x,y, 1000);
	}
	visible = false;
	global.key = false;
}