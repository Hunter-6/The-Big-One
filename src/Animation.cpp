#include "Animation.h"

const int FRAME_TIME = 5;

Animation::Animation(SDL_Renderer* renderer, const std::vector<std::string>& animationPaths, int frameCount, int frameDuration)
    : m_renderer(renderer), m_frameCount(frameCount), m_frameDuration(frameDuration), m_currentFrameIndex(0), m_frameTime(0) {
    
    for (const std::string& folderPath : animationPaths) {
        std::vector<SDL_Texture*> frames; 
        for (int i = 0; i < frameCount; ++i) {
            std::string imagePath = folderPath + "/Warrior_" + std::to_string(i) + ".png";
            SDL_Surface* surface = IMG_Load(imagePath.c_str());
            if (surface) {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture) {
                    frames.push_back(texture);
                }
                SDL_FreeSurface(surface);
            }
        }
        m_animationFrames[folderPath] = frames;
    }
}

Animation::~Animation() {
    for (auto& entry : m_animationFrames) {
        for (SDL_Texture* texture : entry.second) {
            SDL_DestroyTexture(texture);
        }
    }
}

void Animation::update() {
    m_frameTime += FRAME_TIME;
    if (m_frameTime >= m_frameDuration) {
        m_frameTime = 0;
        m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frameCount;
    }
}

void Animation::render(int x, int y, int width, int height) {
    for (const auto& entry : m_animationFrames) {
        const std::vector<SDL_Texture*>& frames = entry.second;
        if (m_currentFrameIndex < frames.size()) {
            SDL_Rect destRect = { x, y, width, height };
            SDL_RenderCopy(m_renderer, frames[m_currentFrameIndex], nullptr, &destRect);
        }
    }
}
