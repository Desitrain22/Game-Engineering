// Inherit the parent event
event_inherited();

//modify x pos
x += xspd;

bounce_timer --;

if (bounce_timer <= 0){

	//bounce up
	mspd *= -.8;
	//bounce to side
	xspd = random_range(-10,10);
	//reset timer
	bounce_timer = bounce_timer_max;
	
}

