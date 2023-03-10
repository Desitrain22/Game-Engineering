/// @description Insert description here
// You can write your code in this editor
if (xPos<350-(50/sqrt(2))) //350 is center of circle, 50/root(2) is the x and y
//components of the 45 degree edge of the circle
{
	xPos+=1
}
else
{
	if !(triX>=500) //After the ball 'bumpbs' the triangle, it will slide to the t
	//op of the screen, hit the top, and continue right a bit
	{
		triX+=1
	}
}

if (yPos<350-(50/sqrt(2)))
{
	yPos+=1
}
else
{
	if (triX >= 500) //once we hit the edge, we falllllll
	{
		if (triY <= 300)
		{
			triY+=4
		}
		else
		{
			triY=0;
			triX=0;
			xPos=100;
			yPos=100;
		}
	}
	else if (triY>-250)
	{
		triY-=1
	}
}
tick+=1;
if (tick<300)
{
	elX += (1/2) * 0.005 * ((tick)^2);
}
else if (tick < 500)
{
	elX -= (1/2) * 0.005 * ((300-tick)^2);
}
