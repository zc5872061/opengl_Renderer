//
//  GameComponent.h
//  test
//
//  Created by Chukie on 15/8/28.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#ifndef __test__GameComponent__
#define __test__GameComponent__

#pragma once

#include "Common.h"
#include "GameTime.h"

namespace Library
{
    class Game;
    class GameTime;
    
    class GameComponent
    {
        public:
            GameComponent();
            GameComponent(Game* game);
            virtual ~GameComponent();
            
            Game* GetGame();
            void SetGame(Game* game);
            bool Enabled() const;
            void SetEnabled(bool enabled);
            void SetDrawAble(bool value){mDrawAble = value;}
            bool GetDrawAble()const{return mDrawAble;}
            virtual void Initialize();
            virtual void Update(GameTime gametime);
            
        protected:
            Game* mGame;
            bool mEnabled;
        
            bool mDrawAble;
        
        private:
            GameComponent(const GameComponent& rhs);
            GameComponent& operator=(const GameComponent& rhs);
    };
}


#endif /* defined(__test__GameComponent__) */
