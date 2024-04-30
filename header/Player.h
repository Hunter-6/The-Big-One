#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Animation.h"

enum class AttackDirection {
    LEFT,
    RIGHT
};

class Player : public GameObject {
public:
    Player(SDL_Renderer* renderer, const char* texturePath, int x, int y, int width, int height, const std::vector<std::string>& animationPaths);
    ~Player();

    void handleInput(SDL_Event& event);
    void update(); // Cập nhật trạng thái của lợn
    void render(); // Vẽ lợn lên màn hình

    // Các phương thức khác tùy thuộc vào yêu cầu của trò chơi
    void jump();
    void stopJump();
    void attackLeft();
    void attackRight();

private:
    bool m_isJumping;
    bool m_isAttacking;
    int m_jumpHeight;
    int m_jumpSpeed;
    int m_attackCooldown;
    int m_jumpVelocity;
    int m_initialY;
    SDL_Renderer* m_renderer;
    std::vector<SDL_Texture*> m_jumpFrames;
    std::vector<std::string> m_animationPaths;
    int m_currentStatusIndex;
    Animation* m_animation;
    AttackDirection m_attackDirection;
    SDL_TimerID m_jumpTimerID;
    SDL_TimerID m_jumpTimer;
    const float GRAVITY = 1.0f;
    static Uint32 JumpTimerCallback(Uint32 interval, void* param);
};

#endif // PLAYER_H
