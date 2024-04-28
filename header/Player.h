#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <SDL.h>
#include <SDL_image.h>

enum class AttackDirection {
    LEFT,
    RIGHT
};

class Player : public GameObject {
public:
    Player(SDL_Renderer* renderer, const char* texturePath, int x, int y, int width, int height);
    ~Player();

    void handleInput(SDL_Event& event);
    void update(); // Cập nhật trạng thái của lợn
    void render(); // Vẽ lợn lên màn hình

    // Các phương thức khác tùy thuộc vào yêu cầu của trò chơi
    void jump();
    void attackLeft();
    void attackRight();

private:
    // Các thuộc tính riêng tùy thuộc vào yêu cầu của lợn
    bool m_isJumping;
    bool m_isAttacking;
    int m_jumpHeight; // Độ cao của nhảy
    int m_jumpSpeed; // Tốc độ nhảy
    int m_attackCooldown; // Thời gian cooldown giữa các đợt tấn công
    int m_jumpVelocity; // Vận tốc nhảy
    int m_attackVelocity; // Vận tốc tấn công
    AttackDirection m_attackDirection;

    static const int GRAVITY = 1;
    int m_initialY; 
};

#endif // PLAYER_H
