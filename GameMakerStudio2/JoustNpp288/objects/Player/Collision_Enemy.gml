/// @description Insert description here
// You can write your code in this editor
target = instance_place(x,y, Enemy);
if (target.sprite_index != ost_death and self.dead = false)
{
	if target.y < y
	{
		self.die();
		global.playerLives-=1;
		index = random_range(0,3);
		self.xPos = positions[index][0];
		self.yPos = positions[index][1];
	}
	else if target.y > y
	{
		target.egg();
		global.userScore += 500;
	}
	else
	{
		temp = sign(x - target.x);
		self.xspd = temp * 3;
		target.xspd = -1 * self.xspd;
	}
}