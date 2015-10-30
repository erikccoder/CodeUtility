//
//  FlowToolsOscServer.hpp
//  SimpleFlowTest001
//
//  Created by erik on 28/10/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxThreadedOSCReceiver.h"
#include "SimpleFlowTools.h"



///
/// Osc Receive port is 4300.
///
class FlowToolsOscServer
{
    
private:
    
    ofxOscReceiver oscReceiver;
    ofxOscSender oscSender;
    SimpleFlowTools fTools;
    string remoteIp;
    
    vector<ofPtr<ofRectangle> > previewRect;
    vector<ofPtr<ofRectangle> > stackRect;
    
public:
    
    void setup(int width, int height);
    SimpleFlowTools& operator <<(ofBaseHasTexture& _texture);
    void draw(int x, int y);
    void validateSenderIp(string remoteIp);
    void createPreviewRect(ofRectangle rect);
    
    void receiveOsc();
    void onOsc(ofxOscMessage& m);
    
    
};