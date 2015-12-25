#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define HORIZONTAL_SLIT 0
#define VERTICAL_SLIT 1
#define RADAL_SLIT 2

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int mode;
    int width;
    int height;
    
    deque<ofPixels> frames;
    // pixel array from constructing output image
    ofPixels imagePixels;
    ofImage image;
    ofVideoPlayer video;
    
    // Main processing function which computes pixel color
    ofColor getSlitPixelColor( int x, int y);
    
    // gui and user interaction
    ofxPanel guiPanel;
    ofxToggle guiToggle;
    // if there is a way to make these radio buttons do it
    ofxButton horizontalSlit;
    ofxButton verticalSlit;
    ofxButton radalSlit;
    
    ofxFloatSlider slitWidth;
    ofxFloatSlider playSpeed;
    ofxIntSlider frameBufferSize;
    
private:
    
    
};
