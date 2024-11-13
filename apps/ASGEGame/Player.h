
#ifndef NOTMARIOGAME_PLAYER_H
#define NOTMARIOGAME_PLAYER_H

#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>
#include <Level.h>

/*enum class PlayerState
{
  Idle,
  Walk,
  Run
};*/
class Player
{
 public:
  explicit Player(ASGE::Renderer& renderer, std::string texture);
  void render();

  void move(float direction, float speed);
  void move(ASGE::GamePadData gamepad, float speed, const ASGE::GameTime& us);
  void jump(const ASGE::GameTime& us);
  void gravity(const ASGE::GameTime& us);

  void collisions(Level& level, ASGE::GamePadData gamepad);
  bool collisionCheck(ASGE::SpriteBounds player, ASGE::SpriteBounds obj);
  void setBack(ASGE::GamePadData gamepad, ASGE::SpriteBounds obj);
  [[nodiscard]] const std::unique_ptr<ASGE::Sprite>& getSprite() const;
  [[nodiscard]] float getWalkSpeed() const;
  [[nodiscard]] float getRunSpeed() const;

 private:
  std::unique_ptr<ASGE::Sprite> sprite = nullptr;
  ASGE::Renderer& rendererRef;
  ASGE::SpriteBounds playerBB;
  const float WALK_SPEED    = 1000;
  const float RUN_SPEED     = 1500;
  const float GRAVITY_SPEED = 700;
  const float JUMP_SPEED    = 2000;
  const float SCALE         = 3;
  const float SIDE          = 16;

  // bool isGrounded;
};

#endif // NOTMARIOGAME_PLAYER_H
