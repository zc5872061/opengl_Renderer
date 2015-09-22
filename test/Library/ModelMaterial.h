//
//  ModelMaterial.h
//  test
//
//  Created by Chukie on 15/9/17.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "Common.h"

namespace Library {
    
    class Model;
    enum TextureType
    {
        TextureTypeDifffuse = 0,
        TextureTypeSpecularMap,
        TextureTypeAmbient,
        TextureTypeEmissive,
        TextureTypeHeightmap,
        TextureTypeNormalMap,
        TextureTypeSpecularPowerMap,
        TextureTypeDisplacementMap,
        TextureTypeLightMap,
        TextureTypeEnd
    };
    
    class ModelMaterial
    {
        friend class Model;
    public:
        ModelMaterial(Model& model);
        ~ModelMaterial();
        
    protected:
        Model& mModel;
        std::string mName;
        std::map<TextureType,std::vector<std::string>*> mTextures;
    };
}
