#include <cassert>
#include <cstdio>

#include <SFML/Graphics.hpp>
#include <tmx/TMX.h>
#include <tmx/LayerVisitor.h>
#include <tmx/TileLayer.h>

static constexpr unsigned INITIAL_WIDTH = 800;
static constexpr unsigned INITIAL_HEIGHT = 600;

class Entity {
public:
  virtual void update(float dt) {
  }

  virtual void render(sf::RenderWindow& window) {
  }

};

class World : public Entity {
public:
  World(const std::string& filename)
  : m_vertices(sf::Quads) {
    bool loaded = m_texture.loadFromFile(filename);
    assert(loaded);
  }

  void addVertex(const sf::Vector2f& position, const sf::Vector2f& texCoords) {
    m_vertices.append({position, texCoords});
  }

  virtual void update(float dt) override {

  }

  virtual void render(sf::RenderWindow& window) override {
    window.draw(m_vertices, &m_texture);
  }

private:
  sf::VertexArray m_vertices;
  sf::Texture m_texture;
};



class MapVisitor : public tmx::LayerVisitor {
public:
  virtual void visitTileLayer(tmx::TileLayer& layer) {
    unsigned k = 0;
    unsigned n = 0;

    for (auto cell : layer) {
      unsigned i = k % width;
      unsigned j = k / width;

      unsigned gid = cell.getGID();
      k++;

      if(gid == 0) {
        continue;
      }

      unsigned x = i * 32;
      unsigned y = j * 32;

      tmx::TileSet *tileset = map->getTileSetFromGID(gid);
      gid = gid - tileset->getFirstGID();

      assert(tileset->hasImage());

      const tmx::Image *image = tileset->getImage();
      tmx::Size size = image->getSize();
      tmx::Rect rect = tileset->getCoords(gid, size);

      world->addVertex({ static_cast<float>(x), static_cast<float>(y) }, { static_cast<float>(rect.x), static_cast<float>(rect.y) });
      world->addVertex({ static_cast<float>(x + 32), static_cast<float>(y) }, { static_cast<float>(rect.x + rect.width), static_cast<float>(rect.y) });
      world->addVertex({ static_cast<float>(x + 32), static_cast<float>(y + 32) }, { static_cast<float>(rect.x + rect.width), static_cast<float>(rect.y + rect.height) });
      world->addVertex({ static_cast<float>(x), static_cast<float>(y + 32) }, { static_cast<float>(rect.x), static_cast<float>(rect.y + rect.height) });

      n++;
    }

    std::printf("number of cells: %u/%u\n", n, k);

  }

  tmx::Map *map;
  unsigned width;
  World *world;
};

class Hero : public Entity {
public:
  Hero(const std::string& filename) {
    bool loaded = m_texture.loadFromFile(filename);
    assert(loaded);
  }

  void setPosition(const sf::Vector2f& position) {
    m_position = position;
  }

  virtual void update(float dt) override {
  }

  virtual void render(sf::RenderWindow& window) override {
    sf::CircleShape shape(2.0f);
    shape.setPosition(m_position);
    shape.setOrigin(2.0f, 2.0f);
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);

    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    sprite.setPosition(m_position);
    sprite.scale({ 0.5f, 0.5f });
    window.draw(sprite);
  }

private:
  sf::Vector2f m_position;
  sf::Texture m_texture;
};

int main() {
  sf::RenderWindow window(sf::VideoMode(INITIAL_WIDTH, INITIAL_HEIGHT), "Perce Ciel");
  window.setKeyRepeatEnabled(false);

  tmx::Map *map = tmx::parseMapFile("../shared/PerceCiel/maps/MapBasic.tmx");

  World world("../shared/PerceCiel/maps/All.bmp");

  MapVisitor visitor;
  visitor.map = map;
  visitor.width = 2500;
  visitor.world = &world;

  map->visitLayers(visitor);

  Hero hero("../shared/PerceCiel/graphics/Characters/Player/Maya/Basic.png");


  sf::View view;

//   view.setCenter({ 40000, 6400});
//   view.setSize({ 80000, 12800 });
  view.setSize({ 1.5 * INITIAL_WIDTH, 1.5 * INITIAL_HEIGHT });


  float center_x = 152 * 32.0;
  float center_y = 236 * 32.0;



  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::Escape:
            window.close();
            break;

          case sf::Keyboard::Down:
          case sf::Keyboard::S:
            center_y += 10;
            break;
          case sf::Keyboard::Up:
          case sf::Keyboard::Z:
            center_y -= 10;
            break;
          case sf::Keyboard::Left:
          case sf::Keyboard::Q:
            center_x -= 10;
            break;
          case sf::Keyboard::Right:
          case sf::Keyboard::D:
            center_x += 10;
            break;

          default:
            break;
        }
      }
    }

    hero.setPosition({ center_x, center_y });

    view.setCenter({ center_x, center_y });
    window.setView(view);

    window.clear(sf::Color::White);
    world.render(window);
    hero.render(window);
    window.display();
  }

  delete map;

}
