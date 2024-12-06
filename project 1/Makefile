BUNDLE_NAME = OpenGLScreensaver.saver
INSTALL_PATH = ~/Library/Screen\ Savers
EXECUTABLE = screensaver

# Common flags
CFLAGS = -Wall -O2

# macOS specific
FRAMEWORKS = -framework Cocoa -framework ScreenSaver -framework OpenGL
OBJC_FLAGS = -fobjc-arc
OBJC_SOURCES = OpenGLScreenSaverView.m
OBJC_OBJECTS = $(OBJC_SOURCES:.m=.o)

# Cross-platform OpenGL
CPP_SOURCES = screensaver.cpp
CPP_OBJECTS = $(CPP_SOURCES:.cpp=.o)
ifeq ($(shell uname), Darwin)
    GL_FLAGS = -framework OpenGL -framework GLUT
else
    GL_FLAGS = -lGL -lGLU -lglut
endif

all: native standalone

native: $(BUNDLE_NAME)

standalone: $(EXECUTABLE)

%.o: %.m
	$(CC) $(CFLAGS) $(OBJC_FLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(BUNDLE_NAME): $(OBJC_OBJECTS)
	mkdir -p $(BUNDLE_NAME)/Contents/MacOS
	$(CC) $(OBJC_OBJECTS) $(FRAMEWORKS) -bundle -o $(BUNDLE_NAME)/Contents/MacOS/OpenGLScreensaver
	cp Info.plist $(BUNDLE_NAME)/Contents/

$(EXECUTABLE): $(CPP_OBJECTS)
	$(CXX) $(CPP_OBJECTS) $(GL_FLAGS) -o $@

install: native
	@echo "Cleaning old screen saver..."
	@rm -rf ~/Library/Screen\ Savers/OpenGLScreensaver.saver
	@killall cfprefsd || true
	@echo "Installing screen saver..."
	@cp -R OpenGLScreensaver.saver ~/Library/Screen\ Savers/
	@echo "Refreshing screen saver cache..."
	@defaults write com.apple.screensaver moduleDict -dict-add path ~/Library/Screen\ Savers/OpenGLScreensaver.saver
	@defaults write com.apple.screensaver moduleDict -dict-add moduleName OpenGLScreensaver
	@killall System\ Preferences || true

clean:
	rm -f $(OBJC_OBJECTS) $(CPP_OBJECTS) $(EXECUTABLE)
	rm -rf $(BUNDLE_NAME)

.PHONY: all native standalone install clean
