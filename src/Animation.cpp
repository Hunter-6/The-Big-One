#include "Animation.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

// Thời gian giữa các frame
const int FRAME_TIME = 5;

Animation::Animation(SDL_Renderer* renderer, const std::vector<std::pair<std::string, std::string>>& animationPaths, int frameCount, int frameDuration)
    : m_renderer(renderer), m_frameCount(frameCount), m_frameDuration(frameDuration), m_currentFrameIndex(0), m_frameTime(0) {
    
    for (const auto& entry : animationPaths) {
        const std::string& status = entry.first;
        const std::string& folderPath = entry.second;
        std::vector<SDL_Texture*> frames; 
        // Load các frame ảnh từ folderPath và lưu vào một vector
        for (int i = 0; i < frameCount; ++i) {
            std::string imagePath = folderPath + "/Warrior_" + status + std::to_string(i) + ".png";
            SDL_Surface* surface = IMG_Load(imagePath.c_str());
            if (surface) {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture) {
                    frames.push_back(texture);
                }
                SDL_FreeSurface(surface);
            }
        }
        // Lưu các frame ảnh vào một map
        m_animationFrames[status] = frames;
    }
}

Animation::~Animation() {
    // Giải phóng bộ nhớ cho các frame ảnh
    for (auto& entry : m_animationFrames) {
        for (SDL_Texture* texture : entry.second) {
            SDL_DestroyTexture(texture);
        }
    }
}

void Animation::update() {
    // Cập nhật frame hiện tại dựa trên thời gian
    m_frameTime += FRAME_TIME; // FRAME_TIME là một hằng số đại diện cho thời gian giữa các frame
    if (m_frameTime >= m_frameDuration) {
        m_frameTime = 0;
        m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frameCount;
    }
}

void Animation::render(int x, int y, int width, int height) {
    // Render frame hiện tại lên màn hình
    SDL_Rect destRect = { x, y, width, height };
    const std::string& status = m_animationPaths[m_currentStatusIndex].first;
    SDL_RenderCopy(m_renderer, m_animationFrames[status][m_currentFrameIndex], nullptr, &destRect);
}
