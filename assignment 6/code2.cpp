#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate the transformation matrix elements
void calculateTransformationMatrix(double p0_x, double p0_y, double v_x, double v_y) {
    // Calculate the length of the view up vector
    double length = sqrt(v_x * v_x + v_y * v_y);
    
    // Normalize the view up vector
    double v_x_norm = v_x / length;
    double v_y_norm = v_y / length;
    
    // Calculate u vector (perpendicular to v)
    double u_x = -v_y_norm;
    double u_y = v_x_norm;
    
    // Calculate transformation matrix elements
    // Matrix = [u_x  v_x  -p0_x*u_x - p0_y*v_x]
    //         [u_y  v_y  -p0_x*u_y - p0_y*v_y]
    //         [0    0     1                   ]
    
    double m11 = u_x;
    double m12 = v_x_norm;
    double m13 = -p0_x * u_x - p0_y * v_x_norm;
    double m21 = u_y;
    double m22 = v_y_norm;
    double m23 = -p0_x * u_y - p0_y * v_y_norm;
    
    // Display the transformation matrix
    cout << "Transformation Matrix:" << endl;
    cout << "[" << m11 << "\t" << m12 << "\t" << m13 << "]" << endl;
    cout << "[" << m21 << "\t" << m22 << "\t" << m23 << "]" << endl;
    cout << "[0\t0\t1]" << endl;
}

int main() {
    double p0_x = 1.0;  // P0 x-coordinate
    double p0_y = 2.0;  // P0 y-coordinate
    double v_x = 3.0;   // View up vector x-component
    double v_y = -4.0;  // View up vector y-component
    
    cout << "P0 = (" << p0_x << ", " << p0_y << ")" << endl;
    cout << "V = (" << v_x << ", " << v_y << ")" << endl;
    cout << endl;
    
    calculateTransformationMatrix(p0_x, p0_y, v_x, v_y);
    
    return 0;
}