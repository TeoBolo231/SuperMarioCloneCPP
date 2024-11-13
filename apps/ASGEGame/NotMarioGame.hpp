#pragma once

#include <ASGEGameLib/GComponent.hpp>
//#include <Engine/OGLGame.hpp>
//#include <Engine/Sprite.hpp>
//#include <random>
//#include <vector>
#include <Camera.h>
#include <Level.h>
#include <Player.h>

class NotMarioGame : public ASGE::OGLGame
{
 public:
  explicit NotMarioGame(const ASGE::GameSettings& settings);
  ~NotMarioGame() override;
  NotMarioGame(const NotMarioGame&) = delete;
  NotMarioGame& operator=(const NotMarioGame&) = delete;

 private:
  void keyHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData /*data*/);
  void update(const ASGE::GameTime& us) override;
  void render(const ASGE::GameTime& us) override;
  void gamePad(const ASGE::GameTime& us);

 private:
  Level level1      = Level(*renderer, "/data/map/World_Map.tmx");
  Player player1    = Player(*renderer, "/data/img/mario-luigi-bordered.png");
  Camera mainCamera = Camera(*renderer);

  std::string key_callback_id{};
  std::string mouse_callback_id{};
  std::map<int, bool> keymap{};

  const float G_PAD_DEAD_ZONE = 0.2F;
};
