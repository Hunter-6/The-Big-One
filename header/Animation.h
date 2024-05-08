#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <map>
#include <string>
<<<<<<< HEAD
#include "Player.h"
=======
#include <Player.h>
>>>>>>> 1738b14fe0382c4d7ab244b7339f38bd04591d67

class Animation {
public:
    Animation(SDL_Renderer* renderer, const std::vector<std::string>& animationPaths, int frameCount, int frameDuration);
    ~Animation();

    void update(); 
    void render(int x, int y, int width, int height, PlayerState state); 

private:
    SDL_Renderer* m_renderer;
<<<<<<< HEAD
    std::map<std::string, std::vector<SDL_Texture*>> m_animationFrames;
=======
>>>>>>> 1738b14fe0382c4d7ab244b7339f38bd04591d67
    std::map<PlayerState, std::vector<SDL_Texture*>> m_animations;
    int m_frameCount; 
    int m_frameDuration; 
    int m_currentFrameIndex; 
    int m_frameTime; 
};

#endif // ANIMATION_H
