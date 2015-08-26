//
//  Game.cpp
//  test
//
//  Created by Chukie on 15/8/26.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Game.h"

namespace OglLibrary {
    Game::Game()
    {
    }
    Game::~Game()
    {
    }
    
    void Game::Run()
    {
        InitializeWindow();
        InitializeOpenGL();
        Initialize();
    }
    
    void Game::Exit()
    {
    }
    void Game::Initialize()
    {
    }
    
    void Game::InitializeWindow()
    {
    }
    
    void Game::InitializeOpenGL()
    {
        
    }
    
    void Game::Shutdown()
    {
        
    }
}
