#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

// 颜色结构体
struct Color {
    float r, g, b, a;
    
    Color interpolate(const Color& other, float t) const {
        return {
            r + (other.r - r) * t,
            g + (other.g - g) * t,
            b + (other.b - b) * t,
            a + (other.a - a) * t
        };
    }
};

// 基础图形类
class Shape {
protected:
    float x, y;           // 位置
    float vx, vy;         // 速度
    float rotation;       // 旋转角度
    float scale;         // 缩放
    float targetScale;   // 目标缩放
    Color color;         // 当前颜色
    Color targetColor;   // 目标颜色
    float rotationSpeed; // 旋转速度
    float lifespan;      // 生命周期
    float maxLifespan;   // 最大生命周期

public:
    Shape(float x, float y) : x(x), y(y), rotation(0), scale(0.0f), targetScale(1.0f) {
        // 随机速度
        float angle = (rand() / (float)RAND_MAX) * 2 * M_PI;
        float speed = (rand() % 100) / 2000.0f + 0.02f;
        vx = cos(angle) * speed;
        vy = sin(angle) * speed;
        
        // 随机颜色
        color = {
            (rand() / (float)RAND_MAX),
            (rand() / (float)RAND_MAX),
            (rand() / (float)RAND_MAX),
            0.0f
        };
        
        // 设置目标颜色
        targetColor = {
            (rand() / (float)RAND_MAX),
            (rand() / (float)RAND_MAX),
            (rand() / (float)RAND_MAX),
            1.0f
        };
        
        rotationSpeed = (rand() % 100) / 1000.0f + 0.01f;
        maxLifespan = 5.0f + (rand() % 100) / 20.0f;
        lifespan = maxLifespan;
    }
    
    virtual ~Shape() {}
    
    virtual void draw() = 0;
    
    bool update(float deltaTime) {
        // 更新位置
        x += vx * deltaTime * 60.0f;
        y += vy * deltaTime * 60.0f;
        
        // 边界碰撞
        if(x > 1.0f || x < -1.0f) vx = -vx;
        if(y > 1.0f || y < -1.0f) vy = -vy;
        
        // 更新旋转
        rotation += rotationSpeed * deltaTime * 60.0f;
        if(rotation > 360.0f) rotation -= 360.0f;
        
        // 平滑缩放
        scale = scale * 0.95f + targetScale * 0.05f;
        
        // 颜色插值
        color = color.interpolate(targetColor, 0.05f);
        
        // 更新生命周期
        lifespan -= deltaTime;
        if(lifespan < 1.0f) {
            color.a = lifespan;
            scale *= lifespan;
        }
        
        return lifespan > 0;
    }
};

// 星形类
class Star : public Shape {
    float points;
    float innerRadius;
    float outerRadius;
public:
    Star(float x, float y) : Shape(x, y), 
        points(5 + rand() % 4), 
        innerRadius(0.02f + (rand() % 100) / 2000.0f),
        outerRadius(innerRadius * 2.5f) {}

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scale, scale, 1.0f);
        
        glColor4f(color.r, color.g, color.b, color.a);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        
        for(int i = 0; i <= points * 2; i++) {
            float radius = (i % 2 == 0) ? outerRadius : innerRadius;
            float angle = i * M_PI / points;
            glVertex2f(cos(angle) * radius, sin(angle) * radius);
        }
        glEnd();
        glPopMatrix();
    }
};

// 螺旋类
class Spiral : public Shape {
    int segments;
    float radius;
    float spiralFactor;
public:
    Spiral(float x, float y) : Shape(x, y), 
        segments(100),
        radius(0.1f),
        spiralFactor(3.0f + (rand() % 100) / 50.0f) {}

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scale, scale, 1.0f);
        
        glColor4f(color.r, color.g, color.b, color.a);
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i <= segments; i++) {
            float angle = (float)i / segments * spiralFactor * M_PI * 2;
            float r = radius * (float)i / segments;
            glVertex2f(cos(angle) * r, sin(angle) * r);
        }
        glEnd();
        glPopMatrix();
    }
};

// 花形类
class Flower : public Shape {
    int petals;
    float radius;
public:
    Flower(float x, float y) : Shape(x, y),
        petals(5 + rand() % 4),
        radius(0.05f + (rand() % 100) / 1000.0f) {}

    void draw() override {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);
        glScalef(scale, scale, 1.0f);
        
        glColor4f(color.r, color.g, color.b, color.a);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        
        for(int i = 0; i <= 360; i++) {
            float angle = i * M_PI / 180.0f;
            float r = radius * (1.0f + 0.5f * sin(angle * petals));
            glVertex2f(cos(angle) * r, sin(angle) * r);
        }
        glEnd();
        glPopMatrix();
    }
};

std::vector<Shape*> shapes;
bool shouldClose = false;
float lastTime = 0.0f;

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    static double lastX = xpos;
    static double lastY = ypos;
    
    if (abs(xpos - lastX) > 5 || abs(ypos - lastY) > 5) {
        shouldClose = true;
    }
    
    lastX = xpos;
    lastY = ypos;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    shouldClose = true;
}

void addRandomShape() {
    float x = (rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    float y = (rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    
    int type = rand() % 3;
    Shape* shape = nullptr;
    
    switch(type) {
        case 0:
            shape = new Star(x, y);
            break;
        case 1:
            shape = new Spiral(x, y);
            break;
        case 2:
            shape = new Flower(x, y);
            break;
    }
    
    if(shape) shapes.push_back(shape);
}

void initShapes() {
    for(int i = 0; i < 15; i++) {
        addRandomShape();
    }
}

int main() {
    srand(time(nullptr));
    
    if (!glfwInit()) {
        return -1;
    }
    
    // 获取主显示器
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) {
        glfwTerminate();
        return -1;
    }
    
    // 获取显示器的视频模式
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) {
        glfwTerminate();
        return -1;
    }
    
    // 创建全屏窗口
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Elegant Screensaver", monitor, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetKeyCallback(window, keyCallback);
    
    // 启用混合
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // 启用抗锯齿
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    
    initShapes();
    lastTime = glfwGetTime();
    
    while (!shouldClose && !glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / (float)height;
        
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glBegin(GL_QUADS);
        glColor4f(0.0f, 0.0f, 0.1f, 1.0f);
        glVertex2f(-ratio, -1.0f);
        glVertex2f(ratio, -1.0f);
        glColor4f(0.1f, 0.0f, 0.2f, 1.0f); 
        glVertex2f(ratio, 1.0f);
        glVertex2f(-ratio, 1.0f);
        glEnd();
        
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        // 更新和绘制图形
        for(auto it = shapes.begin(); it != shapes.end();) {
            if(!(*it)->update(deltaTime)) {
                delete *it;
                it = shapes.erase(it);
            } else {
                (*it)->draw();
                ++it;
            }
        }
        
        if(shapes.size() < 15) {
            addRandomShape();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        float frameTime = 1.0f / 60.0f;
        while (glfwGetTime() < currentTime + frameTime) {
        }
    }
    
    for(auto shape : shapes) {
        delete shape;
    }
    shapes.clear();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}