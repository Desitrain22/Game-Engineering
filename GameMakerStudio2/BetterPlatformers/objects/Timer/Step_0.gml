/// @description Insert description here
// You can write your code in this editor
ydir = (ytimer%60==0) ? -ydir : ydir;
y += .25*ydir;
ytimer += 1;

if (place_meeting(x,y,player))
{
	if(visible)
	{
		visible = false;
		global.enemyActive = false;
		timerStart = true;
	}
}

if(timerStart)
{
	invisTimer += 1;
	if (invisTimer >= 600)
	{
		visible = true;
		global.enemyActive = true;
		timerStart = false;
		invisTimer = 0;
	}
}