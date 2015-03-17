#include <cassert>
#include <cstdio>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <tmx/TMX.h>
#include <tmx/LayerVisitor.h>
#include <tmx/TileLayer.h>

static constexpr unsigned INITIAL_WIDTH = 800;
static constexpr unsigned INITIAL_HEIGHT = 600;

// static constexpr float RATIO = 35.0f;
static constexpr float RATIO = 70.0f;

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

      float xf = static_cast<float>(x);
      float yf = static_cast<float>(y);
      float rectx = static_cast<float>(rect.x);
      float recty = static_cast<float>(rect.y);
      float rectw = static_cast<float>(rect.width);
      float recth = static_cast<float>(rect.height);

      world->addVertex({ xf,      yf      }, { rectx,         recty         });
      world->addVertex({ xf + 32, yf      }, { rectx + rectw, recty         });
      world->addVertex({ xf + 32, yf + 32 }, { rectx + rectw, recty + recth });
      world->addVertex({ xf,      yf + 32 }, { rectx,         recty + recth });

      b2BodyDef def;
      def.position.Set((xf + 16) / RATIO, (yf + 16) / RATIO);
      def.type = b2_staticBody;
      b2Body *body = physics->CreateBody(&def);

      b2PolygonShape shape;
      shape.SetAsBox(32 / 2.0f / RATIO, 32 / 2.0f / RATIO);

      b2FixtureDef fixture;
      fixture.shape = &shape;
      fixture.density = 1.0f;
      fixture.friction = 0.5f;
      fixture.restitution = 0.0f;

      body->CreateFixture(&fixture);

      n++;
    }

    std::printf("number of cells: %u/%u\n", n, k);

  }

  tmx::Map *map;
  unsigned width;
  World *world;
  b2World *physics;
};

class Hero : public Entity {
public:
  Hero(const std::string& filename, float x, float y, b2World& physics) {
    bool loaded = m_texture.loadFromFile(filename);
    assert(loaded);

    b2BodyDef def;
    def.position.Set(x / RATIO, y / RATIO);
    def.type = b2_dynamicBody;
    def.fixedRotation = true;
    m_body = physics.CreateBody(&def);

    b2PolygonShape shape;
    shape.SetAsBox(32 / 2.0f / RATIO, 70 / 2.0f / RATIO);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1.0f;
    fixture.friction = 0.0f;
    fixture.restitution = 0.0f;

    m_body->CreateFixture(&fixture);

//     b2PolygonShape sensorShape;
//     sensorShape.SetAsBox(16 / 2.0f / RATIO, 2 / 2.0f / RATIO);
//
//     b2FixtureDef sensor;
//     sensor.shape = ...;
//     sensor.isSensor = true;
//
//     m_sensor = m_body->CreateFixture(&sensor);
  }

  void goLeft() {
    m_body->SetLinearVelocity({ -3.0f, 0.0f });
  }

  void goRight() {
    m_body->SetLinearVelocity({ +3.0f, 0.0f });
  }

  void jump() {
    m_body->ApplyLinearImpulse({ 0.0f, -2.0f }, m_body->GetLocalCenter(), true);
  }

  virtual void update(float dt) override {
  }

  virtual void render(sf::RenderWindow& window) override {
    b2Vec2 pos = m_body->GetPosition();

//     std::printf("%f,%f  %f,%f\n", pos.x, pos.y, pos.x * RATIO, pos.y * RATIO);

    sf::CircleShape shape(2.0f);
    shape.setPosition(pos.x * RATIO, pos.y * RATIO);
    shape.setOrigin(2.0f, 2.0f);
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);

    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    sprite.setPosition(pos.x * RATIO, pos.y * RATIO);
    sprite.setOrigin(64.0f, 256.0f - 2 * 35.0f);
    sprite.scale({ 0.5f, 0.5f });
    window.draw(sprite);
  }

private:
  sf::Texture m_texture;
  b2Body *m_body;
  b2Fixture *m_sensor;
};

int main() {
  b2Vec2 gravity(0.0f, 10.0f);
  b2World physics(gravity);

  sf::RenderWindow window(sf::VideoMode(INITIAL_WIDTH, INITIAL_HEIGHT), "Perce Ciel");
  window.setKeyRepeatEnabled(false);

  tmx::Map *map = tmx::parseMapFile("../shared/PerceCiel/maps/MapBasic.tmx");

  World world("../shared/PerceCiel/maps/All.bmp");

  MapVisitor visitor;
  visitor.map = map;
  visitor.width = 2500;
  visitor.world = &world;
  visitor.physics = &physics;

  map->visitLayers(visitor);

  Hero hero("../shared/PerceCiel/graphics/Characters/Player/Maya/Basic.png", 152 * 32.0f, 230 * 32.0f, physics);


  sf::View view;

//   view.setCenter({ 40000, 6400});
//   view.setSize({ 80000, 12800 });
  view.setSize({ 1.5 * INITIAL_WIDTH, 1.5 * INITIAL_HEIGHT });


  float center_x = 152 * 32.0;
  float center_y = 230 * 32.0;

  sf::Clock clock;

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
//             center_x -= 10;
            hero.goLeft();
            break;
          case sf::Keyboard::Right:
          case sf::Keyboard::D:
//             center_x += 10;
            hero.goRight();
            break;

          case sf::Keyboard::Space:
            hero.jump();
            break;

          default:
            break;
        }
      }
    }

    // update

    sf::Time elapsed = clock.restart();

    int32 velocityIterations = 10;
    int32 positionIterations = 8;
    physics.Step(elapsed.asSeconds(), velocityIterations, positionIterations);

    world.update(elapsed.asSeconds());


    // render

    view.setCenter({ center_x, center_y });
    window.setView(view);

    window.clear(sf::Color::White);
    world.render(window);
    hero.render(window);
    window.display();
  }

  delete map;

}
