//
//  SimpleFlowTools.h
//  TrackingManager_001
//
//  Created by erik on 25/3/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFlowTools.h"


using namespace flowTools;
class SimpleFlowTools
{

private:
//    ofFbo               flowTex_;
    
    ftOpticalFlow       opticalFlow_;
    ftVelocityField     velocityField_;
    
    // FlowTools
    int					flowWidth_;
    int					flowHeight_;
    int					drawWidth_;
    int					drawHeight_;
    
    // Time
    float				lastTime_;
    float				deltaTime_;

    bool                isUpdated_;
    bool                bUpdateVelField_;
    
    ofxPanel flowPanel_;
    float initedTime;
public:
    
//    SimpleFlowTools& operator<<(SimpleFlowTools& fTool, const ofBaseHasTexture& tex){
//        
//        fTool.updateTexture(tex);
//        return fTool;
//    }
    SimpleFlowTools& operator <<(ofBaseHasTexture& _texture)
    {
        updateTexture( _texture );
        return *this;
    }
        
    
    void setup(int _drawWidth, int _drawHeight);
    void updateTexture(ofBaseHasTexture& tex);
    void draw(int x, int y);
    
    
    ofVec2f*        getFlowVectors();
    float           getAverageFlow();

    ///
    /// Get average flow vector inside a rect.
    /// @param _rect area of the average vector. from 0.0 to 1.0
    /// @return 2d vector of the optical flow.
    ///
    ofVec2f         getAvgFlowVector(const ofRectangle& _rect);

    ///
    /// Get average flow vector inside a rect.
    /// @param _pos position of the circle area. from 0.0 to 1.0
    /// @param _r radius of the circle area. from 0.0 to 1.0
    /// @return 2d vector of the optical flow.
    ///
//    ofVec2f         getAvgFlowVector(const ofVec2f& _pos, int _r);

    float           getAvgFlow(const ofRectangle& _rect);
    
    ftOpticalFlow*       opticalFlowPtr();
    ftVelocityField*     velocityFieldPtr();
    
        
    const int& drawWidth() { return drawWidth_; };
    const int& drawHeight() { return drawHeight_; };
};