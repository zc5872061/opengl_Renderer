//
//  ColorHelper.h
//  test
//
//  Created by Chukie on 15/8/31.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "Common.h"
#include <random>

namespace Library
{
    class ColorHelper
    {
    public:
        static const glm::vec4 Black;
        static const glm::vec4 White;
        static const glm::vec4 Red;
        static const glm::vec4 Green;
        static const glm::vec4 Blue;
        static const glm::vec4 Yellow;
        static const glm::vec4 BlueGreen;
        static const glm::vec4 Purple;
        static const glm::vec4 CornflowerBlue;
        static const glm::vec4 Wheat;
        static const glm::vec4 LightGray;
        
        static glm::vec4 RandomColor();
        
    private:
        static std::random_device sDevice;
        static std::default_random_engine sGenerator;
        static std::uniform_real_distribution<float> sDistribution;
        
        ColorHelper();
        ColorHelper(const ColorHelper& rhs);
        ColorHelper& operator=(const ColorHelper& rhs);
    };
}
