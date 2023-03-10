/// @description Insert description here
// You can write your code in this editor

if (hit)
{
	block_health -= 1
	hit = false
}

if block_health<1{
	Spawn_Particles(x,y, 2000);
	instance_destroy()	
}