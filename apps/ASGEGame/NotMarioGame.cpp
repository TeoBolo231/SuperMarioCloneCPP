
#include "NotMarioGame.hpp"

#include <Engine/FileIO.hpp>
#include <Engine/InputEvents.hpp>
#include <Engine/Keys.hpp>
#include <Engine/Logger.hpp>
#include <Engine/Sprite.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

class File; /// Initialises the game.
/// Setup your game and initialise the core components.
/// @param settings
NotMarioGame::NotMarioGame(const ASGE::GameSettings& settings) :
  OGLGame(settings),
  key_callback_id(inputs->addCallbackFnc(ASGE::E_KEY, &NotMarioGame::keyHandler, this)),
  mouse_callback_id(inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &NotMarioGame::clickHandler, this))
{
  renderer->setClearColour(ASGE::COLOURS::CORNFLOWERBLUE);
  toggleFPS();
}

/// Destroys the game.
NotMarioGame::~NotMarioGame()
{
  this->inputs->unregisterCallback(key_callback_id);
  this->inputs->unregisterCallback(mouse_callback_id);
}

/// Processes key inputs.
/// This function is added as a callback to handle the game's keyboard input.
/// For this game, calls to this function are not thread safe, so you may alter
/// the game's state but your code needs to designed to prevent data-races.
/// @param data
/// @see KeyEvent
void NotMarioGame::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());

  keymap[key->key] = key->action != ASGE::KEYS::KEY_RELEASED;

  if (key->key == ASGE::KEYS::KEY_D)
  {
    player1.move(1, player1.getWalkSpeed());
  }
  if (key->key == ASGE::KEYS::KEY_A)
  {
    player1.move(-1, player1.getWalkSpeed());
  }
  if (key->key == ASGE::KEYS::KEY_SPACE)
  {
    // Jump
  }
  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
}

/// @brief   Processes any click inputs
/// @details This function is added as a callback to handle the game's
///          mouse button input. For this game, calls to this function
///          are thread safe, so you may alter the game's state as you
///          see fit.
/// @param   data The event data relating to key input.
/// @see     ClickEvent
/// @return  void
void NotMarioGame::clickHandler(ASGE::SharedEventData /*data*/)
{
  // const auto* click = dynamic_cast<const ASGE::ClickEvent*>(data.get());

  // double x_pos = click->xpos;
  // double y_pos = click->ypos;
}

/// Updates your game and all it's components using a fixed
/// timestep. This allows calculations to resolve correctly and
/// stop physics simulations from imploding
/// https://gamedev.stackexchange.com/questions/1589/when-should-i-use-a-fixed-or-variable-time-step
/// @param us
void NotMarioGame::update(const ASGE::GameTime& us)
{
  auto gamepad = inputs->getGamePad(0);

  gamePad(us);
  mainCamera.update(*player1.getSprite());
  player1.gravity(us);
  player1.collisions(level1, gamepad);
}

/// Simulates the visuals and renders your game scenes.
/// These use a variable time-step, which allows for extra smoothing and
/// interpolation based solely on the framerate of the game.
/// @param us
void NotMarioGame::render(const ASGE::GameTime& /*us*/)
{
  level1.render();
  mainCamera.render();
  player1.render();
}

/// @brief   Handles gamePad inputs
/// @param   us
void NotMarioGame::gamePad(const ASGE::GameTime& us)
{
  auto gamepad = inputs->getGamePad(0);

  if (gamepad.is_connected)
  {
    if (std::abs(gamepad.axis[0]) > G_PAD_DEAD_ZONE)
    {
      if (gamepad.buttons[0] != 0U)
      {
        player1.move(gamepad, player1.getRunSpeed(), us);
      }
      else
      {
        player1.move(gamepad, player1.getWalkSpeed(), us);
      }
    }

    if (gamepad.buttons[1] != 0U)
    {
      player1.jump(us);
    }
  }
}
