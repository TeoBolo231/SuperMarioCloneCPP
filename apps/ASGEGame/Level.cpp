#include "Level.h"

Level::Level(ASGE::Renderer& renderer, const std::string& mapPath) : rendererRef(renderer)
{
  ASGE::FILEIO::File tile_map;
  if (tile_map.open(mapPath))
  {
    ASGE::FILEIO::IOBuffer buffer = tile_map.read();
    std::string file_string(buffer.as_char(), buffer.length);

    tmx::Map map;
    map.loadFromString(file_string, ".");
    for (const auto& layer : map.getLayers())
    {
      Logging::ERRORS("Layer Found");
      std::cout << layer->getName() + "\n";

      if (layer->getType() == tmx::Layer::Type::Tile)
      {
        auto tile_layer = layer->getLayerAs<tmx::TileLayer>();
        float y         = 0;
        for (unsigned int row = 0; row < layer->getSize().y; ++row)
        {
          float x = 0;
          for (unsigned int col = 0; col < layer->getSize().x; ++col)
          {
            auto tile_info = tile_layer.getTiles()[row * tile_layer.getSize().x + col];
            auto tile      = map.getTilesets()[0].getTile(tile_info.ID);

            if (tile != nullptr)
            {
              auto& sprite = tiles.emplace_back(rendererRef.createUniqueSprite());
              if (sprite->loadTexture(tile->imagePath))
              {
                sprite->srcRect()[0] = static_cast<float>(tile->imagePosition.x);
                sprite->srcRect()[1] = static_cast<float>(tile->imagePosition.y);
                sprite->srcRect()[2] = static_cast<float>(tile->imageSize.x);
                sprite->srcRect()[3] = static_cast<float>(tile->imageSize.y);

                sprite->width(static_cast<float>(tile->imageSize.x));
                sprite->height(static_cast<float>(tile->imageSize.y));

                sprite->scale(SCALE);
                sprite->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);

                sprite->yPos(static_cast<float>(y));
                sprite->xPos(static_cast<float>(x));
              }
            }
            x += SIDE * SCALE;
          }
          y += SIDE * SCALE;
        }
      }

      if (layer->getType() == tmx::Layer::Type::Object)
      {
        auto object_layer = layer->getLayerAs<tmx::ObjectGroup>();
        for (const auto& object : object_layer.getObjects())
        {
          Logging::ERRORS("Object found");

          if (object.getName() == "LevelBox")
          {
            Logging::ERRORS("Found lvlbox");
          }

          if (object.getName() == "Ground")
          {
            Logging::ERRORS("Found Ground");
          }

          if (object.getName() == "Pipe")
          {
            Logging::ERRORS("Found Pipe");
          }

          if (object.getName() == "Block")
          {
            Logging::ERRORS("Found Block");
          }

          if (object.getName() == "Exit")
          {
            Logging::ERRORS("Found Exit");
          }

          if (object.getName() == "Start")
          {
            Logging::ERRORS("Found Start");
          }

          /*if (object.getName() == "Exit")
          {
            Logging::ERRORS("Found Exit");
            auto object_aabb = object.getAABB();

            exit_aabb.v1 = { object_aabb.left * SCALE, object_aabb.top * SCALE };
            exit_aabb.v2 = { (object_aabb.left + object_aabb.width) * SCALE,
                             object_aabb.top * SCALE };
            exit_aabb.v3 = { (object_aabb.left + object_aabb.width) * SCALE,
                             (object_aabb.top + object_aabb.height) * SCALE };
            exit_aabb.v4 = { object_aabb.left * SCALE,
                             (object_aabb.top + object_aabb.height) * SCALE };
          }
          if (object.getName() == "Start")
          {
            Logging::ERRORS("Found start");
            //auto object_pos = object.getPosition();

            //mario->xPos(object_pos.x);
            //mario->yPos(object_pos.y);
          }
          if (object.getName() == "Ground")
          {
            Logging::ERRORS("Found ground");
            auto object_aabb = object.getAABB();
            ASGE::SpriteBounds new_obj;

            new_obj.v1 = { object_aabb.left * SCALE, object_aabb.top * SCALE };
            new_obj.v2 = { (object_aabb.left + object_aabb.width) * SCALE,
                             object_aabb.top * SCALE };
            new_obj.v3 = { (object_aabb.left + object_aabb.width) * SCALE,
                             (object_aabb.top + object_aabb.height) * SCALE };
            new_obj.v4 = { object_aabb.left * SCALE,
                             (object_aabb.top + object_aabb.height) * SCALE };
            collision_ground.push_back(new_obj);
          }
          if (object.getName() == "Pipe")
          {
            Logging::ERRORS("Found pipe");
            auto object_aabb = object.getAABB();
            ASGE::SpriteBounds new_obj;

            new_obj.v1 = { object_aabb.left * SCALE, object_aabb.top * SCALE };
            new_obj.v2 = { (object_aabb.left + object_aabb.width) * SCALE,
                           object_aabb.top * SCALE };
            new_obj.v3 = { (object_aabb.left + object_aabb.width) * SCALE,
                           (object_aabb.top + object_aabb.height) * SCALE };
            new_obj.v4 = { object_aabb.left * SCALE,
                           (object_aabb.top + object_aabb.height) * SCALE };
            collision_pipe.push_back(new_obj);
          }
          if (object.getName() == "Block")
          {
            Logging::ERRORS("Found block");
            auto object_aabb = object.getAABB();
            ASGE::SpriteBounds new_obj;

            new_obj.v1 = { object_aabb.left * SCALE, object_aabb.top * SCALE };
            new_obj.v2 = { (object_aabb.left + object_aabb.width) * SCALE,
                           object_aabb.top * SCALE };
            new_obj.v3 = { (object_aabb.left + object_aabb.width) * SCALE,
                           (object_aabb.top + object_aabb.height) * SCALE };
            new_obj.v4 = { object_aabb.left * SCALE,
                           (object_aabb.top + object_aabb.height) * SCALE };
            collision_block.push_back(new_obj);
          }*/
        }
      }
    }
  }
}

void Level::render()
{
  for (auto& sprite : tiles)
  {
    rendererRef.render(*sprite);
  }
}

const std::vector<ASGE::SpriteBounds>& Level::getCollisionGround() const
{
  return collision_ground;
}

const std::vector<ASGE::SpriteBounds>& Level::getCollisionPipe() const
{
  return collision_pipe;
}

const std::vector<ASGE::SpriteBounds>& Level::getCollisionBlock() const
{
  return collision_block;
}
