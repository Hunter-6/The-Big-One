#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <string>
#include <SDL_image.h>

// Lớp cơ sở cho các đối tượng trong trò chơi

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int NUMBER_OF_LAYERS = 12;
const float LAYER_HEIGHT = 0.75f;


class GameObject {
public:
    GameObject(SDL_Renderer* renderer, const char* texturePath, int x, int y, int width, int height);
    virtual ~GameObject();

    virtual void update(); // Cập nhật trạng thái của đối tượng
    virtual void render(); // Vẽ đối tượng lên màn hình

    SDL_Rect getPosition() const; // Trả về vị trí hiện tại của đối tượng
    void setPosition(int x, int y); // Thiết lập vị trí mới cho đối tượng

    bool checkCollision(const SDL_Rect& otherRect) const; // Kiểm tra va chạm với một hình chữ nhật khác

protected:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    SDL_Rect m_position;
};

#endif // GAMEOBJECT_H
