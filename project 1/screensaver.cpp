#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>

class Shape {
protected:
    float x, y, rotation, scale;
    float r, g, b;
    float speed, rotationSpeed;
public:
    Shape(float x, float y);
    virtual void draw() = 0;
    virtual void update();
};

class Star : public Shape {
    float points, innerRadius, outerRadius;
public:
    Star(float x, float y);
    void draw() override;
};

class Circle : public Shape {
    float radius;
    int segments;
public:
    Circle(float x, float y);
    void draw() override;
};

std::vector<Shape*> shapes;

// Shape implementation
Shape::Shape(float x, float y) : x(x), y(y), rotation(0), scale(1.0f) {
    r = static_cast<float>(rand()) / RAND_MAX;
    g = static_cast<float>(rand()) / RAND_MAX;
    b = static_cast<float>(rand()) / RAND_MAX;
    speed = (rand() % 100) / 1000.0f + 0.01f;
    rotationSpeed = (rand() % 100) / 1000.0f + 0.01f;
}

void Shape::update() {
    rotation += rotationSpeed;
    if(rotation > 360.0f) rotation -= 360.0f;
    
    x += speed;
    if(x > 1.0f || x < -1.0f) speed = -speed;
}

// Star implementation
Star::Star(float x, float y) : Shape(x, y), points(5), innerRadius(0.02f), outerRadius(0.05f) {}

void Star::draw() {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, 1.0f);
    
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);  // center point
    
    for(int i = 0; i <= points * 2; i++) {
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;
        float angle = i * M_PI / points;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
    glPopMatrix();
}

// Circle implementation
Circle::Circle(float x, float y) : Shape(x, y), radius(0.05f), segments(32) {}

void Circle::draw() {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, 1.0f);
    
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);  // center point
    
    for(int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * M_PI / segments;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
    glPopMatrix();
}

void initShapes() {
    for(int i = 0; i < 10; i++) {
        float x = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;
        float y = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;
        
        if(i % 2 == 0)
            shapes.push_back(new Star(x, y));
        else
            shapes.push_back(new Circle(x, y));
    }
}

int main() {
    if (!glfwInit()) return -1;
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Screensaver", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // Initialize random seed
    srand(static_cast<unsigned>(time(nullptr)));
    
    // Initialize shapes
    initShapes();
    
    // Setup viewport and projection
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);
    
    while (!glfwWindowShouldClose(window)) {
        // Update and render shapes
        for(auto shape : shapes) {
            shape->update();
            shape->draw();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Cleanup
    for(auto shape : shapes) delete shape;
    shapes.clear();
    glfwTerminate();
    return 0;
}