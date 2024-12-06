#import "OpenGLScreenSaverView.h"
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>

@implementation OpenGLScreenSaverView {
    NSOpenGLContext *openGLContext;
    NSOpenGLPixelFormat *pixelFormat;
    float rotation;
    float colors[3];
    BOOL isAnimating;
    float scale;
    float scaleDir;
    float colorPhase;
}

- (instancetype)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview {
    self = [super initWithFrame:frame isPreview:isPreview];
    if (self) {
        static const NSOpenGLPixelFormatAttribute attributes[] = {
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 24,
            NSOpenGLPFAAlphaSize, 8,
            0
        };
        
        pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
        if (!pixelFormat) {
            NSLog(@"Error: No OpenGL pixel format");
            return nil;
        }
        
        openGLContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
        if (!openGLContext) {
            NSLog(@"Error: No OpenGL context");
            return nil;
        }
        
        [openGLContext setView:self];
        
        // 初始化变量
        rotation = 0.0f;
        scale = 1.0f;
        colorPhase = 0.0f;
        colors[0] = 1.0f;
        colors[1] = 0.0f;
        colors[2] = 0.0f;
        
        [self setAnimationTimeInterval:1/60.0];
    }
    return self;
}

- (void)startAnimation {
    [super startAnimation];
    isAnimating = YES;
}

- (void)stopAnimation {
    [super stopAnimation];
    isAnimating = NO;
}

- (void)drawRect:(NSRect)rect {
    [openGLContext makeCurrentContext];
    
    NSRect bounds = [self bounds];
    [self setupProjection:bounds];
    [self render];
    
    [openGLContext flushBuffer];
}

- (void)animateOneFrame {
    [self setNeedsDisplay:YES];  // 使用Cocoa的绘制机制
    
    // 更新动画参数
    rotation += 1.0f;
    if (rotation > 360.0f) {
        rotation -= 360.0f;
    }
    
    scale = 0.5f + 0.3f * sinf(rotation * M_PI / 180.0f);
    
    // 更新颜色
    colorPhase += 0.01f;
    if (colorPhase > 2.0f * M_PI) {
        colorPhase -= 2.0f * M_PI;
    }
    
    colors[0] = (sinf(colorPhase) + 1.0f) * 0.5f;
    colors[1] = (sinf(colorPhase + 2.0f * M_PI / 3.0f) + 1.0f) * 0.5f;
    colors[2] = (sinf(colorPhase + 4.0f * M_PI / 3.0f) + 1.0f) * 0.5f;
}

- (void)initGL {
    // 初始化OpenGL上下文
    openGLContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
}

- (void)setupProjection:(NSRect)bounds {
    glViewport(0, 0, bounds.size.width, bounds.size.height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspect = bounds.size.width / bounds.size.height;
    if (bounds.size.width >= bounds.size.height) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

- (void)render {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw star
    glColor3f(colors[0], colors[1], colors[2]);
    [self drawStarAtX:0.0f y:0.0f size:0.5f];
    
    // Draw hexagon
    glColor3f(colors[1], colors[2], colors[0]);
    [self drawPolygonAtX:0.0f y:0.0f size:0.3f sides:6];
    
    // Draw points
    glPushMatrix();
    glScalef(scale, scale, 1.0f);
    
    glPointSize(3.0f);
    glColor3f(colors[2], colors[0], colors[1]);
    glBegin(GL_POINTS);
    for (int i = 0; i < 36; i++) {
        float angle = (10.0f * i + rotation) * M_PI / 180.0f;
        float x = 0.7f * cos(angle);
        float y = 0.7f * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    
    glPopMatrix();
}

- (void)drawStarAtX:(float)x y:(float)y size:(float)size {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);
    
    glBegin(GL_LINES);
    for (int i = 0; i < 5; i++) {
        float angle1 = (72.0f * i - rotation) * M_PI / 180.0f;
        float angle2 = (72.0f * (i + 2) - rotation) * M_PI / 180.0f;
        
        float x1 = size * cos(angle1);
        float y1 = size * sin(angle1);
        float x2 = size * cos(angle2);
        float y2 = size * sin(angle2);
        
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();
    
    glPopMatrix();
}

- (void)drawPolygonAtX:(float)x y:(float)y size:(float)size sides:(int)sides {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(-rotation * 0.5f, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, 1.0f);
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < sides; i++) {
        float angle = (360.0f / sides * i) * M_PI / 180.0f;
        float xPos = size * cos(angle);
        float yPos = size * sin(angle);
        glVertex2f(xPos, yPos);
    }
    glEnd();
    
    glPopMatrix();
}

- (BOOL)hasConfigureSheet {
    return NO;
}

- (NSWindow*)configureSheet {
    return nil;
}

@end
