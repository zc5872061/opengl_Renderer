//
//  FrameBufferDemo.h
//  OglRenderer
//
//  Created by Chukie on 15/10/19.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//


//
//  testDemo.h
//  OglRenderer
//
//  Created by Chukie on 15/10/13.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "DrawableGameComponent.h"
#include "ShaderProgram.h"

using namespace Library;

namespace Rendering
{
    class FrameBufferDemo : public DrawableGameComponent
    {
    public:
        FrameBufferDemo(Game* game, Camera* camera);
        ~FrameBufferDemo();
        
        virtual void Initialize() override;
        virtual void Draw(GameTime gametime) override;
        
        void setUpVABO();
        GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);
        
        
    private:
        FrameBufferDemo();
        FrameBufferDemo(const FrameBufferDemo& rhs);
        FrameBufferDemo& operator=(const FrameBufferDemo& rhs);
        
        ShaderProgram* mFrameBufferS;
        ShaderProgram* mFrameBufferScreenS;
        GLuint mcubeVBO;
        GLuint mcubeVAO;
        GLuint mfloorVAO;
        GLuint mfloorVBO;
        GLuint mquadVAO;
        GLuint mquadVBO;
        GLuint mCubeTex;
        GLuint mFloorTex;
        GLuint mFramebuffer;
        GLuint mtextureColorbuffer;
        GLuint mRBO;
    };
}
