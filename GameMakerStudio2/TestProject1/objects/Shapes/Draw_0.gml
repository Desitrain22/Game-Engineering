/// @description Insert description here
// You can write your code in this editor

draw_set_color(c_white);

draw_circle(xPos,yPos,50,false);

draw_set_color(c_fuchsia);

draw_ellipse(200,400+elX, 300,700-elX, false);

//draw_triangle(100,400, 50,550, 150, 550,false)
//draw_triangle(50,550, 100,700,150,550,false)

draw_triangle_color(triX+400,triY+400,triX+350,triY+350,triX+500,triY+250, c_red,c_olive,c_green,false)
