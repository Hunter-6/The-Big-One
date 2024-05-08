#include "Animation.h"

const int FRAME_TIME = 5; // Adjust as needed

Animation::Animation(SDL_Renderer* renderer, const std::vector<std::string>& animationPaths, int frameCount, int frameDuration)
    : m_renderer(renderer),
      m_frameCount(frameCount),
      m_frameDuration(frameDuration),
      m_currentFrameIndex(0),
      m_frameTime(0)
{
    // Load animations based on PlayerState
    for (const std::string& folderPath : animationPaths) {
        PlayerState state = getStateFromPath(folderPath);
        std::vector<SDL_Texture*> frames;

        for (int i = 0; i < frameCount; ++i) {
            std::string imagePath = folderPath + "/Warrior_" + std::to_string(i) + ".png";
            SDL_Surface* surface = IMG_Load(imagePath.c_str()); 
            if (surface) {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                frames.push_back(texture);
                SDL_FreeSurface(surface); 
            } 
        }

        m_animations[state] = frames; 
    }
}

// Hàm giải phóng tài nguyên animation
Animation::~Animation() {
<<<<<<< HEAD
    for (auto& animationPair : m_animations) {
        for (SDL_Texture* texture : animationPair.second) {
=======
    for (auto& entry : m_animations) {
        for (SDL_Texture* texture : entry.second) {
>>>>>>> 1738b14fe0382c4d7ab244b7339f38bd04591d67
            SDL_DestroyTexture(texture);
        }
    }
}

// Hàm cập nhật animation
void Animation::update() {
    // Cập nhật thời gian cho animation
    m_frameTime += SDL_GetTicks();

    // Chuyển đến khung hình tiếp theo khi đủ thời gian
    if (m_frameTime >= m_frameDuration) {
        m_frameTime -= m_frameDuration;
        m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frameCount;
    }
}

<<<<<<< HEAD
// Hàm render animation
void Animation::render(int x, int y, int width, int height) {
    // Lấy các khung hình animation phù hợp với currentState
    std::vector<SDL_Texture*>& frames = m_animations[currentState];

    // Hiển thị khung hình animation hiện tại
    if (m_currentFrameIndex < frames.size()) {
        SDL_Rect destRect = { x, y, width, height };
        SDL_RenderCopy(m_renderer, frames[m_currentFrameIndex], nullptr, &destRect); 
    }
}

// Hàm lấy PlayerState từ đường dẫn thư mục animation
PlayerState Animation::getStateFromPath(const std::string& path) {
    if (path.find("idles") != std::string::npos) {
        return PlayerState::IDLE;
    } else if (path.find("left") != std::string::npos) {
        return PlayerState::MOVING_LEFT;
    } else if (path.find("right") != std::string::npos) {
        return PlayerState::MOVING_RIGHT;
    } else if (path.find("attack_left") != std::string::npos) {
        return PlayerState::ATTACKING_LEFT;
    } else if (path.find("attack_right") != std::string::npos) {
        return PlayerState::ATTACKING_RIGHT;
    } else {
        return PlayerState::IDLE; // Giá trị mặc định
=======
void Animation::render(int x, int y, int width, int height, PlayerState state) {
    std::vector<SDL_Texture*>& frames = m_animations[state];

    if ( m_currentFrameIndex < frames.size()) {
        SDL_Rect desRect = {x,y, width, height};
        SDL_RenderCopy(m_renderer, frames[m_currentFrameIndex], nullptr, &desRect);
>>>>>>> 1738b14fe0382c4d7ab244b7339f38bd04591d67
    }
}
