#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager); // manager reference is passed to this assetManager...
SDL_Renderer* Game::renderer;
SDL_Event Game::event;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {

}

bool Game::IsRunning() const {
    return this->isRunning;
}


void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "ERROR Initializing SDL!" << std::endl;
        return;
    }

    window = SDL_CreateWindow(
        NULL, //title
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS // can be with border...
    );
    if (!window) {
        std::cerr << "ERROR Creating SDL WINDOW" << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(
        window,
        -1, //default driver index to output to
        0 // no other flags wanted to set...
    );
    if (!renderer) {
        std::cerr << "ERROR Creating SDL Renderer!" << std::endl;
        return;
    }

    LoadLevel(0);

    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber) {
    // ###################################################
    /* Start including new assets to the assetManager list */
    
    ////////////////// debug IMAGES created under this!!!!!!!!!!!!!!!!
    //std::string textureFilePath = "./assets/images/tank-big-right.png";
    
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());


    // ####################################################
    /* Start adding entities and also components to them */
    
    /////////////// DEBUG --- add entities...
    //debug under this...

    Entity& chopperEntity(manager.AddEntity("chopper"));
    chopperEntity.AddComponent<TransformComponent>(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0, 0, 32,32, 1);
    chopperEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    chopperEntity.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");

    Entity& tankEntity(manager.AddEntity("tank"));
    tankEntity.AddComponent<TransformComponent>(0,0, 20, 20, 32,32, 1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");

    Entity& radarEntity(manager.AddEntity("radar"));
    radarEntity.AddComponent<TransformComponent>(WINDOW_WIDTH-96, 32, 0, 0, 64, 64, 1);
    radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 90, false, true);


    // List all entitied to CONSOLE:
    manager.ListAllEntities();
}

void Game::ProcessInput() {
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT: {
        isRunning = false;
        break;
    } 
    case SDL_KEYDOWN: {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            isRunning = false;
        }
    }    
    
    default: {
        break;
        }
        
    }
}

void Game::Update() {
    // Wait until 16.6ms (60fps) has elapsed since the last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

    // deltaTime is the difference in ticks from last frame converted to seconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value (so it will not time jump if something goes wrong or it takes time to render some frame etc...)
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass.
    ticksLastFrame = SDL_GetTicks(); // SDL_GetTicks() tells the ticks from SDL_init!

    manager.Update(deltaTime); // manager calls all the entities update and the entity will call the components updates etc...


}

void Game::Render() {
    // Set the background color
    SDL_SetRenderDrawColor(renderer, 21,21,21, 255);

    // clear the back buffer
    SDL_RenderClear(renderer);


    // #######################################
    // DRAW ALL GAME OBJECTS HERE of the SCENE
    // #######################################
    
    if (manager.HasNoEntities()) {
        return;
    }    
    manager.Render();

    // ############# END OF DRAW OBJECTS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // Swap the front and back buffers!
    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}