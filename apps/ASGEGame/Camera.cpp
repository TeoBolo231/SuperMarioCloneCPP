
#include "Camera.h"
#include <Engine/Sprite.hpp>

Camera::Camera(ASGE::Renderer& renderer) : rendererRef(renderer)
{
  camera.lookAt(ASGE::Point2D(static_cast<float>(CAM_W * 0.5), static_cast<float>(CAM_H * 0.5)));
}

void Camera::render()
{
  rendererRef.setProjectionMatrix(camera.getView());
}

void Camera::update(ASGE::Sprite& player)
{
  auto look_at = ASGE::Point2D(player.xPos(), static_cast<float>(CAM_H * 0.5));
  look_at.x    = std::max(look_at.x, CAM_W * 0.5F);
  look_at.x    = std::min(look_at.x, CAM_W * 7.4F);
  camera.lookAt(ASGE::Point2D(look_at.x, look_at.y));
}
