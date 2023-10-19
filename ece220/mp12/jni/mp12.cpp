//									tab:8
//
// mp12.cpp - source file for Spring 2018 MP12 student code
//
// "Copyright (c) 2018 by Steven S. Lumetta."
//
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without written agreement is
// hereby granted, provided that the above copyright notice and the following
// two paragraphs appear in all copies of this software.
//
// IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO
// ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
// EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
// PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
// THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE,
// SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
//
// Author:	    Steve Lumetta
// Version:	    1.00
// Creation Date:   20 April 2018
// Filename:	    mp12.cpp
// History:
//	SL	1.00	20 April 2018
//		First written.
//

#include <iostream>
#include <list>

#include <math.h>
#include <stdio.h>

#include "WALYmain.h"

#include "TurtleScreen.h"

#include "mp5.h"
#include "mp12.h"

using namespace std;
using namespace WALY;

// THESE ARE GLOBAL VARIABLES IN THE INTEREST OF TESTING.  THEY SHOULD
// BE FILE-SCOPE OR LOCAL TO frameUpdate.
FILE *input = NULL;           // input stream
list<segment_t> lines;        // list of lines drawn
command_t cmd = {CMD_NONE};   // current command
int32_t moveColor = 0xFFFFFF; // current movement drawing color
bool check=0;
bool u_command=0;
bool signal=0;
int32_t
openInputStream(const char *fname) 
{
    input=fopen (fname,"r");  //open the file
    if(input==NULL){ // if fail return 0
        return 0;
    }
    return 1;
}

void closeInputStream(void) //close
{
    fclose(input);
}

void showLines(void)
{
    // you can use 'call showLines ()' in GDB to look at the
    // list of segments.  Don't forget to call makeVisibleChange
    // when you change this list, since the background won't be
    // redrawn unless you call that function (so changes will not
    // show up.
    for (list<segment_t>::iterator it = lines.begin();
         lines.end() != it; it++)
    {
        Screen::debug() << it->color << " " << it->x1 << "," << it->y1 << "  " << it->x2 << "," << it->y2 << endl;
    }
}

void drawEverything(void)
{
    for (list<segment_t>::iterator it = lines.begin(); //set color and draw line
         lines.end() != it; it++)
    {
        set_color(it->color); 
        draw_line(it->x1, it->y1, it->x2, it->y2);
    }
}

void readNewCommand(TurtleScreen *ts)
{
    char line[200]; // the current line
    char g[200];
    char useless[200];
    int32_t v,m;
    if(fgets(line,200,input)== NULL){ //get command
        check=1;
        return;
    }
    if(sscanf(line,"%s", g)!=1){
        return;
    }
    if(strcasecmp(g,"color")==0){ //get color
        if(sscanf(line,"%s %x", useless,&v)!=2){
            printf("Unrecognized command: %s", line);
        }else{
            moveColor=v;
        }
    }
    else if(strcasecmp(g, "move") == 0){//get move message
    if(sscanf(line, "%s %d %d", useless, &v, &m) != 3){
       printf("Unrecognized command: %s", line);
    }    
    else if (v>0 && m>0){
        segment_t node;
        const double pi =acos(-1.0);
        u_command=1;
        cmd.framesLeft=m;
        int32_t angle = ts->getDirection();
        cmd.type =CMD_MOVE; 
        cmd.startX=ts->getX();  //get current position
        cmd.startY=ts->getY();
        cmd.endX=cmd.startX-round(v*sin(angle*pi/18));
        cmd.endY=cmd.startY-round(v*sin(angle*pi/18));
        node.color=moveColor;
        node.x1=cmd.startX,node.x2=cmd.endX;
        node.y1=cmd.startY, node.y2=cmd.endY;
        lines.push_front(node);
    }
    }
    else if(strcasecmp(g, "restart") == 0){ // get another input
        check=1;
        rewind(input);
    }
    else if(strcasecmp(g, "turn")==0){
        if (sscanf(line, "%s %d", useless, &v) != 2){
            printf("Unrecognized command: %s", line);
        }
        else if(v!=0){
            u_command=1;
            cmd.type=CMD_TURN;
            cmd.framesLeft=abs(v);
            cmd.dir= v > 0 ? 1 : -1;
        }
    }
    else if(strcasecmp(g, "wait")==0){
        if (sscanf(line, "%s %d", useless, &v) != 2){
            printf("Unrecognized command: %s", line);
        }
        else if(v>0){
            u_command = 1;
            cmd.type = CMD_WAIT; 
            cmd.framesLeft = v;    
        }
    }
    else{
        printf("Unrecognized command: %s", line);
        if ( (check == 0 || u_command == 1) && cmd.type == CMD_NONE ){
            readNewCommand(ts);;
        } 
    }   
}

void frameUpdate(TurtleScreen *ts)
{
    if(signal==0){
        signal=1;
        return;
    }
    if(cmd.type== CMD_NONE){
        readNewCommand(ts);
    }
    switch ((cmd.type)) //use switch to go into differnet type
    {
    case CMD_NONE:
        break;

    case CMD_TURN:
        if(cmd.framesLeft<=0) {
            cmd.type=CMD_NONE;
        }else{
            if(cmd.dir>0){
                ts->turnLeft();
            }else{
                ts->turnRight();  
            }
            cmd.framesLeft--;
            ts->makeVisibleChange();
        }
        break;

    case CMD_MOVE:
            if(cmd.framesLeft>0){
                int x= ts->getX();
                int x_x= round((cmd.endX - x) / (double)cmd.framesLeft);
                int y=ts->getY();
                int y_y = round((cmd.endY - y) / (double)cmd.framesLeft);
                ts->setY(y + y_y);
                ts->setX(x + x_x); 
                cmd.framesLeft--;
                ts->makeVisibleChange();
            }
            if (cmd.framesLeft <= 0) cmd.type = CMD_NONE;
            break;
    case CMD_WAIT:
            if (cmd.framesLeft > 0){ 
                cmd.framesLeft--;
            }
            if (cmd.framesLeft <= 0){ 
                cmd.type = CMD_NONE;
            }
            break;


    default:
        printf("Unrecognized cmd.type when doing frameUpdate()\n");
        break;
    }
}
