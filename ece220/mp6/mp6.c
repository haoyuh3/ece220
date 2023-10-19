/*									tab:8
 *
 * mp6.c - implementation file for ECE220 "Blocky" game
 *
 * "Copyright (c) 2017-2018 by Steven S. Lumetta."
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
 * Author:	    Steve Lumetta
 * Version:	    5
 * Creation Date:   7 November 2017
 * Filename:	    mp2.c
 * History:
 *	SL	1	7 November 2017
 *		First written.
 *      JXG     2	8 November 2017
 *		Added ncurses support.
 *	SL	3	30 November 2017
 *		Polished for MP distribution.
 *	SL	4	18 February 2018
 *		Edited slightly for ECE220H S18 distribution.
 *	SL	5	18 February 2018
 *		Stripped down from gold version.
 */


#include <stdint.h>
#include <stdio.h>

#include "mp6.h"


/* 
 * The maximum number of blocks in one piece.  Do not change for
 * this assignment (you can do as you like with the code afterward).
 */
#define MAX_PIECE_SIZE 4

/*
 * Pieces are defined by an array of offsets from the center point.
 * Each piece consists of a set of adjacent blocks that together form
 * the piece.  The first index of the array is the piece type, the 
 * second is the orientation (0-3), the third is block index within 
 * the piece (0 to MAX_PIECE_SIZE - 1), and the fourth gives the 
 * x (0) and y (1) offsets of the block relative to the center point.
 * Note that the first block is always the center point of the piece.
 * 
 * Offsets may be replicated if a piece contains fewer than MAX_PIECE_SIZE
 * blocks.
 *
 * Clockwise rotation changes the orientation in the positive (mod 4)
 * direction, and counter-clockwise rotation changes the orientation in
 * the negative (mod 4) direction.
 */
static const int32_t piece_def[NUM_PIECE_TYPES][4][MAX_PIECE_SIZE][2] = {
    {   /* PIECE_TYPE_ELL */
	{{0, 0}, { 1,  0}, { 2,  0}, { 0,  1}},
	{{0, 0}, { 0,  1}, { 0,  2}, {-1,  0}},
	{{0, 0}, {-1,  0}, {-2,  0}, { 0, -1}},
	{{0, 0}, { 0, -1}, { 0, -2}, { 1,  0}}
    },
    {   /* PIECE_TYPE_REV_ELL */
	{{0, 0}, { 1,  0}, { 2,  0}, { 0, -1}},
	{{0, 0}, { 0,  1}, { 0,  2}, { 1,  0}},
	{{0, 0}, {-1,  0}, {-2,  0}, { 0,  1}},
	{{0, 0}, { 0, -1}, { 0, -2}, {-1,  0}}
    },
    {   /* PIECE_TYPE_LINE */
	{{0, 0}, {-1,  0}, { 1,  0}, { 2,  0}},
	{{0, 0}, { 0, -1}, { 0,  1}, { 0,  2}},
	{{0, 0}, { 1,  0}, {-1,  0}, {-2,  0}},
	{{0, 0}, { 0,  1}, { 0, -1}, { 0, -2}}
    },
    {   /* PIECE_TYPE_TEE */
	{{0, 0}, {-1,  0}, { 0, -1}, { 1,  0}},
	{{0, 0}, { 0, -1}, { 1,  0}, { 0,  1}},
	{{0, 0}, { 1,  0}, { 0,  1}, {-1,  0}},
	{{0, 0}, { 0,  1}, {-1,  0}, { 0, -1}}
    },
    {   /* PIECE_TYPE_ESS */
	{{0, 0}, { 0, -1}, { 1,  0}, { 1,  1}},
	{{0, 0}, { 1,  0}, { 0,  1}, {-1,  1}},
	{{0, 0}, { 0,  1}, {-1,  0}, {-1, -1}},
	{{0, 0}, {-1,  0}, { 0, -1}, { 1, -1}}
    },
    {   /* PIECE_TYPE_REV_ESS */
	{{0, 0}, { 0, -1}, {-1,  0}, {-1,  1}},
	{{0, 0}, { 1,  0}, { 0, -1}, {-1, -1}},
	{{0, 0}, { 0,  1}, { 1,  0}, { 1, -1}},
	{{0, 0}, {-1,  0}, { 0,  1}, { 1,  1}}
    }
};


/* 
 * empty_board -- fills a board b with empty spaces (SPACE_EMPTY)
 * INPUTS: b -- the board
 * OUTPUTS: b -- the board, filled with empty spaces
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
// this part is used to empty the board
// if the point is zero then make it value to zero
// loop height and width
int32_t
empty_board (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH])
{
    for (int i=0; i<BOARD_WIDTH;i++){
        for (int j=0;j<BOARD_HEIGHT;j++){
            b[j][i]=0;
        }
    }
    return 1;
}


/* 
 * mark_piece -- forcibly writes a piece into a board, ignoring the 
 *               board's current contents; you will need to understand
 *               the piece definition array (piece_def) in order to
 *               implement this function
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the orientation of the piece
 *         x -- horizontal coordinate of the piece's center point
 *         y -- vertical coordinate of the piece's center point
 *         v -- type of space to write (in the shape of the piece)
 * OUTPUTS: b -- the board, with the piece filled in with value v
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
//2 represent current 1 represent old from main.c
// p is the type and orient represent the row (consists of four points and index[1]represent dy index[0] represent dx)
void
mark_piece (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH], 
            piece_type_t p, int32_t orient, int32_t x, int32_t y,
	    space_type_t v)
{   
    int dy, dx;
    //b[1][1]=1;
    b[y][x]=v; // makr center point
    for (int i=0; i<4;i++){
         dy=piece_def[p][orient][i][1]; //get the relative distance respect to center point
         dx=piece_def[p][orient][i][0];
         b[y+dy][x+dx]=v; // its value is v
    }  

}


/* 
 * test_piece_fit -- checks whether a piece fits into a board; you will 
 *		     need to understand the piece definition array 
 *		     (piece_def) in order to implement this function
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the orientation of the piece
 *         x -- horizontal coordinate of the piece's center point
 *         y -- vertical coordinate of the piece's center point
 * OUTPUTS: none
 * RETURN VALUE: if the piece does not fit within the board, returns 
 *		 FIT_OUT_OF_BOARD; otherwise, if the piece would overwrite 
 *		 non-empty board spaces, returns FIT_NO_ROOM_THERE; 
 *		 otherwise, returns FIT_SUCCESS
 * SIDE EFFECTS: none
 */
//if the piece is out of board or have no space then it wil fail
fit_result_t
test_piece_fit (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH], 
                piece_type_t p, int32_t orient, int32_t x, int32_t y)
{ 
    int dy, dx;
    int x_new,y_new;
    for (int i=0; i<4;i++){
         dy=piece_def[p][orient][i][1]; //get the location of four points
         dx=piece_def[p][orient][i][0];
         x_new=dx+x, y_new=dy+y;
         if (x_new>=BOARD_WIDTH || x_new<0 || y_new>=BOARD_HEIGHT || y_new<0){return FIT_OUT_OF_BOARD;} //out of board then fail
         if (b[y+dy][x+dx]!=0){return FIT_NO_ROOM_THERE;}
    }
    return FIT_SUCCESS; //if pass all loop then it success
}


/* 
 * print_board -- prints a board to the screen using period ('.') to 
 *		  represent empty spaces, percent ('%') to represent 
 *		  old blocks, and asterisk ('*') to represent the current 
 *		  piece (SPACE_BLOCK); see specification for example
 * 		  of board appearance
 * INPUTS: b -- the board
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: prints to the monitor
 */
// loop all the board prints a board to the screen using period ('.') to represent empty spaces, percent ('%') to represent 
//old blocks, and asterisk ('*') to represent the current 
void
print_board (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH])
{
    for (int i=0; i<BOARD_HEIGHT; i++){
        for (int j=0; j<BOARD_WIDTH;j++){
          if (b[i][j]==0){printf(".");}
          if(b[i][j]==2){printf("*");}
          if(b[i][j]==1){printf("%%");}
        }
        printf("\n"); //after print a row
    }
}


/* 
 * try_to_move_down -- tries to move the current piece down one space in 
 *                     the board; assumes that the piece is in the board
 *		       and must thus be removed before it can be put into
 *                     its new position (or back into its old position
 *                     on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece moved down (on success), or
 *               unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
// this part is used to move down the piece which means all point's y plus 1
int32_t
try_to_move_down (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH], 
                  piece_type_t p, int32_t orient, int32_t x, int32_t y)
{
    int sgn;
    mark_piece( b,p,orient,x,y,0); // to hide the current piece which help to test
    sgn=test_piece_fit ( b,p,orient,x,y+1); // call test_piece_fit to check
    if (sgn==1 || sgn==2){
        mark_piece( b,p,orient,x,y,2); // if fail then return back and return 0
        return 0;
    }
   
    mark_piece( b,p,orient,x,y+1,2); // otherwise mark new point
    return 1;
}


/* 
 * try_to_move_left -- tries to move the current piece one space left in
 *                     the board; assumes that the piece is in the board
 *		       and must thus be removed before it can be put into
 *                     its new position (or back into its old position
 *                     on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece moved left (on success), or
 *               unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
//move left piece which mean all x minus 1
int32_t
try_to_move_left (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH], 
                  piece_type_t p, int32_t orient, int32_t x, int32_t y)
{   
    mark_piece( b,p,orient,x,y,0);
    int sgn;
    sgn=test_piece_fit ( b,p,orient,x-1,y); // call test_piece_fit to check
    if (sgn==1 || sgn==2){
        mark_piece( b,p,orient,x,y,2); // return back
        return 0;
    }
    
    mark_piece( b,p,orient,x-1,y,2); // new location
    return 1;
}


/* 
 * try_to_move_right -- tries to move the current piece one space right in
 *                     the board; assumes that the piece is in the board
 *		       and must thus be removed before it can be put into
 *                     its new position (or back into its old position
 *                     on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece moved right (on success), or
 *               unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
//move right means all x add 1
int32_t
try_to_move_right (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH], 
                   piece_type_t p, int32_t orient, int32_t x, int32_t y)
{   
    mark_piece( b,p,orient,x,y,0);
    int sgn;
    sgn=test_piece_fit ( b,p,orient,x+1,y); // move right
    if (sgn==1 || sgn==2){
        mark_piece( b,p,orient,x,y,2); // return back
        return 0;
    }
    
    mark_piece( b,p,orient,x+1,y,2); // move right and mark points
    return 1;
   
}


/* 
 * try_to_rotate_clockwise -- 
 *	tries to rotate the current piece clockwise in the board; assumes 
 *	that the piece is in the board and must thus be removed before it 
 *	can be put into its new position (or back into its old position on
 *	failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece rotated clockwise (on success), 
 *		 or unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
// this function is used to rotate clockwise
int32_t
try_to_rotate_clockwise (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH], 
                         piece_type_t p, int32_t orient, int32_t x, int32_t y)
{   
    mark_piece( b,p,orient,x,y,0);
    int sgn;
    int orient_new;
    orient_new=(orient+1)%4; //orient only have four value module 4 to get right orient and get relative distance according to center point
    sgn=test_piece_fit ( b,p,orient_new,x,y);
    if (sgn==1 || sgn==2){
        mark_piece( b,p,orient,x,y,2);
        return 0;
    }

    mark_piece( b,p,orient_new,x,y,2); // have new location
    return 1;
}


/* 
 * try_to_rotate_cc -- 
 *	tries to rotate the current piece counter-clockwise in the board; 
 *	assumes that the piece is in the board and must thus be removed 
 *	before it can be put into its new position (or back into its old 
 *	position on failure)
 * INPUTS: b -- the board
 *         p -- the type of piece
 *         orient -- the current orientation of the piece
 *         x -- current horizontal coordinate of the piece's center point
 *         y -- current vertical coordinate of the piece's center point
 * OUTPUTS: b -- the board, with the piece rotated counter-clockwise (on 
 *		 success), or unchanged on failure
 * RETURN VALUE: 1 on success, 0 on failure
 * SIDE EFFECTS: none
 */
// this funciton used tp rotate cc
int32_t
try_to_rotate_cc (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH], 
                  piece_type_t p, int32_t orient, int32_t x, int32_t y)
{   
    mark_piece( b,p,orient,x,y,0);
    int sgn;
    int orient_new;
    orient_new=(orient-1);
    while(orient_new<0){ // if negative then add it till positive 
        orient_new+=4;
    }
    orient_new=orient_new%4; // module 4
    sgn=test_piece_fit ( b,p,orient_new,x,y);
    if (sgn==1 || sgn==2){
        mark_piece( b,p,orient,x,y,2); // fail and return back
        return 0;
    }

    mark_piece( b,p,orient_new,x,y,2); // success and get new four points
    return 1;
    
}


/* 
 * remove_row -- removes a single row from a board, moving rows above
 *		 it downward and adding a new empty row at the top of
 *		 the board; this function should be called by your
 *		 remove_full_rows function
 * INPUTS: b -- the board
 *	   row -- which row to remove
 * OUTPUTS: b -- the board, with the specified row removed
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
// this function is used to remove whole row if they are all full 
void
remove_row (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH], int row)
{
    for(int j=BOARD_HEIGHT-1;j>0;j--){
        for (int i=0; i<row;i++){
            b[j][i]=b[j-1][i]; // each row will get its value from above and last row lose its value
        }
    }
    for (int i=0; i<BOARD_WIDTH;i++){
        b[0][i]=0; // to maintain the num of rows we add a empty row
    }
    
}
/* 
 * remove_full_rows -- removes all rows filled with SPACE_FULL from a 
 * 		       board, moving rows above them downward and adding 
 *		       new empty rows at the top of the board
 * INPUTS: b -- the board
 * OUTPUTS: b -- the board, with full rows removed
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
//  this part is used to judge which row is full and change teh row above
void
remove_full_rows (space_type_t b[BOARD_HEIGHT][BOARD_WIDTH])
{   
    int sgn=1; // a signal help to judge whether it is full
    for (int j=0;j<BOARD_HEIGHT;j++){
        sgn=1;
        for (int i=0; i<BOARD_WIDTH;i++){
            if (b[j][i]!=1){sgn=-1;} // when one is not full then the function will not call remove_row
        }
        if (sgn==1){remove_row (b,j);} // if one row is full then call the function
    }
}
