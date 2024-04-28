#include "GameObject.h"
#include <SDL_image.h>
#include <iostream>

GameObject::GameObject(SDL_Renderer* renderer, const char* texturePath, int x, int y, int width, int height)
    : m_renderer(renderer) {
    // Load texture từ file
    SDL_Surface* surface = IMG_Load(texturePath);
    if (!surface) {
        std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
        // Xử lý lỗi tải texture
    }
    m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    // Thiết lập vị trí của đối tượng
    m_position.x = x;
    m_position.y = y;
    m_position.w = width;
    m_position.h = height;
}

GameObject::~GameObject() {
    // Giải phóng bộ nhớ của texture
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
}

void GameObject::update() {
    // Cập nhật trạng thái của đối tượng, mặc định không làm gì
}

void GameObject::render() {
    // Vẽ đối tượng lên màn hình
    if (m_texture) {
        SDL_RenderCopy(m_renderer, m_texture, NULL, &m_position);
    }
}

SDL_Rect GameObject::getPosition() const {
    // Trả về vị trí hiện tại của đối tượng
    return m_position;
}

void GameObject::setPosition(int x, int y) {
    // Thiết lập vị trí mới cho đối tượng
    m_position.x = x;
    m_position.y = y;
}

bool GameObject::checkCollision(const SDL_Rect& otherRect) const {
    // Kiểm tra va chạm với một hình chữ nhật khác
    return SDL_HasIntersection(&m_position, &otherRect);
}
