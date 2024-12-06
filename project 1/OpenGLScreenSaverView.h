#import <ScreenSaver/ScreenSaver.h>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>

@interface OpenGLScreenSaverView : ScreenSaverView
{
    NSOpenGLContext* glContext;
}

@property (nonatomic, assign) BOOL isPreviewMode;

// 私有方法声明
- (void)drawStarAtX:(float)x y:(float)y size:(float)size;
- (void)drawPolygonAtX:(float)x y:(float)y size:(float)size sides:(int)sides;

@end
