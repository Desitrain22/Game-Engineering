/// @description Insert description here
// You can write your code in this editor
deathtimer = 0;
flapCoolDown = 0;
xPos = 10;
yPos = 10;

defaultSprite = PlayerIdle;
moveSprite = PlayerWalk;
stopSprite = PlayerStop;
flapSprite = PlayerFlap;
flapHold = PlayerFlapHold;

dead = false;

init_movement();

function flap()
{
	if (flapCoolDown < 0)
	{
		yspd = flapacc;
		flapCoolDown = 0.25;
		sprite_index = flapSprite;
	}
	else
	{
		sprite_index = flapHold;
	}		
}

function respawn()
{
	x = xPos;
	y = yPos;
	sprite_index = defaultSprite;
	dead = false;
}

function die()
{
	sprite_index = ost_death;
	xspd = 0;
	yspd = 0;
	deathtimer = 3;
	dead=true;
}

function moveL()
{
	if (place_meeting(x,y+2,Wall))
	{
		if (xspd > 0)
		{
			sprite_index = stopSprite;
			image_xscale = 1;
			decel = true;
		}
		else
		{
			sprite_index = moveSprite;
			image_xscale = 1;
			decel = false;
		}
	}
	xspd -= accel;
	acceltimer = 0.25;
}

function moveR()
{
	if (instance_place(x,y+1.01,Wall))
	{
		if (xspd < 0)
		{
			sprite_index = stopSprite;
			image_xscale = -1;
			decel = true;
		}
		else
		{
			sprite_index = moveSprite;
			image_xscale = -1;
			decel = false;
		}
	}
	xspd += accel;
	acceltimer = 0.25;
}