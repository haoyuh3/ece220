/*									tab:8
 *
 * main.c - skeleton source file for ECE220 picture drawing program
 *
 * "Copyright (c) 2018 by Charles H. Zega, and Saransh Sinha."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Charles Zega, Saransh Sinha
 * Version:	    1
 * Creation Date:   12 February 2018
 * Filename:	    mp5.h
 * History:
 *	CZ	1	12 February 2018
 *		First written.
 */
#include "mp5.h"

/*
	You must write all your code only in this file, for all the functions!
*/



/* 
 *  near_horizontal
 *	 
 *	 
 *	
 *	
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */
//this part is used to print horizontal line first we need to decide which point is start and end because we need to loop the point
// I use res in my code to decide whether the point is valid

//if the slope is smaller than 1 then print horizontal line use the formula to get the x and y and loop x
// compare x to get sgn
int32_t
near_horizontal(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
    int32_t res=1; //res initialize to 1 because we want to see whther it is zero in the end
	int x,y;
	int32_t sgn;
	int32_t s;
	int32_t x1 =x_start;
	int32_t x2= x_end;
	int32_t y1= y_start;
	int32_t y2= y_end;
	if (x2<x1){  //used to decide which is start and end 
		s=x2;x2=x1;x1=s;
        s=y2; y2=y1; y1=s;	
	}
	if (y2-y1>0){sgn=1;}
	if (y2-y1==0){sgn=0;}
	if (y2-y1<0){sgn=-1;}
	
	for (int32_t i =0; i<= x2-x1; i++){
		x=i+x1;
		y=y1+ (2*(y2-y1)*(x-x1)+(x2-x1)*sgn)/(2*(x2-x1));
		res &=draw_dot(x,y);
	}



	return res;
}


/* 
 *  near_vertical
 *	 
 *	 
 *	
 *	
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */
//similar to horizontal function
//return res to determine whether it is valid
int32_t
near_vertical(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
    int32_t res=1;
	int32_t x,y;
	int32_t sgn=0;
	int32_t s;
	int32_t x1 =x_start;
	int32_t x2= x_end;
	int32_t y1= y_start;
	int32_t y2= y_end;
	if (y2<y1){
		s=x2;x2=x1;x1=s;
        s=y2; y2=y1; y1=s;	
	}
	if (x2-x1>0){sgn=1;}
	else {sgn=-1;}
		for (int32_t i =0; i<= y2-y1; i++){
		y=i+y1;
		x=x1+ (2*(x2-x1)*(y-y1)+(y2-y1)*sgn)/(2*(y2-y1)); 
		res &=draw_dot(x,y);
	}


	return res;
}

/* 
 *  draw_line
 *	 
 *	 
 *	
 *	
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */
//we first need to get slope and choose which pattern we need;
int32_t
draw_line(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int32_t res=1;
    int32_t dy=y_end-y_start;
	int32_t dx=x_end-x_start;
	if (dy<0) dy=-dy;
	if (dx<0) dx=-dx; // in this part I compare dy and dx to compare with 1
	if (dy>dx) res &=near_vertical(x_start, y_start,x_end,y_end);
	else res &= near_horizontal(x_start, y_start,x_end,y_end);

	return res;
}


/* 
 *  draw_rect
 *	 
 *	 
 *	
 *	
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 * OUTPUTS: draws a pixel to every point of the edges of the rectangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */
// from one point we can get four point by adding w and h and we can get four points and use draw line
// calll draw_line to connect points
int32_t
draw_rect(int32_t x, int32_t y, int32_t w, int32_t h){
	/* Your code goes here! */
	int32_t res=1;
    int32_t x_topright,y_topright;
	int32_t x_downleft, x_downright,y_downleft,y_downright;
	x_topright=x+w, y_topright=y;
    x_downleft=x, y_downleft=y+h;
	x_downright=x+w,y_downright=y+h;
    res &= draw_line(x,y,x_topright,y_topright);
	res &= draw_line(x,y,x_downleft,y_downleft);
	res &= draw_line(x_topright,y_topright,x_downright,y_downright);
	res &= draw_line(x_downleft,y_downleft,x_downright,y_downright);

	return res;
}


/* 
 *  draw_triangle
 *	 
 *	 
 *	
 *	
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the triangle
 *         x_B,y_B -- the coordinates of another of the vertices of the triangle
 *         x_C,y_C -- the coordinates of the final of the vertices of the triangle
 * OUTPUTS: draws a pixel to every point of the edges of the triangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */
// we have been given three points we just need to use draw_line to connect three line
// calll draw_line to connect points
int32_t
draw_triangle(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	/* Your code goes here! */
    int32_t res=1;
	res &=draw_line(x_A,y_A,x_B,y_B);
	res &=draw_line(x_B,y_B,x_C,y_C);
    res &=draw_line(x_A,y_A,x_C,y_C);

	return res;
}

/* 
 *  draw_parallelogram
 *	 
 *	 
 *	
 *	
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the parallelogram
 *         x_B,y_B -- the coordinates of another of the vertices of the parallelogram
 *         x_C,y_C -- the coordinates of another of the vertices of the parallelogram
 * OUTPUTS: draws a pixel to every point of the edges of the parallelogram
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */
// we know that the parallelogram have properties that x_D=-x_B+x_C+x_A, y_D=-y_B+y_C+y_A
int32_t
draw_parallelogram(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	/* Your code goes here! */
    int32_t x_D;
    int32_t y_D;
	int32_t res=1;
    x_D=-x_B+x_C+x_A, y_D=-y_B+y_C+y_A; // to get points
    res &= draw_line(x_A,y_A,x_B,y_B);
	res &= draw_line(x_A,y_A,x_D,y_D);
	res &= draw_line(x_B,y_B,x_C,y_C);
	res &= draw_line(x_C,y_C,x_D,y_D);

	return res;
}


/* 
 *  draw_circle
 *	 
 *	 
 *	
 *	
 * INPUTS: x,y -- the center of the circle
 *         inner_r,outer_r -- the inner and outer radius of the circle
 * OUTPUTS: draws a pixel to every point whose distance from the center is
 * 	    greater than or equal to inner_r and less than or equal to outer_r
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */
// find the points taht is between inner radius and outer;
// d= x^2+y^2
int32_t
draw_circle(int32_t x, int32_t y, int32_t inner_r, int32_t outer_r){
	/* Your code goes here!*/
    int32_t res=1;
	int32_t i;
	int32_t j;
	if (outer_r<inner_r){return 0;} // invalid
	for (i=x-outer_r;i<=x+outer_r;i++){
		for (j=y-outer_r;j<=y+outer_r;j++){
			if ((i-x)*(i-x)+(j-y)*(j-y)<=outer_r*outer_r && (i-x)*(i-x)+(j-y)*(j-y)>=inner_r*inner_r) {res &= draw_dot(i,j);}//distance is ((i-x)*(i-x)+(j-y)*(j-y)
		}
	}
	return res;
}


/* 
 *  rect_gradient
 *	 
 *	 
 *	
 *	
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 *         start_color -- the color of the far left side of the rectangle
 *         end_color -- the color of the far right side of the rectangle
 * OUTPUTS: fills every pixel within the bounds of the rectangle with a color
 *	    based on its position within the rectangle and the difference in
 *          color between start_color and end_color
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */
// the color should be represented as hex we use shift right to get the num of  r, g, b and use formula to get correspondence r g b
// and finally get final color.
int32_t
rect_gradient(int32_t x, int32_t y, int32_t w, int32_t h, int32_t start_color, int32_t end_color){
	/* Your code goes here! */
    int32_t res=1;
	int32_t level1,level2,level3;
	if (w<1 || h<0){return 0;}
	int32_t r1,r2,g1,g2,b1,b2;
	r1= start_color/(256*256)%256, r2 =end_color/(256*256)%256; // rgb can represent in hex and first 8 represent r and so on 
	g1=start_color/256%256, g2=end_color/256%256; //get the num of g1
	b1=start_color%256, b2=end_color%256; // get the num of b1
	int sgn1=1,sgn2=1,sgn3=1;
	if (r2<r1){sgn1=-1;}
	if (g2<g1){sgn2=-1;}
	if (b2<b1){sgn3=-1;}
	for (int32_t i=x;i<=x+w;i++){
      level1= r1+ (2*(i-x)*(r2-r1)+(w)*sgn1)/(2*(w));
	  level2= g1+ (2*(i-x)*(g2-g1)+(w)*sgn2)/(2*(w));
	  level3= b1+ (2*(i-x)*(b2-b1)+(w)*sgn3)/(2*(w));
	  set_color(256*256*level1+level2*256+level3); // change in to num
	  for (int32_t j=y; j<=y+h;j++){
		res &= draw_dot(i,j);
	  }
	} 

	return res;
}


/* 
 *  draw_picture
 *	 
 *	 
 *	
 *	
 * INPUTS: none
 * OUTPUTS: alters the image by calling any of the other functions in the file
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */
int32_t
draw_square(int32_t x, int32_t y){
	int32_t res=1;
	
    for(int i=x; i<=x+10;i++){
		for(int j=y; j<=y+10;j++){
			res &= draw_dot(i,j);
		}
	}
	
	return res;
}

int32_t
draw_picture(){
	/* Your code goes here! */
	set_color(0xfd0630);
	draw_square(20,30);
	draw_square(30,30);
	draw_square(60,30);
	draw_square(70,30);
	for (int x=10; x<=80;x=x+10){
	draw_square(x,40);
	}
	for (int x=10; x<=80;x=x+10){
	draw_square(x,50);
	}
	for (int x=20; x<=70;x=x+10){
	draw_square(x,60);
	}
	for (int x=30; x<=60;x=x+10){
	draw_square(x,70);
	}
	for (int x=40; x<=50;x=x+10){
	draw_square(x,80);
	}for (int x=10; x<=80;x=x+10){
	draw_square(x,40);
	}
	//print candy
	set_color(0xf8fa0a);
	for (int x=160; x<=180;x=x+10){
		draw_square(x,40);
	}
	draw_square(150,50);
	set_color(0xfdfe99);
	draw_square(160,50);
	set_color(0xf8fa0a);
	
	for (int x=170; x<=180;x=x+10){
		draw_square(x,50);
	}
    set_color(0xf8da15);
	draw_square(190,50);
	set_color(0xf8fa0a);
	for(int x=150; x<=170;x=x+10){
		draw_square(x,60);
	}
	set_color(0xf8da15);
	for (int x=220; x<=300;x=x+30){
		draw_square(x,60);
	}
	set_color(0xf8fa0a);
	for(int x=150; x<=170;x=x+10){
		draw_square(x,70);
	}
	set_color(0xf8da15);
	for(int x=180; x<=190;x=x+10){
		draw_square(x,70);
	}
	for(int x=160; x<=180;x=x+10){
		draw_square(x,80);
	}
	// monster
	set_color(0xafd0ff);
	draw_square(330,40);
	set_color(0x1b72fe);
	draw_square(340,40);
	set_color(0xafd0ff);
	draw_square(320,50);
	set_color(0x1b72fe);
	draw_square(330,50);
	set_color(0x5334fe);
	draw_square(340,50);
	draw_square(350,50);
	set_color(0x1b72fe);
	draw_square(320,60);
	set_color(0xe370fe);
	draw_square(330,60),draw_square(350,60);
	set_color(0x1b72fe);
	draw_square(340,60);
	draw_square(330,70),draw_square(340,70),draw_square(350,70);draw_square(330,80),draw_square(350,80);
    set_color(0x1b72fe);
	draw_square(320,70);

	//0xafd0ff first
	//e370fe eyecolor
	//#1b72fe second
	//third 5334fe
    set_color(0xafd0ff);
	draw_square(330+100,40);
	set_color(0x1b72fe);
	draw_square(340+100,40);
	set_color(0xafd0ff);
	draw_square(320+100,50);
	set_color(0x1b72fe);
	draw_square(330+100,50);
	set_color(0x5334fe);
	draw_square(340+100,50);
	draw_square(350+100,50);
	set_color(0x1b72fe);
	draw_square(320+100,60);
	set_color(0xe370fe);
	draw_square(330+100,60),draw_square(350+100,60);
	set_color(0x1b72fe);
	draw_square(340+100,60);
	draw_square(330+100,70),draw_square(340+100,70),draw_square(350+100,70);draw_square(330+100,80),draw_square(350+100,80);
    set_color(0x1b72fe);
	draw_square(320+100,70);
    // 
	set_color(0xfffc02);
	for (int x=500; x<=540;x=x+10){
		draw_square(x,40);
	}
	set_color(0);
	for (int x=490; x<=550;x=x+10){
		draw_square(x,50);
	}
	set_color(0xfffc02);
	draw_square(530,60);
	draw_square(490,60),draw_square(520,60);
	for (int x=490; x<=550;x=x+10){
		draw_square(x,70);
	}
	set_color(0);
	draw_square(500,60),draw_square(510,60), draw_square(550,60),draw_square(540,60),draw_square(520,80),draw_square(530,80);
    set_color(0xfffc02);
	
	draw_square(490,80),draw_square(500,80),draw_square(510,80);draw_square(540,80),draw_square(550,80);
    for (int x=500; x<=540;x=x+10){
		draw_square(x,90);
	}
	
    




	//
	set_color(0xfd0630);
	draw_line(50,125,50,225);
	draw_line(50,175,100,175);
	draw_line(100,125,100,225);//H
	draw_line(150,125,175,150);// first 
	draw_line(150,125+35,175,150+35);//second line
	draw_line(150,225,175,200);
	draw_line(190,150+5,245,150+5);//row
	draw_line(203,135,203,175);//colume
        draw_line(231,135,231,175);//colume
	draw_line(180,175,255,175);
        draw_line(203,195,195,225);
	draw_line(231,195,240,225);//hong
    //    draw_circle(345,75-40,25,27);
	//draw_line(345,75+27+5-40,345,75+27+40-40);
	//draw_line(345-10,75+20-40,345-50,75+27+45-40);
	//draw_line(345+10,75+20-40,345+50,75+27+45-40);//draw sun
	set_color(0xf2e585);
	draw_line(345-28,150+5-20,345+27,150+5-20);
	draw_line(203+128,135-20,203+128,175-20);
	draw_line(231+128,135-20,231+128,175-20);
	draw_line(335-28,175-20,355+27,175-20);
	draw_rect(312+10,175,66-20,20);
	draw_line(345,175-20,345,175+20);
	draw_line(312+10,185,312+56,185);
    draw_line(203+128,195+10,195+128,225);
    draw_line(231+128,195+10,240+128,225);
	draw_line(335+27+100,225,335+27+100,160);
	draw_line(462,160,430,120);
	draw_line(462,160,495,120);
	rect_gradient(50,250,445,20,0xf58e73,0xfdd016);
	return 0;
}
