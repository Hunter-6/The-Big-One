#include "Player.h"

Player::Player(SDL_Renderer* renderer, const char* texturePath, int x, int y, int width, int height)
    : GameObject(renderer, texturePath, (SCREEN_WIDTH / 2) - 10, ((SCREEN_HEIGHT / 9) * 8) - 15, width, height), m_isJumping(false), m_isAttacking(false),
      m_jumpHeight(100), m_jumpSpeed(5), m_attackCooldown(30), m_jumpVelocity(0), m_initialY(((SCREEN_HEIGHT/9)*8)-15) {
    // Khởi tạo các thuộc tính riêng của lớp Player
}

Player::~Player() {
    // Hủy bỏ bất kỳ tài nguyên nào cần thiết
}

void Player::handleInput(SDL_Event& event) {
    // Xử lý sự kiện đầu vào để điều khiển lợn
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
            case SDLK_w:
                jump();
                break;
            case SDLK_RETURN:
            case SDLK_a:
            case SDLK_LEFT:
                attackLeft();
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                attackRight();
                break;
            // Xử lý các phím điều khiển khác tùy thuộc vào yêu cầu của trò chơi
        }
    }
}

void Player::jump() {
    // Xử lý hành động nhảy của lợn
    if (!m_isJumping) {
        // Thực hiện nhảy
        m_isJumping = true;
        m_jumpVelocity = -m_jumpSpeed;
    }
}

void Player::attackLeft() {
    // Xử lý hành động tấn công bên trái của lợn
    if (!m_isAttacking) {
        // Thực hiện tấn công bên trái
        m_isAttacking = true;
        // Đặt hướng tấn công
        m_attackDirection = AttackDirection::LEFT;
    }
}

void Player::attackRight() {
    // Xử lý hành động tấn công bên phải của lợn
    if (!m_isAttacking) {
        // Thực hiện tấn công bên phải
        m_isAttacking = true;
        // Đặt hướng tấn công
        m_attackDirection = AttackDirection::RIGHT;
    }
}

void Player::update() {
    // Cập nhật trạng thái của lợn
    GameObject::update();
    if (m_isJumping) {
        m_position.y += m_jumpVelocity;
        m_jumpVelocity += GRAVITY;

        if (m_position.y >= m_initialY) {
            m_position.y = m_initialY;
            m_isJumping = false;
        }
    }

    
    if (m_isAttacking) {
        // Nếu lợn đang tấn công, thực hiện logic tấn công và cooldown
        // (ví dụ: kiểm tra va chạm với các đối tượng sói)
        m_attackCooldown--;
        if (m_attackCooldown <= 0) {
            m_isAttacking = false;
            m_attackCooldown = 30; // Reset thời gian cooldown
        }
    }
    // Điều chỉnh vị trí của chú lợn tùy theo hướng tấn công
    if (m_isAttacking) {
        switch (m_attackDirection) {
            case AttackDirection::LEFT:
                // Xử lý tấn công bên trái
                break;
            case AttackDirection::RIGHT:
                // Xử lý tấn công bên phải
                break;
            // Xử lý các hướng tấn công khác tùy thuộc vào yêu cầu của trò chơi
        }
    }
}

void Player::render() {
    // Vẽ lợn lên màn hình
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_position);

    //vẽ tạm hình vuôgn 
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    SDL_Rect rect = {m_position.x, m_position.y, m_position.w, m_position.h};
    SDL_RenderDrawRect(m_renderer, &rect);
}
