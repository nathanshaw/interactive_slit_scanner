#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


    // GUI setup
    guiPanel.setup();
    guiPanel.setBackgroundColor(ofColor(0,0,0,50));
    guiPanel.setPosition(30,10);
    
    guiPanel.add(guiToggle.setup("Display GUI", true));
    guiPanel.add(horizontalSlit.setup("Horizontal", true));
    guiPanel.add(verticalSlit.setup("Vertical", false));
    guiPanel.add(radalSlit.setup("Radal", false));
    guiPanel.add(playSpeed.setup("Speed", 0.5, 0.05, 4));
    guiPanel.add(slitWidth.setup("Slit Width", 4.5, 0.2, 50));
    guiPanel.add(frameBufferSize.setup("Buffer Size", 450, 50, 1000));
    // add in option to load your own video into the program in future
    video.loadMovie("hands.mov");
    video.play();
    
    frameBufferSize = 450;
    
    mode = RADAL_SLIT;
    
    video.setSpeed(playSpeed);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Decode new frame if needed
    video.update();
    // only continue if new frame has been obtained
    if(video.isFrameNew()){
        // push the new (current) frame to the begenning of the buffer
        frames.push_front( video.getPixelsRef() );
        if ( frames.size() > frameBufferSize){
            frames.pop_back();
        }
    }
    if (!frames.empty() ) {
        if (!imagePixels.isAllocated()) {
            imagePixels = frames[0];
        }
        
        height = frames[0].getHeight();
        width = frames[0].getWidth();
        for (int y=0; y < height; y++){
            for (int x=0; x < width; x++){
                // get "slit" pixel color
                ofColor color = getSlitPixelColor(x, y);
                imagePixels.setColor(x, y, color );
            }
        }
        image.setFromPixels( imagePixels );
    }
    
    
    
    // update varaibles with the state of the GUI
    video.setSpeed(playSpeed);
    
    // brute force, needs to be replaced with something "better"
    if (horizontalSlit) {
        mode = HORIZONTAL_SLIT;
    }
    else if (verticalSlit) {
        mode = VERTICAL_SLIT;
    }
    else if (radalSlit) {
        mode = RADAL_SLIT;
    }
}

ofColor ofApp::getSlitPixelColor ( int x, int y){
    float f;
    switch (mode) {
        case RADAL_SLIT:
            f = ofDist(x, y, mouseX, mouseY) / slitWidth;
            break;
            
        case HORIZONTAL_SLIT:
            f = x / slitWidth;
            break;
            
        case VERTICAL_SLIT:
            f = y / slitWidth;
    }
    
    //Here "frame number" is computed as a float value.
    //We need it for getting a "smooth result"
    //by interpolating colors later
    //Compute two frame numbers surrounding f
    int i0 = int( f );
    int i1 = i0 + 1;
    //Compute weights of the frames i0 and i1
    float weight0 = i1 - f;
    float weight1 = 1 - weight0;
    //Limiting frame numbers by range from 0 to n=frames.size()-1
    int n = frames.size() - 1;
    i0 = ofClamp( i0, 0, n );
    i1 = ofClamp( i1, 0, n );
    //Getting the frame colors
    ofColor color0 = frames[ i0 ].getColor( x, y );
    ofColor color1 = frames[ i1 ].getColor( x, y );
    //Interpolate colors - this is the function result
    ofColor color = color0 * weight0 + color1 * weight1;
    return color;
}

//--------------------------------------------------------------
void ofApp::draw(){
    // gets us a referece to the pixel array
    // ofPixels &pixels = video.getPixelsRef();
    image.draw(0,0);
    if (guiToggle) {
        guiPanel.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 32) {
        guiToggle = !guiToggle;
    }
    // if key is H or h toggle horizontal slit
    else if (key == 72 || key == 104) {
        mode = HORIZONTAL_SLIT;
    }
    // if key is r or R trigger radal slit
    else if (key == 82 || key == 114) {
        mode = RADAL_SLIT;
    }
    // if key is V or v toggle vertical slit
    else if (key == 118 || key == 86) {
        mode = VERTICAL_SLIT;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
   
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
