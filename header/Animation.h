#ifndef ANIMATION_H
#define ANIMATION_H

#include "GameObject.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <map>

// const int FRAME_TIME = 100;

// std::vector<std::pair<std::string, std::string>> animationPaths = {
//     {"idle", "assets/Player/idles"},
//     {"Left", "assets/Player/left"},
//     {"Right", "assets/Player/attack"}
// };

class Animation {
public:
    Animation(SDL_Renderer* renderer, const std::vector<std::pair<std::string, std::string>>& animationPaths, int frameCount, int frameDuration);
    ~Animation();
    
    void update(); // Cập nhật frame hiện tại của animation
    void render(int x, int y, int width, int height); // Render frame hiện tại lên màn hình

private:
    SDL_Renderer* m_renderer;
    std::map<std::string, std::vector<SDL_Texture*>> m_animationFrames;
    std::vector<SDL_Texture*> m_frames; // Danh sách các frame ảnh
    int m_frameCount; // Số lượng frame ảnh
    int m_frameDuration; // Thời gian hiển thị của mỗi frame
    int m_currentFrameIndex; // Index của frame hiện tại
    int m_frameTime; // Thời gian hiện tại của frame
};

// Animation::Animation(SDL_Renderer* renderer, const std::string& folderPath, int frameCount, int frameDuration)
//     : m_renderer(renderer), m_frameCount(frameCount), m_frameDuration(frameDuration), m_currentFrameIndex(0), m_frameTime(0) {
//     // Load các frame ảnh từ folderPath và lưu vào một vector
//     for (int i = 0; i < frameCount; ++i) {
//         std::string imagePath = folderPath + "/Warrior_Idle_" + std::to_string(i) + ".png";
//         SDL_Surface* surface = IMG_Load(imagePath.c_str());
//         if (surface) {
//             SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//             if (texture) {
//                 m_frames.push_back(texture);
//             }
//             SDL_FreeSurface(surface);
//         }
//     }
// }

// Animation::~Animation() {
//     // Giải phóng bộ nhớ cho các frame ảnh
//     for (SDL_Texture* texture : m_frames) {
//         SDL_DestroyTexture(texture);
//     }
// }

// void Animation::update() {
//     // Cập nhật frame hiện tại dựa trên thời gian
//     m_frameTime += FRAME_TIME; // FRAME_TIME là một hằng số đại diện cho thời gian giữa các frame
//     if (m_frameTime >= m_frameDuration) {
//         m_frameTime = 0;
//         m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frameCount;
//     }
// }

// void Animation::render(int x, int y, int width, int height) {
//     // Render frame hiện tại lên màn hình
//     SDL_Rect destRect = { x, y, width, height };
//     SDL_RenderCopy(m_renderer, m_frames[m_currentFrameIndex], nullptr, &destRect);
// }


#endif // ANIMATION_H