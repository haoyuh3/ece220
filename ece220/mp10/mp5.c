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
#include <stdio.h>

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

int32_t
near_horizontal(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int32_t res = 1;
	if (x_start > x_end){
		int32_t t;
		t = x_start; x_start = x_end; x_end = t;
		t = y_start; y_start = y_end; y_end = t;
	}
	int32_t sgn = 0;
	if (y_end > y_start) sgn = 1;
	else sgn = -1;
	for (int32_t x = x_start; x <= x_end; x++){
		int32_t y = (2 * (y_end - y_start) * (x - x_start) + (x_end - x_start) * sgn) / (2 * (x_end - x_start)) + y_start;
		res &= draw_dot(x, y);
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

int32_t
near_vertical(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int32_t res = 1;
	if (y_start > y_end){
		int32_t t;
		t = x_start; x_start = x_end; x_end = t;
		t = y_start; y_start = y_end; y_end = t;
	}
	int32_t sgn = 0;
	if (x_end > x_start) sgn = 1;
	else sgn = -1;
	for (int32_t y = y_start; y <= y_end; y++){
		int32_t x = (2 * (x_end - x_start) * (y - y_start) + (y_end - y_start) * sgn) / (2 * (y_end - y_start)) + x_start;
		res &= draw_dot(x, y);
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

int32_t
draw_line(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int32_t res = 1, dy = y_end - y_start, dx = x_end - x_start;
	dy = dy > 0 ? dy : -dy, dx = dx > 0 ? dx : -dx;
	if (x_start == x_end && y_start == y_end) draw_dot(x_start, y_start);
	else if (dy < dx) res = near_horizontal(x_start, y_start, x_end, y_end);
	else res = near_vertical(x_start, y_start, x_end, y_end);
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

int32_t
draw_rect(int32_t x, int32_t y, int32_t w, int32_t h){
	/* Your code goes here! */
	if (w < 0 || h < 0) return 0;
	int32_t res = 1;
	for (int32_t i = x; i <= x + w; i++) res &= draw_dot(i, y), res &= draw_dot(i, y + h);
	for (int32_t i = y; i <= y + h; i++) res &= draw_dot(x, i), res &= draw_dot(x + w, i);
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

int32_t
draw_triangle(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	/* Your code goes here! */
	int32_t res = 1;
	res &= draw_line(x_A, y_A, x_B, y_B);
	res &= draw_line(x_A, y_A, x_C, y_C);
	res &= draw_line(x_B, y_B, x_C, y_C);
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

int32_t
draw_parallelogram(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	/* Your code goes here! */
	int32_t res = 1, x_D = x_C - x_B + x_A, y_D = y_C - y_B + y_A;
	res &= draw_line(x_A, y_A, x_B, y_B);
	res &= draw_line(x_B, y_B, x_C, y_C);
	res &= draw_line(x_C, y_C, x_D, y_D);
	res &= draw_line(x_D, y_D, x_A, y_A);
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

int32_t
draw_circle(int32_t x, int32_t y, int32_t inner_r, int32_t outer_r){
	/* Your code goes here!*/
	if (inner_r < 0 || outer_r < inner_r) return 0;
	int32_t res = 1;
	for (int32_t i = x - outer_r; i <= x + outer_r; i++){
		for (int32_t j = y - outer_r; j <= y + outer_r; j++){
			int32_t d2 = (i - x) * (i - x) + (j - y) * (j - y);
			if (d2 <= outer_r * outer_r && d2 >= inner_r * inner_r){
				res &= draw_dot(i, j);
			}
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

int32_t
rect_gradient(int32_t x, int32_t y, int32_t w, int32_t h, int32_t start_color, int32_t end_color){
	/* Your code goes here! */
	if (w < 0 || h < 0) return 0;
	int32_t r1 = (start_color / (256 * 256)) % 256, g1 = (start_color / 256) % 256, b1 = start_color % 256;
	int32_t r2 = (end_color / (256 * 256)) % 256, g2 = (end_color / 256) % 256, b2 = end_color % 256;
	int32_t res = 1, sgn_r = 0, sgn_g = 0, sgn_b = 0;
	if (r2 > r1) sgn_r = 1;
	else sgn_r = -1;
	if (g2 > g1) sgn_g = 1;
	else sgn_g = -1;
	if (b2 > b1) sgn_b = 1;
	else sgn_b = -1;
	for (int32_t i = x; i <= x + w; i++){
		int32_t ri, gi, bi;
		ri = (2 * (i - x) * (r2 - r1) + w * sgn_r) / (2 * w) + r1;
		gi = (2 * (i - x) * (g2 - g1) + w * sgn_g) / (2 * w) + g1;
		bi = (2 * (i - x) * (b2 - b1) + w * sgn_b) / (2 * w) + b1;
		set_color(256 * 256 * ri + 256 * gi + bi);
		for (int32_t j = y; j <= y + h; j++){
			res &= draw_dot(i, j);
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
draw_picture(){
	/* Your code goes here! */
	int32_t res = 1;
	res &= rect_gradient(0, 0, WIDTH - 1, HEIGHT - 1, 0x00000000, 0x00FFFFFF);
	set_color(0x00FF0000);
	res &= draw_line(WIDTH * 1 / 32, HEIGHT * 1 / 4, WIDTH * 31 / 224, HEIGHT * 1 / 4);
	res &= draw_line(WIDTH * 31 / 224, HEIGHT * 1 / 4, WIDTH * 23 / 224, HEIGHT * 5 / 8);
	res &= draw_line(WIDTH * 23 / 224, HEIGHT * 5 / 8, WIDTH * 31 / 224, HEIGHT * 5 / 8);
	res &= draw_line(WIDTH * 31 / 224, HEIGHT * 5 / 8, WIDTH * 31 / 224, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 31 / 224, HEIGHT * 3 / 4, WIDTH * 1 / 32, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 1 / 32, HEIGHT * 3 / 4, WIDTH * 15 / 224, HEIGHT * 3 / 8);
	res &= draw_line(WIDTH * 15 / 224, HEIGHT * 3 / 8, WIDTH * 1 / 32, HEIGHT * 3 / 8);
	res &= draw_line(WIDTH * 1 / 32, HEIGHT * 3 / 8, WIDTH * 1 / 32, HEIGHT * 1 / 4);
	set_color(0x00FF7F00);
	res &= draw_line(WIDTH * 25 / 112, HEIGHT * 1 / 4, WIDTH * 31 / 112, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 31 / 112, HEIGHT * 3 / 4, WIDTH * 1 / 4, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 1 / 4, HEIGHT * 3 / 4, WIDTH * 53 / 224, HEIGHT * 5 / 8);
	res &= draw_line(WIDTH * 53 / 224, HEIGHT * 5 / 8, WIDTH * 47 / 224, HEIGHT * 5 / 8);
	res &= draw_line(WIDTH * 47 / 224, HEIGHT * 5 / 8, WIDTH * 11 / 56, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 11 / 56, HEIGHT * 3 / 4, WIDTH * 19 / 112, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 19 / 112, HEIGHT * 3 / 4, WIDTH * 25 / 112, HEIGHT * 1 / 4);
	res &= draw_triangle(WIDTH * 25 / 112, HEIGHT * 9 / 20, WIDTH * 103 / 448, HEIGHT * 11 / 20, WIDTH * 97 / 448, HEIGHT * 11 / 20);
	set_color(0x00FFFF00);
	res &= draw_line(WIDTH * 69 / 224, HEIGHT * 1 / 4, WIDTH * 93 / 224, HEIGHT * 1 / 4);
	res &= draw_line(WIDTH * 93 / 224, HEIGHT * 1 / 4, WIDTH * 93 / 224, HEIGHT * 5 / 16);
	res &= draw_line(WIDTH * 93 / 224, HEIGHT * 5 / 16, WIDTH * 85 / 224, HEIGHT * 5 / 16);
	res &= draw_line(WIDTH * 85 / 224, HEIGHT * 5 / 16, WIDTH * 85 / 224, HEIGHT * 11 / 16);
	res &= draw_line(WIDTH * 85 / 224, HEIGHT * 11 / 16, WIDTH * 93 / 224, HEIGHT * 11 / 16);
	res &= draw_line(WIDTH * 93 / 224, HEIGHT * 11 / 16, WIDTH * 93 / 224, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 93 / 224, HEIGHT * 3 / 4, WIDTH * 69 / 224, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 69 / 224, HEIGHT * 3 / 4, WIDTH * 69 / 224, HEIGHT * 11 / 16);
	res &= draw_line(WIDTH * 69 / 224, HEIGHT * 11 / 16, WIDTH * 77 / 224, HEIGHT * 11 / 16);
	res &= draw_line(WIDTH * 77 / 224, HEIGHT * 11 / 16, WIDTH * 77 / 224, HEIGHT * 5 / 16);
	res &= draw_line(WIDTH * 77 / 224, HEIGHT * 5 / 16, WIDTH * 69 / 224, HEIGHT * 5 / 16);
	res &= draw_line(WIDTH * 69 / 224, HEIGHT * 5 / 16, WIDTH * 69 / 224, HEIGHT * 1 / 4);
	set_color(0x0000FF00);
	res &= draw_line(WIDTH * 25 / 56, HEIGHT * 1 / 4, WIDTH * 27 / 56, HEIGHT * 1 / 4);
	res &= draw_line(WIDTH * 27 / 56, HEIGHT * 1 / 4, WIDTH * 27 / 56, HEIGHT * 9 / 20);
	res &= draw_line(WIDTH * 27 / 56, HEIGHT * 9 / 20, WIDTH * 29 / 56, HEIGHT * 9 / 20);
	res &= draw_line(WIDTH * 29 / 56, HEIGHT * 9 / 20, WIDTH * 29 / 56, HEIGHT * 1 / 4);
	res &= draw_line(WIDTH * 29 / 56, HEIGHT * 1 / 4, WIDTH * 31 / 56, HEIGHT * 1 / 4);
	res &= draw_line(WIDTH * 31 / 56, HEIGHT * 1 / 4, WIDTH * 31 / 56, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 31 / 56, HEIGHT * 3 / 4, WIDTH * 29 / 56, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 29 / 56, HEIGHT * 3 / 4, WIDTH * 29 / 56, HEIGHT * 11 / 20);
	res &= draw_line(WIDTH * 29 / 56, HEIGHT * 11 / 20, WIDTH * 27 / 56, HEIGHT * 11 / 20);
	res &= draw_line(WIDTH * 27 / 56, HEIGHT * 11 / 20, WIDTH * 27 / 56, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 27 / 56, HEIGHT * 3 / 4, WIDTH * 25 / 56, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 25 / 56, HEIGHT * 3 / 4, WIDTH * 25 / 56, HEIGHT * 1 / 4);
	set_color(0x0000FFFF);
	res &= draw_line(WIDTH * 131 / 224, HEIGHT * 1 / 4, WIDTH * 155 / 224, HEIGHT * 1 / 4);
	res &= draw_line(WIDTH * 155 / 224, HEIGHT * 1 / 4, WIDTH * 155 / 224, HEIGHT * 7 / 20);
	res &= draw_line(WIDTH * 155 / 224, HEIGHT * 7 / 20, WIDTH * 139 / 224, HEIGHT * 7 / 20);
	res &= draw_line(WIDTH * 139 / 224, HEIGHT * 7 / 20, WIDTH * 139 / 224, HEIGHT * 9 / 20);
	res &= draw_line(WIDTH * 139 / 224, HEIGHT * 9 / 20, WIDTH * 155 / 224, HEIGHT * 9 / 20);
	res &= draw_line(WIDTH * 155 / 224, HEIGHT * 9 / 20, WIDTH * 155 / 224, HEIGHT * 11 / 20);
	res &= draw_line(WIDTH * 155 / 224, HEIGHT * 11 / 20, WIDTH * 139 / 224, HEIGHT * 11 / 20);
	res &= draw_line(WIDTH * 139 / 224, HEIGHT * 11 / 20, WIDTH * 139 / 224, HEIGHT * 13 / 20);
	res &= draw_line(WIDTH * 139 / 224, HEIGHT * 13 / 20, WIDTH * 155 / 224, HEIGHT * 13 / 20);
	res &= draw_line(WIDTH * 155 / 224, HEIGHT * 13 / 20, WIDTH * 155 / 224, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 155 / 224, HEIGHT * 3 / 4, WIDTH * 131 / 224, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 131 / 224, HEIGHT * 3 / 4, WIDTH * 131 / 224, HEIGHT * 1 / 4);
	set_color(0x000000FF);
	res &= draw_line(WIDTH * 81 / 112, HEIGHT * 1 / 4, WIDTH * 93 / 112, HEIGHT * 1 / 4);
	res &= draw_line(WIDTH * 93 / 112, HEIGHT * 1 / 4, WIDTH * 89 / 112, HEIGHT * 5 / 8);
	res &= draw_line(WIDTH * 89 / 112, HEIGHT * 5 / 8, WIDTH * 93 / 112, HEIGHT * 5 / 8);
	res &= draw_line(WIDTH * 93 / 112, HEIGHT * 5 / 8, WIDTH * 93 / 112, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 93 / 112, HEIGHT * 3 / 4, WIDTH * 81 / 112, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 81 / 112, HEIGHT * 3 / 4, WIDTH * 85 / 112, HEIGHT * 3 / 8);
	res &= draw_line(WIDTH * 85 / 112, HEIGHT * 3 / 8, WIDTH * 81 / 112, HEIGHT * 3 / 8);
	res &= draw_line(WIDTH * 81 / 112, HEIGHT * 3 / 8, WIDTH * 81 / 112, HEIGHT * 1 / 4);
	set_color(0x00C000FF);
	res &= draw_line(WIDTH * 193 / 224, HEIGHT * 1 / 4, WIDTH * 31 / 32, HEIGHT * 1 / 4);
	res &= draw_line(WIDTH * 31 / 32, HEIGHT * 1 / 4, WIDTH * 31 / 32, HEIGHT * 11 / 20);
	res &= draw_line(WIDTH * 31 / 32, HEIGHT * 11 / 20, WIDTH * 201 / 224, HEIGHT * 11 / 20);
	res &= draw_line(WIDTH * 201 / 224, HEIGHT * 11 / 20, WIDTH * 201 / 224, HEIGHT * 13 / 20);
	res &= draw_line(WIDTH * 201 / 224, HEIGHT * 13 / 20, WIDTH * 31 / 32, HEIGHT * 13 / 20);
	res &= draw_line(WIDTH * 31 / 32, HEIGHT * 13 / 20, WIDTH * 31 / 32, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 31 / 32, HEIGHT * 3 / 4, WIDTH * 193 / 224, HEIGHT * 3 / 4);
	res &= draw_line(WIDTH * 193 / 224, HEIGHT * 3 / 4, WIDTH * 193 / 224, HEIGHT * 9 / 20);
	res &= draw_line(WIDTH * 193 / 224, HEIGHT * 9 / 20, WIDTH * 209 / 224, HEIGHT * 9 / 20);
	res &= draw_line(WIDTH * 209 / 224, HEIGHT * 9 / 20, WIDTH * 209 / 224, HEIGHT * 7 / 20);
	res &= draw_line(WIDTH * 209 / 224, HEIGHT * 7 / 20, WIDTH * 193 / 224, HEIGHT * 7 / 20);
	res &= draw_line(WIDTH * 193 / 224, HEIGHT * 7 / 20, WIDTH * 193 / 224, HEIGHT * 1 / 4);
	return res;
}
