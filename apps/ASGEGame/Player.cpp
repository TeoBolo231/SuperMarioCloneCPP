
#include "Player.h"

Player::Player(ASGE::Renderer& renderer, std::string texture) : rendererRef(renderer)
{
  sprite = rendererRef.createUniqueSprite();

  sprite->loadTexture(texture);

  sprite->srcRect()[0] = 80;
  sprite->srcRect()[1] = 34;
  sprite->srcRect()[2] = 16;
  sprite->srcRect()[3] = 16;
  sprite->width(SIDE);
  sprite->height(SIDE);
  sprite->scale(SCALE);

  sprite->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);
}

void Player::render()
{
  rendererRef.render(*sprite);
}

void Player::move(float direction, float speed)
{
  sprite->xPos(sprite->xPos() + speed * direction);

  if (direction >= 0)
  {
    sprite->setFlipFlags(ASGE::Sprite::NORMAL);
  }
  else if (direction < 0)
  {
    sprite->setFlipFlags(ASGE::Sprite::FLIP_X);
  }
}

void Player::move(ASGE::GamePadData gamepad, float speed, const ASGE::GameTime& us)
{
  sprite->xPos(static_cast<float>(sprite->xPos() + speed * gamepad.axis[0] * us.deltaInSecs()));

  if (gamepad.axis[0] >= 0)
  {
    sprite->setFlipFlags(ASGE::Sprite::NORMAL);
  }
  else if (gamepad.axis[0] < 0)
  {
    sprite->setFlipFlags(ASGE::Sprite::FLIP_X);
  }
}

void Player::jump(const ASGE::GameTime& us)
{
  sprite->yPos(static_cast<float>(sprite->yPos() + JUMP_SPEED * -1 * us.deltaInSecs()));
}

void Player::gravity(const ASGE::GameTime& us)
{
  sprite->yPos(static_cast<float>(sprite->yPos() + GRAVITY_SPEED * 1 * us.deltaInSecs()));
}

void Player::collisions(Level& level, ASGE::GamePadData gamepad)
{
  playerBB = sprite->getWorldBounds();

  for (auto object : level.getCollisionGround())
  {
    if (collisionCheck(playerBB, object))
    {
      setBack(gamepad, object);
    }
  }
  for (auto object : level.getCollisionPipe())
  {
    if (collisionCheck(playerBB, object))
    {
      setBack(gamepad, object);
    }
  }
  for (auto object : level.getCollisionBlock())
  {
    if (collisionCheck(playerBB, object))
    {
      setBack(gamepad, object);
    }
  }
}

bool Player::collisionCheck(ASGE::SpriteBounds playerbb, ASGE::SpriteBounds obj)
{
  return playerbb.v1.x + sprite->width() * SCALE >= obj.v1.x && playerbb.v1.x <= obj.v2.x &&
         playerbb.v1.y + sprite->height() * SCALE >= obj.v1.y && playerbb.v1.y <= obj.v4.y;
}

void Player::setBack(ASGE::GamePadData gamepad, ASGE::SpriteBounds obj)
{
  if (gamepad.axis[0] > 0)
  {
    sprite->xPos(obj.v1.x - SIDE);
  }
  else
  {
    sprite->xPos(obj.v2.x);
  }

  /*if (sprite->yPos() > futPosY)
  {
    sprite->yPos(obj.v4.y);
  }
  else
  {
    sprite->yPos(obj.v1.y - SIDE);
  }*/
}

const std::unique_ptr<ASGE::Sprite>& Player::getSprite() const
{
  return sprite;
}

float Player::getWalkSpeed() const
{
  return WALK_SPEED;
}

float Player::getRunSpeed() const
{
  return RUN_SPEED;
}
