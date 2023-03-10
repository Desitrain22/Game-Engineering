/// @description Insert description here
// You can write your code in this editor
if (alarm[1] == -1)
{
	global.eggs += 1;	
	global.eggs = min(global.eggs, 4);
	global.userScore += global.eggs * 250;
	global.numEnemies -= 1;
	instance_destroy();
	audio_play_sound(Eggquire,1,false);
}