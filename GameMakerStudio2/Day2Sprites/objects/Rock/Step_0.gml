if(gone)
{
	x = 1000;
	y = 1000;
}
else if (y > room_height)
{
	y = 0;
	veloc=0;	
	x = random(room_width);
}
/*else if (place_meeting(x,y,player))
{
	gone = true;
}*/
else
{
	veloc += accel;
	y += veloc;
}

