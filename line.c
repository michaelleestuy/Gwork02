#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>


void linemaker(char image[500][500], int x, int y, int ex, int ey){
  int dx = ex - x;
  int dy = ey - y;

  
  
  if( (dx < 0 && dy < 0) || (dx > 0 && dy < 0) || (dx == 0 && dy < 0) || (dy == 0 && dx < 0)){
    int tx = x;
    int ty = y;
    x = ex;
    y = ey;
    ex = tx;
    ey = ty;

    dx = ex - x;
    dy = ey - y;
  }
  
  int c = dx * y - dy * x;

  if(dy > 0 && dx < 0){
    int d =  2 * dy * (x + 1) - dx * (2 * y + 1) + 2 * c;

    if(dx + dy <= 0){
       while(x >= ex){
	 image[x][y] = 'r';
	 if(d < 0){
	   d -= 2 * dx;
	   y++;
	 }
	 d -= 2 * dy;
	 x--;
       }
    }
    else{
      while(y <= ey){
	 image[x][y] = 'r';
	 if(d > 0){
	   d -= 2 * dy;
	   x--;
	 }
	 d -= 2 * dx;
	 y++;
       }
    }

  }


  
  
  else if(dx >= dy){

    int d =  2 * dy * (x + 1) - dx * (2 * y + 1) + 2 * c;
   
    while(x <= ex){
      image[x][y] = 'r';
      if(d > 0){
	d -= 2 * dx;
	y++;
      }
      d += 2 * dy;
      x++;
    }
  }
  
  else if(dy > dx){
    int d =  dy * (2 * x + 1) - dx * (2 * y) + 2 * c;
   
    while(y <= ey){
      image[x][y] = 'r';
      if(d < 0){
	d += 2 * dy;
	x++;
      }
      d -= 2 * dx;
      y++;
    }
  }
}

void drawlines(char * file){
  int b = open(file, O_CREAT | O_WRONLY | O_APPEND, 888);

  char image[500][500];
  int i;
  int j;
  for(i = 0; i < 500; i++){
    for(j = 0; j < 500; j++){
      image[i][j] = 'g';
    }
  }
  


  
  linemaker(image, 250, 250, 0, 0);
  linemaker(image, 250, 250, 250, 0);
  linemaker(image, 250, 250, 500, 0);
  linemaker(image, 250, 250, 500, 250);

  linemaker(image, 250, 250, 500, 500);
  linemaker(image, 250, 250, 250, 500);
  linemaker(image, 250, 250, 0, 500);
  linemaker(image, 250, 250, 0, 250);
  
  
  linemaker(image, 250, 250, 125, 0);
  linemaker(image, 250, 250, 375, 0);
  linemaker(image, 250, 250, 500, 125);
  linemaker(image, 250, 250, 500, 375);

  linemaker(image, 250, 250, 375, 500);
  linemaker(image, 250, 250, 125, 500);
  linemaker(image, 250, 250, 0, 375);
  linemaker(image, 250, 250, 0, 125);
  
  write(b, "P3 500 500 255", sizeof("P3 500 500 255"));

  for(i = 0; i < 500; i++){
    for(j = 0; j < 500; j++){
      if(image[i][j] == 'g')
	write(b, "0 255 0", sizeof("0 255 0"));
      if(image[i][j] == 'r')
	write(b, "255 0 0", sizeof("255 0 0"));
    }
  }
  
}



int main(){
  drawlines("basic.ppm");
  return 0;

}
