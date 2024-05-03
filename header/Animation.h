#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <map>
#include <string>

class Animation {
public:
    Animation(SDL_Renderer* renderer, const std::vector<std::string>& animationPaths, int frameCount, int frameDuration);
    ~Animation();

    void update(); 
    void render(int x, int y, int width, int height); 

private:
    SDL_Renderer* m_renderer;
    std::map<std::string, std::vector<SDL_Texture*>> m_animationFrames;
    int m_frameCount; 
    int m_frameDuration; 
    int m_currentFrameIndex; 
    int m_frameTime; 
};

#endif // ANIMATION_H
