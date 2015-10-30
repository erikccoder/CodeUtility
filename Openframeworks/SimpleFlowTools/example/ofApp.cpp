#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    cam.setDeviceID(2);
    cam.initGrabber(640, 360);
    
//    video.loadMovie("/Users/erik/Downloads/VJing with a GoPro.mp4");
//    video.play();
    
    fbo.allocate(cam.width, cam.height);
//    fTools.setup(cam.width, cam.height);
    fbo.begin();
    ofClear(0);
    fbo.end();
    
    oFlow.setup(cam.width, cam.height);
    
//    ofSetLogLevel(OF_LOG_VERBOSE);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    
//    fTools.updateTexture(cam);
//    fTools << cam;
    fbo.begin();
        cam.draw(cam.width, 0, -cam.width, cam.height);
    fbo.end();
    
//    fTools << fbo;
    oFlow << fbo;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    stringstream ss;
    ss << "frame: " << ofGetFrameNum() << endl << "";
    
//    video.draw(0, 0);
    fbo.draw(0, 0);
    oFlow.draw(0,0);
    
//    ofDrawBitmapStringHighlight(ss.str(), 0, 10);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    if(button > 0){
        ofHideCursor();
        ofShowCursor();
    }
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
