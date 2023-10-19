#include <stdlib.h>
#include <string.h>

#include "mp8.h"


/*
 * basicFlood -- wrapper for flood filling recursively from a point until 
 *               reaching white or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
// basicflood should initialize the outred and by calling the recurse to justify which point is reachable
// and by looking outred to fill the outred and outgreen and outblue
void 
basicFlood (int32_t width, int32_t height,
	    const uint8_t* inRed, const uint8_t* inGreen, 
	    const uint8_t* inBlue, 
	    int32_t startX, int32_t startY, 
	    uint8_t floodR, uint8_t floodG, uint8_t floodB,
	    uint8_t* outRed, uint8_t* outGreen, 
	    uint8_t* outBlue)
{       
	     //first to initialize the outred，blue,green
		//  for (int i=0;i<height;i++){
		// 	for (int j=0; j<width; j++){
		// 		outRed[j+i* width]=0;
				
		// 	}
		//  }
		memset(outRed,0,width*height*sizeof(uint8_t)); // use memset to initialize the outredf
		 basicRecurse(width, height,inRed, inGreen, inBlue, startX, startY,outRed);
		 for (int i=0;i<height;i++){
			for (int j=0; j<width; j++){ // look through all the point
				if (outRed[j+i*width] !=0){ // indicate outred is flooded and have been reached
                   outRed[j+i * width]=floodR;
				   outGreen[j+i * width]=floodG;
				   outBlue[j+i * width]=floodB;
				}
				else // havenn't reached then it have its  previous color
				{
				outRed[j+i*width]=inRed[j+i*width]; 
				outGreen[j+i*width]=inGreen[j+i*width];
				outBlue[j+i*width]=inBlue[j+i*width];
				}
			}
		 }

}


/*
 * colorsWithinDistSq -- returns 1 iff two colors are within Euclidean
 *                       distance squared of one another in RGB space
 * INPUTS: r1 -- red component of color 1
 *         g1 -- green component of color 1
 *         b1 -- blue component of color 1
 *         r2 -- red component of color 2
 *         g2 -- green component of color 2
 *         b2 -- blue component of color 2
 *         distSq -- maximum distance squared for the check
 * RETURN VALUE: 1 if the sum of the squares of the differences in the 
 *               three components is less or equal to distSq; 0 otherwise
 * SIDE EFFECTS: none
 */
// disSq is squared dis =(r1-r2)*(r1-r2)+(g1-g2)*(g1-g2)+(b2-b1)*(b2-b1)
int32_t
colorsWithinDistSq (uint8_t r1, uint8_t g1, uint8_t b1,
                    uint8_t r2, uint8_t g2, uint8_t b2, uint32_t distSq)
{
	int dist1;
	dist1= (r1-r2)*(r1-r2)+(g1-g2)*(g1-g2)+(b2-b1)*(b2-b1);
	if (dist1<=distSq){
    return 1; // successful
	}
	return 0; //fail
}


/*
 * greyFlood -- wrapper for flood filling recursively from a point until 
 *              reaching near-white pixels or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 *         distSq -- maximum distance squared between white and boundary
 *                   pixel color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
// it is similiar to basicrecurse we just need to change the recurse
void 
greyFlood (int32_t width, int32_t height,
	   const uint8_t* inRed, const uint8_t* inGreen, 
	   const uint8_t* inBlue, 
	   int32_t startX, int32_t startY, 
	   uint8_t floodR, uint8_t floodG, uint8_t floodB, uint32_t distSq,
	   uint8_t* outRed, uint8_t* outGreen, 
	   uint8_t* outBlue)
{
	// for (int i=0;i<height;i++){
	// 		for (int j=0; j<width; j++){
	// 			outRed[j+i* width]=0;
				
	// 		}
	// 	 }
	memset(outRed,0,width*height*sizeof(uint8_t));
    greyRecurse(width,height, inRed, inGreen,inBlue,startX,startY,distSq,outRed); //call grey recurse

	for (int i=0;i<height;i++){
			for (int j=0; j<width; j++){
				if (outRed[j+i*width] !=0){ // indicate outred is flooded and have been reached
                   outRed[j+i * width]=floodR;
				   outGreen[j+i * width]=floodG;
				   outBlue[j+i * width]=floodB;
				}
				else // haven't reached
				{
				outRed[j+i*width]=inRed[j+i*width];
				outGreen[j+i*width]=inGreen[j+i*width];
				outBlue[j+i*width]=inBlue[j+i*width];
				}
			}
	}
}


/*
 * limitedFlood -- wrapper for flood filling recursively from a point until 
 *                 reaching pixels too different (in RGB color) from the 
 *                 color at the flood start point, too far away 
 *                 (> 35 pixels), or beyond the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 *         distSq -- maximum distance squared between pixel at origin 
 *                   and boundary pixel color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
// it is similiar we just need to call another recurse and change the recurse condition 
// we will use dis from orig point to judge
void 
limitedFlood (int32_t width, int32_t height,
	      const uint8_t* inRed, const uint8_t* inGreen, 
	      const uint8_t* inBlue, 
	      int32_t startX, int32_t startY, 
	      uint8_t floodR, uint8_t floodG, uint8_t floodB, uint32_t distSq,
	      uint8_t* outRed, uint8_t* outGreen, 
	      uint8_t* outBlue)
{
	// for (int i=0;i<height;i++){
	// 		for (int j=0; j<width; j++){
	// 			outRed[j+i* width]=0;
				
	// 		}
	// 	 }
	memset(outRed,0,width*height*sizeof(uint8_t)); //initialize the outred
    limitedRecurse(width,height, inRed, inGreen,inBlue,startX,startY,startX,startY,distSq,outRed);

	for (int i=0;i<height;i++){
			for (int j=0; j<width; j++){
				if (outRed[j+i*width] !=0){ // the point that have reached will be flooded
                   outRed[j+i * width]=floodR;
				   outGreen[j+i * width]=floodG;
				   outBlue[j+i * width]=floodB;
				}
				else // the poin that haven't been reached
				{
				outRed[j+i*width]=inRed[j+i*width];
				outGreen[j+i*width]=inGreen[j+i*width];
				outBlue[j+i*width]=inBlue[j+i*width];
				}
			}
	}
}

	


