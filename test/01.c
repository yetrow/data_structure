#include<stdio.h>
int main(void)
{
    short myshort = 100;
    unsigned short screenWidth=800;
    unsigned short screenHeight=600;
    
    unsigned short x=1920;
    unsigned short y=1080;

    printf("myshort= %hd\n",myshort);
    printf("the screen solution is: %hu X %hu\n",screenWidth,screenHeight);
    printf("current position is: %hu,%hu",x,y);
    int x=1;

    return 0;
}