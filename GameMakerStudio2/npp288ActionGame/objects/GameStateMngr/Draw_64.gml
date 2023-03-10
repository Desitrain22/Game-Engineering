/// @description Insert description here
// You can write your code in this editor
if (room == StartScreen)
{
	audio_stop_all();
	draw_text(20,100,"Welcome to 'Sink or Simp'")
	draw_text(20,120,"Press Space to Start")
	draw_text(20,140,"Arrow Keys: Move")
	draw_text(20,160,"Space Bar: Jump")
}
else if (room == EndGame)
{
	if (DEAD)
	{
		draw_text(40,100,"You died! Press Space to Try again");
	}
	else
	{
		draw_text(40,100,"Success! Time: " + string(TIME));
	}
}
else
{
	draw_text(20,100, "Time Elapsed: " + string(TIME));
}
	