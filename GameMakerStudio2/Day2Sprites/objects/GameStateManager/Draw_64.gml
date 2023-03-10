/// @description Insert description here
// You can write your code in this editor
if (room == Room1)
{
	draw_text(20,20, "SCORE: " + string(SCORE));
	draw_text(20,40, "LIVES: " + string(LIFE));
}
else
{
	if (room == rm_end)
	{
		draw_text(20, 250, "YOU LOSE. SCORE: " + string(SCORE));
	}
	draw_text(20, 300, "PRESS SPACE TO START");
	if (room == rm_start)
	{
		LIFE = 3;
		SCORE = 0;
	}
}