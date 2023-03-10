/// @description Insert description here
// You can write your code in this editor

// Inherit the parent event
event_inherited();
function egg()
{
	with (instance_create_depth(x,y,1,Egg))
	{
		xspd = -other.xspd;
		yspd = 0;
	}
	instance_destroy();
}

defaultSprite = EnemySprite;
moveSprite = EnemySprite;
stopSprite = EnemyStop;
flapSprite = EnemyFlap;
flapHold = EnemyFlap;
decel = false;
acceltimer = .15;
alarm[0] = 90;
alarm[4] = 180;