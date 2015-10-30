//
//  SimpleFlowTools.cpp
//  TrackingManager_001
//
//  Created by erik on 25/3/15.
//
//

#include "SimpleFlowTools.h"

void SimpleFlowTools::setup(int _drawWidth, int _drawHeight)
{
    drawWidth_ = _drawWidth;
    drawHeight_ = _drawHeight;
    
//    flowTex_.allocate(drawWidth_, drawHeight_);
//    flowTex_.begin(); ofClear(0);   flowTex_.end();
    
    flowWidth_ = drawWidth_/4;
    flowHeight_ = drawHeight_/4;
    
    opticalFlow_.setup(flowWidth_, flowHeight_);
    
    velocityField_.allocate(flowWidth_ / 4, flowHeight_ / 4);
    
    lastTime_ = ofGetElapsedTimef();
    
    flowPanel_.setup("flowCtl", "flowCtl.xml");
    
    flowPanel_.add(opticalFlowPtr()->parameters);
    flowPanel_.add(velocityFieldPtr()->parameters);
    flowPanel_.loadFromFile(flowPanel_.getName() + ".xml");
    flowPanel_.minimizeAll();
    
    isUpdated_ = false;
    initedTime = ofGetElapsedTimef();
}


void SimpleFlowTools::updateTexture(ofBaseHasTexture& tex)
{
    if(tex.getTextureReference().getWidth() == 0
       || tex.getTextureReference().getHeight() == 0)
    {
        return;
    }
    
    float now = ofGetElapsedTimef();

    opticalFlow_.setSource(tex.getTextureReference());
    opticalFlow_.update(deltaTime_);
    
    velocityField_.setSource(opticalFlow_.getOpticalFlowDecay());


    deltaTime_ = now - lastTime_;
    lastTime_ = now;
    
    isUpdated_ = true;
}

//void SimpleFlowTools::update()
//{
//    isUpdated_ = false;
//    opticalFlow_.setSource(flowTex_.getTextureReference());
//    
//    opticalFlow_.update(deltaTime_);
//    
//    if(bUpdateVelField_)
//    {
//        velocityField_.setSource(opticalFlow_.getOpticalFlowDecay());
//        isUpdated_ = true;
//    }
//    
//    
//    deltaTime_ = ofGetElapsedTimef() - lastTime_;
//    lastTime_ = ofGetElapsedTimef();
//    bUpdateVelField_ = false;
//}



void SimpleFlowTools::draw(int x, int y)
{
    flowPanel_.draw();
    if(isUpdated_)
    {
        stringstream ss;
//        ss << "opticalFlow_.getAverageFlow: " << (int)(opticalFlow_.getAverageFlow() * 1000) / 1000.0;
        
        velocityField_.draw(x, y, drawWidth_, drawHeight_);
        
        ofDrawBitmapStringHighlight(ss.str(), 0, 10);
    }
}

ofVec2f* SimpleFlowTools::getFlowVectors()
{
    return opticalFlow_.getFlowVectors();
}
float SimpleFlowTools::getAverageFlow()
{
    return opticalFlow_.getAverageFlow();
}

//--------------------------------------------------------------
ofVec2f SimpleFlowTools::getAvgFlowVector(const ofRectangle& _rect){
    
    int x1, x2;
    int y1, y2;
    int flowWidth = opticalFlow_.getWidth();
    int flowHeight = opticalFlow_.getHeight();
    
    ofVec2f* rgVec = getFlowVectors();
    int count = 0;
    ofVec2f avgVect(0,0);
    
    x1 = MAX(0, _rect.x * flowWidth);
    x2 = MIN(flowWidth, _rect.width * flowWidth + x1);
    
    y1 = MAX(0, _rect.y * flowHeight);
    y2 = MIN(flowHeight, _rect.height * flowHeight + y1);
    
    for (int i = y1; i < y2; i++)
    {
        for (int j = x1; j < x2; j++)
        {
            avgVect += rgVec[ i*flowWidth + j];
            count++;
        }
    }
    
    return (avgVect / count);
}

//--------------------------------------------------------------
float SimpleFlowTools::getAvgFlow(const ofRectangle& _rect)
{
    return 0;
}




ftOpticalFlow*       SimpleFlowTools::opticalFlowPtr()      {   return &opticalFlow_;       }
ftVelocityField*     SimpleFlowTools::velocityFieldPtr()    {   return &velocityField_;     }
