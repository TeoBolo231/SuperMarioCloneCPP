
#ifndef NOTMARIOGAME_CAMERA_H
#define NOTMARIOGAME_CAMERA_H

#include <Engine/Camera.hpp>
#include <Engine/Renderer.hpp>
class Camera
{
 public:
  explicit Camera(ASGE::Renderer& renderer);
  void render();
  void update(ASGE::Sprite& player);

 private:
  const float CAM_W = 1280;
  const float CAM_H = 720;
  ASGE::Camera camera{ CAM_W, CAM_H };
  ASGE::Renderer& rendererRef;
};

#endif // NOTMARIOGAME_CAMERA_H
