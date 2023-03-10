/// @description Insert description here
// You can write your code in this editor

global.numEnemies = 1;
state = 1
coords = [[64,54],[1267,54],[1329,340],[480,440],[700,440]];
global.playerLives = 5;

function lose()
{
	room_goto(Room2);
	global.playerLives = 5;
}

function setStage()
{
	state += 1;
	if state == 1
	{
		global.numEnemies= 2;
	}

	if state == 2
	{
		global.numEnemies = 3;
	}

	if state >= 3
	{
		global.numEnemies = 5;
		global.numEnemies += (state-3);
	}
	
	for (var i = 0; i < global.numEnemies; i++)
	{
		index = random_range(0,4);
		instance_create_depth(coords[index][0], coords[index][1], 1, Enemy);
	}	
}