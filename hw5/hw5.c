#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

  // struct comp { 
 	// char address[80];
 	// char phone[11]; } tc; 
 	// struct inv
 	//  {
 	//   char barcode[12]; 
 	//   float price; 
 	//   struct comp *manuf; 
 	// }; 
 	// main() 
 	// { 
 	// 	 struct inv s; 
 	// 	sprintf(tc.address,"313 Main St."); 
 	// 	strcpy(tc.phone,"3035552479"); 
 	// 	s.price=6.42; strcpy(s.barcode,"1961354128"); 
 	// 	s.manuf=&tc; 
 	// 	printf("%c %s\n",s.manuf->address[5],&(tc.phone[6])); 
//  	// } 

 struct point { int x,y; }; 
 struct rect { struct point ne,se,sw,nw; }; 


void RotateRect(struct rect *R)
{
	//rotate the rectangle clockwise by 90 degree
	//find center
	struct point center={
		(R->ne.x+R->nw.x)/2, (R->ne.y+R->se.y)/2
	};
	//rotate each point
	R->ne.x=(center.x+ (R->nw.y-center.y));
	R->ne.y=(center.y+ (center.x-R->nw.x));
	R->se.x=R->ne.x;
	R->se.y=(2*center.y-R->ne.y);

	R->nw.x= (2*center.x -R->ne.x );
	R->nw.y= R->ne.y;
	R->sw.x=R->sw.x;
	R->sw.y= R->se.y;


}

int RectArea(struct rect R)
{
	int area=0;
	area= (R.ne.x - R.nw.x)*(R.ne.y- R.se.y);
	return area;
}
 main()
 {

 	struct rect R={
 		6,4,//ne : x,y
 		6,0,//se : x,y
 		0,0,//sw : x,y
 		0,4 //nw : x,y
 	};
 	printf("ne %d %d se: %d %d nw: %d %d sw %d %d\n", R.ne.x,R.ne.y,R.se.x,R.se.y,R.nw.x,R.nw.y,R.sw.x,R.sw.y );
 	RotateRect(&R);
 	printf("Rotated rectangle:\n");
 	printf("ne %d %d se: %d %d nw: %d %d sw %d %d\n", R.ne.x,R.ne.y,R.se.x,R.se.y,R.nw.x,R.nw.y,R.sw.x,R.sw.y );

 	printf("Area: %d\n", RectArea(R));
 }

// struct Mascot {
// char *animal;
// char *vegetable;
// char *mineral;
// };
// struct Color {
// char primary[10];
// char secondary[10];
// };
// struct School {
// char *Location;
// struct Mascot *cartoon;
// struct Color theme;
// };

// int main(void)
// {
// struct School *clemson;
// // allocate space for each pointer
//  clemson =(struct School*) malloc(sizeof(struct School));
//  clemson->Location=(char *) malloc(10*sizeof(char));
//  clemson->cartoon= (Mascot *) malloc(sizeof(Mascot));
//  clemson->cartoon->animal= (char *) malloc(10*sizeof(char));
// // store info
//  memcpy( clemson->Location, "Clemson", 8);
//  memcpy( clemson->theme.primary, "Orange", 7);
//  memcpy( clemson->theme.secondary, "Purple", 7);
//  memcpy( clemson->cartoon->animal, "Tiger", 6);
// // print result
//  printf("%s\n", clemson->theme.primary);
//  printf("%s\n", clemson->theme.secondary);
//  printf("%s\n", clemson->cartoon->animal);
//  printf("%s\n", clemson->Location);
//  // free memory
//  free(clemson->cartoon->animal);
//  free(clemson->cartoon);
//  free(clemson->Location);
//  free(clemson);
// }