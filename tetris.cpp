#include <stdio.h>
#include <Windows.h>
#define WIDTH 14        //����
#define HEIGHT 22        //����

 int block[][4][4]={
{

                {0,0,0,0},

                {1,0,0,0},

                {1,1,1,0},

                {0,0,0,0}
				
				},

        		
				{

                {0,0,1,0},

                {0,0,1,0},

                {0,1,1,0},

                {0,0,0,0}
				},

        {

                {1,1,1,0},

                {0,0,1,0},

                {0,0,0,0},

                {0,0,0,0}},

        {
                {1,1,0,0},

                {1,0,0,0},

                {1,0,0,0},

                {0,0,0,0}},


    {

{0, 0, 0, 0},

{0, 0, 1, 0},

{1, 1, 1, 0},

{0, 0, 0, 0} },  

{

{0, 1, 1, 0},

{0, 0, 1, 0},

{0, 0, 1, 0},

{0, 0, 0, 0} },   

{

{1, 1, 1, 0},

{1, 0, 0, 0},

{0, 0, 0, 0},

{0, 0, 0, 0} },   

{

{1, 0, 0, 0},

{1, 0, 0, 0},

{1, 1, 0, 0},

{0, 0, 0, 0} },


    {

{0, 0, 0, 0},

{0, 1, 0, 0},

{1, 1, 1, 0},

{0, 0, 0, 0} },  

{

{0, 0, 0, 0},

{0, 1, 0, 0},

{1, 1, 0, 0},

{0, 1, 0, 0} },   

{

{0, 0, 0, 0},

{0, 0, 0, 0},

{1, 1, 1, 0},

{0, 1, 0, 0} },   

{

{0, 0, 0, 0},

{0, 1, 0, 0},

{0, 1, 1, 0},

{0, 1, 0, 0} },



    {

{0, 1, 0, 0},

{0, 1, 0, 0},

{0, 1, 0, 0},

{0, 1, 0, 0} },  

{

{0, 0, 0, 0},

{0, 0, 0, 0},

{1, 1, 1, 1},

{0, 0, 0, 0} },   

{

{0, 1, 0, 0},

{0, 1, 0, 0},

{0, 1, 0, 0},

{0, 1, 0, 0} },   

{

{0, 0, 0, 0},

{0, 0, 0, 0},

{1, 1, 1, 1},

{0, 0, 0, 0} },


    {

{1, 1, 0, 0},

{1, 1, 0, 0},

{0, 0, 0, 0},

{0, 0, 0, 0} },  

{

{1, 1, 0, 0},

{1, 1, 0, 0},

{0, 0, 0, 0},

{0, 0, 0, 0} },   

{

{1, 1, 0, 0},

{1, 1, 0, 0},

{0, 0, 0, 0},

{0, 0, 0, 0} },   

{

{1, 1, 0, 0},

{1, 1, 0, 0},

{0, 0, 0, 0},

{0, 0, 0, 0} },




   {

{0, 0, 0, 0},

{0, 1, 1, 0},

{1, 1, 0, 0},

{0, 0, 0, 0} },  

{

{0, 1, 0, 0},

{0, 1, 1, 0},

{0, 0, 1, 0},

{0, 0, 0, 0} },   

{

{0, 0, 0, 0},

{0, 1, 1, 0},

{1, 1, 0, 0},

{0, 0, 0, 0} },  

{

{0, 1, 0, 0},

{0, 1, 1, 0},

{0, 0, 1, 0},

{0, 0, 0, 0} }, 



    {

{0, 0, 0, 0},

{1, 1, 0, 0},

{0, 1, 1, 0},

{0, 0, 0, 0} },  

{

{0, 0, 1, 0},

{0, 1, 1, 0},

{0, 1, 0, 0},

{0, 0, 0, 0} },

{  

{0, 0, 0, 0},

{1, 1, 0, 0},

{0, 1, 1, 0},

{0, 0, 0, 0} },  

{

{0, 0, 1, 0},

{0, 1, 1, 0},

{0, 1, 0, 0},

{0, 0, 0, 0} ,


}
};



 
 

void gotoxy(int x, int y)
{

    COORD pos = { x*2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void MAP()
{
 	int arr[22][14]={{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 					{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 				};
 					for (int i = 0; i < 22;i++){
 						for(int j=0;j<14;j++){
 							if(arr[i][j]==1){
 								printf("��");
							 }
							 else if(arr[i][j]==0){
							 	printf("  ");
							 }
						 }
						printf("\n");		 
					 }

			}

int main() {
	MAP(); 
}
