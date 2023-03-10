/// @description Insert description here
// You can write your code in this editor
xspd = 0;
if (global.playerX > x)
{
	moveR();
	moveR();
}
else
{
	moveL();
	moveL();
}

alarm_set(4, random_range(0,310));