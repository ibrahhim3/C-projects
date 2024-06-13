#include <stdio.h>
#include <math.h>
#define NUM_SAMPLES 10  // Number of training samples for each class
#define EPSILON 0.001  // A small floating-point number to avoid divide-by-zero

void the_average_points(double sumxc1, double sumyc1,double sumxc2,double sumyc2);
void the_midpoint(double average_xc1,double average_yc1,double average_xc2,double average_yc2);
void the_slope_line (double average_xc1,double average_yc1,double average_xc2,double average_yc2);
void the_dist(double average_xc1,double average_yc1,double average_xc2,double average_yc2);


int main (){
    // these for the sum of class 1 , 2 
    double sumxc1=0;
    double sumxc2=0;
    double sumyc1=0;
    double sumyc2=0;
//this loop for class 1
for(int i=0; NUM_SAMPLES > i ; i++){
    printf("> ");
double x1, y1 ;
    scanf("%lf %lf", &x1, &y1);

  sumxc1+= x1;
  sumyc1+= y1;

}
//this loop for class 2
for(int i=0; NUM_SAMPLES > i ;i++){
    printf("> ");
double x2 , y2;
    scanf("%lf %lf",&x2,&y2);

  sumxc2+=x2;
  sumyc2+=y2;

}
// calling the agerage function with passing the sum of the classes x y 
the_average_points(sumxc1,sumyc1,sumxc2,sumyc2);
    
}

void  the_average_points(double sumxc1, double sumyc1,double sumxc2,double sumyc2){
// to get the average of each sum 
        double average_xc1= sumxc1 / NUM_SAMPLES;
            double average_yc1= sumyc1 / NUM_SAMPLES;
                double average_xc2= sumxc2 / NUM_SAMPLES;
                    double average_yc2= sumyc2 / NUM_SAMPLES;
// calling the midpoint to get the the midpoint (;
    the_midpoint(average_xc1,average_yc1,average_xc2,average_yc2);
//calling this funtion to get the slope 
    the_slope_line(average_xc1,average_yc1,average_xc2,average_yc2);
//this function to know in which class and the dist
    the_dist(average_xc1, average_yc1, average_xc2, average_yc2);
   
   
}
    
void the_midpoint(double average_xc1,double average_yc1,double average_xc2,double average_yc2){
//this is the calculateions to get the midpoint 
    double midpoint_x=(average_xc1+average_xc2)/2;
    double midpoint_y=(average_yc1+average_yc2)/2;

        printf("midpoint = %.1lf %.1lf \n",midpoint_x,midpoint_y);


}

void the_slope_line(double average_xc1,double average_yc1,double average_xc2,double average_yc2) {
    double the_slope=0;
    if ( average_xc1 ==  average_xc2) {
        // to avoid divide by zero, add EPSILON
        the_slope = EPSILON;
         printf("separating line slope = %.1lf",the_slope);
    }else{

        the_slope=(average_yc2-average_yc1)/(average_xc2-average_xc1);
    }
    printf("separating line slope = %.1lf",the_slope);
}


void the_dist(double average_xc1,double average_yc1,double average_xc2,double average_yc2){
double test_x,test_y;
while (1)
{
         printf("\n> ");
  int expected_input=scanf("%lf %lf",&test_x,&test_y);

    if(expected_input!=2){
        break;
    }

//the calculation to know to which class it is closser 
    double dist_of_class1=sqrt((test_x -average_xc1 ) * (test_x -average_xc1 ) + (test_y -average_yc1) * (test_y -average_yc1));
    double dist_of_class2=sqrt((test_x -average_xc2) * (test_x -average_xc2) + (test_y -average_yc2) * (test_y -average_yc2));

    if(dist_of_class1>dist_of_class2){

    printf("Class 2, distance = %.2lf\n", dist_of_class2);

}else
  printf("Class 1, distance = %.2lf\n", dist_of_class1);

}





}