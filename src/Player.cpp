#include "Player.h"

int x = (SCREEN_WIDTH / 2) - 10;
int y = ((SCREEN_HEIGHT / 9) * 8) - 15;

Player::Player(SDL_Renderer* renderer, const std::vector<std::string>& animationPaths, int x, int y, int width, int height)
    : GameObject(renderer, "", x, y, width, height), m_isJumping(false), m_isAttacking(false), m_renderer(renderer), m_animation(nullptr),
      m_jumpHeight(100), m_jumpSpeed(1000), m_attackCooldown(15), m_jumpVelocity(0), m_initialY(y), m_animationPaths(animationPaths), m_currentStatusIndex(0)
       {
    // Khởi tạo các thuộc tính riêng của lớp Player
    m_jumpTimer = SDL_AddTimer(m_jumpSpeed, JumpTimerCallback, this);

    //animation
    if (!m_animationPaths.empty()){
        m_animation = new Animation(renderer, animationPaths, 6, 130);

    }
    
}

Player::~Player() {
    // Hủy bỏ bất kỳ tài nguyên nào cần thiết
    SDL_RemoveTimer(m_jumpTimer);

    if (m_animation){
        delete m_animation;
        m_animation = nullptr;

    }
}

Uint32 Player::JumpTimerCallback(Uint32 interval, void* param) {
    Player* player = static_cast<Player*>(param);
    player->stopJump(); // Khi timer kết thúc, dừng nhảy của người chơi
    return 0;
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
                // m_animation.setAnimation("left");
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
        m_jumpVelocity = -SDL_sqrt(2 * GRAVITY * m_jumpHeight);
        m_isJumping = true;
    }
}

void Player::stopJump() {
    m_isJumping = false;
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

    if (m_animation){
        m_animation->update();
    }

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
}

void Player::render() {

    GameObject::render();

    if (m_animation){
        m_animation->render(m_position.x-35, m_position.y-45, m_position.w + 79, m_position.h + 44);
    }
    // Vẽ lợn lên màn hình
    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_position);

    //vẽ tạm hình vuôgn 
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    SDL_Rect rect = {m_position.x, m_position.y, m_position.w, m_position.h};
    SDL_RenderDrawRect(m_renderer, &rect);
}
