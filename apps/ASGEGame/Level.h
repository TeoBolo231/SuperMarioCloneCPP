#ifndef NOTMARIOGAME_LEVEL_H
#define NOTMARIOGAME_LEVEL_H

#include <Engine/FileIO.hpp>
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

class Level
{
 public:
  explicit Level(ASGE::Renderer& renderer, const std::string& mapPath);

  void render();
  [[nodiscard]] const std::vector<ASGE::SpriteBounds>& getCollisionGround() const;
  [[nodiscard]] const std::vector<ASGE::SpriteBounds>& getCollisionPipe() const;
  [[nodiscard]] const std::vector<ASGE::SpriteBounds>& getCollisionBlock() const;

 private:
  ASGE::Renderer& rendererRef;
  std::vector<std::unique_ptr<ASGE::Sprite>> tiles;
  const float SIDE  = 16.0F;
  const float SCALE = 3.0F;

  ASGE::SpriteBounds exit_aabb;
  std::vector<ASGE::SpriteBounds> collision_ground;
  std::vector<ASGE::SpriteBounds> collision_pipe;
  std::vector<ASGE::SpriteBounds> collision_block;
};

#endif // NOTMARIOGAME_LEVEL_H
