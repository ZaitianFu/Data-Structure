/* Your code here! */
#include "maze.h"

SquareMaze::SquareMaze()
{
}

void SquareMaze::makeMaze (int width, int height)
{

  int size = height*width;
	int n =0;
	while (n<size/2){
		int x = (rand()*23412)%(width-1);
		int y = (rand()*23412)%(height-1);

		if (rand()*10>5){
			if (setofcells.find(x+y*height)!=setofcells.find(x+1+y*height)){
				setofcells.setunion((x+y*height),(x+1+y*height));
				rightWall[x+y*height] = false;
				n++;
			}
			else{
				if (setofceels.find(x+y*height)!=setofcells.find(x+(y+1)*height){
					setofcells.setunion((x+y*height),(x+(y+1)*height));
					downWall[x+y*height] = false;
					n++;
				}
			}
		}
	}



	int counterx =0;
	int countery=0;
  setofcells.addelements(width*height);
	for (int i=0; i<width*height;i++){
		if (setofcells.find(i)!=setofcells.find(i+1)&&counterx<width-1){
			rightWall[i] = false;
			setofcells.setunion(i,i+1);
		}
		else{
			rightWall[i] = true;
		}
		counterx++;
		if (setofcells.find(i)!=setofcells.find(i+width)&&countery<height-1){
			downWall[i] = false;
			setofcells.setunion(i,i+width);
		}
		else{
			downWall[i] = true;
		}




		if (counterx ==width){
			countery++;
			counterx =0;
		}

	}
}

bool SquareMaze::canTravel (int x, int y, int dir) const
{
	//right direction
	/*if(dir == 0&&x != width-1)
		return (rightWall[y*width + x] == false);
	//down direction
	if(dir == 1&&y != height-1)
		return (downWall[y*width + x] == false);
	//left direction
	if(dir == 2&&x != 0)
		return (rightWall[y*width + x-1] == false);
	//up direction
	if(dir == 3&&y != 0)
		return (downWall[(y-1)*width + x] == false);
	//else
	else
		return false;
		*/
}

void SquareMaze::setWall (int x, int y, int dir, bool exists)
{
	/*int index = (y*width)+x;
	//set right wall
	if(dir == 0&&x != width-1)
			rightWall[index] = exists;
	//set down wall
	if(dir == 1&&y != height-1)
			downWall[index] = exists;
			*/

}

vector< int > SquareMaze::solveMaze ()
{

}

PNG * SquareMaze::drawMaze () const
{

}

PNG * SquareMaze::drawMazeWithSolution ()
{


}
