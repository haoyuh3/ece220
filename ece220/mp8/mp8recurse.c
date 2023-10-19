#include <stdlib.h>
#include <string.h>

#include "mp8.h"


/*
 * basicRecurse -- flood fill recursively from a point until reaching
 *                 white or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
// we will use recures to search all the possible points
// the points will flood left, right, up and down for each point we need to judge whetjer it is possible
// in this part recurse will stop when the color is not white
void 
basicRecurse (int32_t width, int32_t height,
	      const uint8_t* inRed, const uint8_t* inGreen, 
	      const uint8_t* inBlue, 
	      int32_t x, int32_t y, 
	      uint8_t* marking)
{   
	
	
	//if( Red !=255 && Green !=255 && Blue != 255) { // if the point is noot white then we will ignoreit
    marking[x+width*y]=1; // mark the current point to 1 when call functionitself it will help to search and mark points
	//}
	// flood left
	if (x-1>=0 && !(inRed[x-1+y*width]==255 && inGreen[x-1+y*width]==255 && inBlue[x-1+y*width]==255) && marking[x-1+y*width]==0){
       basicRecurse(width, height,inRed, inGreen, inBlue, x-1, y,marking);
	}
	//flod right
	if (x+1<width && !(inRed[x+1+y*width]==255 && inGreen[x+1+y*width]==255 && inBlue[x+1+y*width]==255) && marking[x+1+y*width]==0){
		basicRecurse(width, height,inRed, inGreen, inBlue, x+1, y,marking);
	}
	//flood up
	if (y-1>=0 && !(inRed[x+(y-1)*width]==255 && inGreen[x+(y-1)*width]==255 && inBlue[x+(y-1)*width]==255) && marking[x+(y-1)*width]==0){
		basicRecurse(width, height,inRed, inGreen, inBlue, x, y-1,marking);
	}
	//flood down
	if (y+1<height && !(inRed[x+(y+1)*width]==255 && inGreen[x+(y+1)*width]==255 && inBlue[x+(y+1)*width]==255) && marking[x+(y+1)*width]==0){
		basicRecurse(width, height,inRed, inGreen, inBlue, x, y+1,marking);
	}
	
}


/*
 * greyRecurse -- flood fill recursively from a point until reaching
 *                near-white pixels or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         distSq -- maximum distance squared between white and boundary
 *                   pixel color
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
// it is similiar to basicflood but this time we will not ignore all the white points but we will try to
//stop when the color is similiar to white
// colorwithindisq is used to find similiar color
void 
greyRecurse (int32_t width, int32_t height,
	     const uint8_t* inRed, const uint8_t* inGreen, 
	     const uint8_t* inBlue, 
	     int32_t x, int32_t y, uint32_t distSq, 
	     uint8_t* marking)
{
	// int Red, Green,Blue;
	// Red= inRed[x+y*width];
	// Green= inGreen[x+y*width]; 
	// Blue= inBlue[x+y*width];
	// if( Red !=255 && Green !=255 && Blue != 255) {}


	// use colorwithdistsq to find color that is similiar to white if value is 0 means two color are different
    //if (colorsWithinDistSq(255,255,255,inRed[x+y*width],inGreen[x+y*width],inBlue[x+y*width],distSq)==0)
	marking[x+width*y]=1;
	//left
	if (x-1>=0 && (colorsWithinDistSq(255,255,255,inRed[x-1+y*width],inGreen[x-1+y*width],inBlue[x-1+y*width],distSq)==0) && marking[x-1+y*width]==0){
       greyRecurse(width, height,inRed, inGreen, inBlue, x-1, y,distSq,marking);
	}//right
	if (x+1<width && (colorsWithinDistSq(255,255,255,inRed[x+1+y*width],inGreen[x+1+y*width],inBlue[x+1+y*width],distSq)==0) && marking[x+1+y*width]==0){
		greyRecurse(width, height,inRed, inGreen, inBlue, x+1, y,distSq,marking);
	}//up
	if (y-1>=0 && (colorsWithinDistSq(255,255,255,inRed[x+(y-1)*width],inGreen[x+(y-1)*width],inBlue[x+(y-1)*width],distSq)==0) && marking[x+(y-1)*width]==0){
		greyRecurse(width, height,inRed, inGreen, inBlue, x, y-1,distSq,marking);
	}//down
	if (y+1<height && (colorsWithinDistSq(255,255,255,inRed[x+(y+1)*width],inGreen[x+(y+1)*width],inBlue[x+(y+1)*width],distSq)==0) && marking[x+(y+1)*width]==0){
		greyRecurse(width, height,inRed, inGreen, inBlue, x, y+1,distSq,marking);
	}
}


/*
 * limitedRecurse -- flood fill recursively from a point until reaching
 *                   pixels too different (in RGB color) from the color at
 *                   the flood start point, too far away (> 35 pixels), or
 *                   beyond the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         origX -- starting x position of the flood
 *         origY -- starting y position of the flood
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         distSq -- maximum distance squared between pixel at origin 
 *                   and boundary pixel color
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
// we want to another limitation-distance from orig
// it will not larger than 35
void 
limitedRecurse (int32_t width, int32_t height,
	        const uint8_t* inRed, const uint8_t* inGreen, 
	        const uint8_t* inBlue, 
	        int32_t origX, int32_t origY, int32_t x, int32_t y, 
		uint32_t distSq, uint8_t* marking)
{   
	marking[x+width*y]=1;
	// add another limitation (x-origX)*(x-origX)+(y-origY)*(y-origY)<35*35
	// left
	if (x-1>=0 && ((x-1-origX)*(x-1-origX)+(y-origY)*(y-origY)<35*35) && (colorsWithinDistSq(inRed[origX+origY* width],inGreen[origX+origY* width],inBlue[origX+origY* width],inRed[x-1+y*width],inGreen[x-1+y*width],inBlue[x-1+y*width],distSq)==1) && marking[x-1+y*width]==0){
       limitedRecurse(width, height,inRed, inGreen, inBlue,origX,origY, x-1, y,distSq,marking);
	}//right
	if (x+1<width && ((x+1-origX)*(x+1-origX)+(y-origY)*(y-origY)<35*35) && (colorsWithinDistSq(inRed[origX+origY* width],inGreen[origX+origY* width],inBlue[origX+origY* width],inRed[x+1+y*width],inGreen[x+1+y*width],inBlue[x+1+y*width],distSq)==1) && marking[x+1+y*width]==0){
		limitedRecurse(width, height,inRed, inGreen, inBlue,origX,origY, x+1, y,distSq,marking);
	}//up
	if (y-1>=0 && ((x-origX)*(x-origX)+(y-1-origY)*(y-1-origY)<35*35) && (colorsWithinDistSq(inRed[origX+origY* width],inGreen[origX+origY* width],inBlue[origX+origY* width],inRed[x+(y-1)*width],inGreen[x+(y-1)*width],inBlue[x+(y-1)*width],distSq)==1) && marking[x+(y-1)*width]==0){
		limitedRecurse(width, height,inRed, inGreen, inBlue,origX,origY, x, y-1,distSq,marking);
	}//down
	if (y+1<height && ((x-origX)*(x-origX)+(y+1-origY)*(y+1-origY)<35*35) && (colorsWithinDistSq(inRed[origX+origY* width],inGreen[origX+origY* width],inBlue[origX+origY* width],inRed[x+(y+1)*width],inGreen[x+(y+1)*width],inBlue[x+(y+1)*width],distSq)==1) && marking[x+(y+1)*width]==0){
		limitedRecurse(width, height,inRed, inGreen, inBlue,origX,origY, x, y+1,distSq,marking);
	}
}



