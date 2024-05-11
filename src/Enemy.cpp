// #include "Enemy.h"

// Enemy::Enemy(SDL_Renderer* renderer, const char* texturePath, int x, int y, int width, int height)
//     : GameObject(renderer, texturePath, x, y, width, height), m_movementSpeed(2) {
//     // Khởi tạo các thuộc tính riêng của lớp Enemy
// }

// Enemy::~Enemy() {
//     // Hủy bỏ bất kỳ tài nguyên nào cần thiết
// }

// void Enemy::update() {
//     // Cập nhật trạng thái của kẻ thù
//     // (ví dụ: di chuyển, kiểm tra va chạm, v.v.)
// }

// void Enemy::render() {
//     // Vẽ kẻ thù lên màn hình
//     SDL_RenderCopy(m_renderer, m_texture, NULL, &m_position);
// }

// void Enemy::moveLeft() {
//     // Di chuyển kẻ thù sang trái
//     m_position.x -= m_movementSpeed;
// }

// void Enemy::moveRight() {
//     // Di chuyển kẻ thù sang phải
//     m_position.x += m_movementSpeed;
// }

// void Enemy::setMovementSpeed(int speed) {
//     // Thiết lập tốc độ di chuyển của kẻ thù
//     m_movementSpeed = speed;
// }
