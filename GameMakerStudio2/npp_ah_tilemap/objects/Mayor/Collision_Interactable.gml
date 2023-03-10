if (collision_line(x, y, bbox_right, y, Interactable))
{
	yspd *= -1
}
else if (instance_place(x, y-1, Interactable))
{
	