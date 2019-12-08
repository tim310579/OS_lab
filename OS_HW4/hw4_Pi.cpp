
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
// Defines precision for x and y values. More the 
// interval, more the number of significant digits 


  
int main() 
{
    	
    long long interval, i, INTERVAL = 10000000; 
    double rand_x, rand_y, origin_dist, pi; 
    long long circle_points = 0, square_points = 0; 
    interval = INTERVAL*INTERVAL;
    // Initializing rand() 
    srand(time(NULL)); 
  
    // Total Random numbers generated = possible x 
    // values * possible y values 
    for (i = 0; i < INTERVAL; i++) { 
  
        // Randomly generated x and y values 
        rand_x = (double)rand()/ (RAND_MAX); 
        rand_y = (double)rand()/ (RAND_MAX); 
  		//printf("%f", rand_x);
        // Distance between (x, y) from the origin 
        origin_dist = sqrt(rand_x * rand_x + rand_y * rand_y); 
  
        // Checking if (x, y) lies inside the define 
        // circle with R=1 
        if (origin_dist <= 1) 
            circle_points++; 
  
        // Total number of points generated 
        square_points++; 
  		
        // estimated pi after this iteration 
        
  
        // For visual understanding (Optional) 
        //cout << rand_x << " " << rand_y << " " << circle_points 
            // << " " << square_points << " - " << pi << endl << endl; 
  
        // Pausing estimation for first 10 values (Optional) 
        
    } 
    printf("%d\n", RAND_MAX);
    pi = (double)(4*circle_points)/(square_points); 
    // Final Estimated Value 
    printf("%lld %lld", circle_points, square_points);
    printf("\nFinal Estimation of Pi = %lf", pi); 
  
    return 0; 
} 
