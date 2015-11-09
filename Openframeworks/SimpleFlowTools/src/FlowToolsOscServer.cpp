//
//  FlowToolsOscServer.cpp
//  SimpleFlowTest001
//
//  Created by erik on 28/10/15.
//
//

#include "FlowToolsOscServer.h"

void FlowToolsOscServer::setup(int width, int height){
    oscReceiver.setup(4300);
//    oscReceiver.start();
//    ofAddListener(oscReceiver.messageReceived, this, &FlowToolsOscServer::onOsc);
    

    remoteIp = "";
//    oscSender.setup("192.168.0.58", 4300);
    
    fTools.setup(width, height);
}

void FlowToolsOscServer::validateSenderIp(string _ip)
{
    if(remoteIp != _ip)
    {
        remoteIp = _ip;
        oscSender.setup(remoteIp, 4300);
    }
}

void FlowToolsOscServer::createPreviewRect(ofRectangle rect)
{
    
    ofPtr<ofRectangle> preview;
    if(stackRect.size()){
        preview = stackRect.back();
        stackRect.pop_back();
    }
    else{
        preview = ofPtr<ofRectangle>(new ofRectangle);
    }
    
    ofVec2f flowSize(fTools.drawWidth(), fTools.drawHeight());
    
    preview->position = rect.position * flowSize;
    preview->width    = rect.width * flowSize.x;
    preview->height   = rect.height * flowSize.y;
    
    previewRect.push_back(preview);
}

void FlowToolsOscServer::onOsc(ofxOscMessage& m)
{
//    ofLog() << "onOsc: " << m.getAddress() << " | " << m.getRemoteIp() << ":" << m.getRemotePort();
//    return;
    string _add = m.getAddress();
    string _remoteIp = m.getRemoteIp();
    
    if (_add.find("/rect-") != string::npos
        || _add.find("/rect_") != string::npos)
    {
        
        if(m.getNumArgs() != 4) return;
        
        validateSenderIp(_remoteIp);
        
        ofRectangle rect(
            m.getArgAsFloat(0), m.getArgAsFloat(1),
            m.getArgAsFloat(2), m.getArgAsFloat(3)
        );
        
        createPreviewRect(rect);
        
        
        ofVec2f force = fTools.getAvgFlowVector(rect);
        
        if(remoteIp == "") return;
        
        ofxOscMessage outMsg;        
        outMsg.setAddress(_add + "-force");
        outMsg.addFloatArg(force.x);
        outMsg.addFloatArg(force.y);
        
        oscSender.sendMessage(outMsg);
    }
}

SimpleFlowTools& FlowToolsOscServer::operator <<(ofBaseHasTexture& _texture)
{
    fTools << _texture;
    receiveOsc();
    return fTools;
}

void FlowToolsOscServer::receiveOsc()
{
    while (oscReceiver.hasWaitingMessages())
    {
        ofxOscMessage msg;

        if (oscReceiver.getNextMessage(&msg))
        {
            onOsc(msg);
        }
        
    }
}

void FlowToolsOscServer::draw(int x, int y)
{
    fTools.draw(x, y);
    ofPushStyle();
    ofNoFill();
    ofSetColor(ofColor::red);
    while (previewRect.size())
    {
        ofPtr<ofRectangle> rect = previewRect.back();
        previewRect.pop_back();
        ofRect(*rect);
        stackRect.push_back(rect);
    }
    ofPopStyle();
}

