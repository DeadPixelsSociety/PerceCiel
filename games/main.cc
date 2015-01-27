#include <cstdio>

#include <SFML/Graphics.hpp>
#include <tmx/TMX.h>
#include <tmx/LayerVisitor.h>
#include <tmx/TileLayer.h>

static constexpr unsigned INITIAL_WIDTH = 800;
static constexpr unsigned INITIAL_HEIGHT = 600;

class MapVisitor : public tmx::LayerVisitor {
public:
  virtual void visitTileLayer(tmx::TileLayer& layer) {
    unsigned k = 0;
    unsigned x = 0;

    for (auto cell : layer) {
      unsigned i = k % width;
      unsigned j = k / width;

      unsigned gid = cell.getGID();
      k++;

      if(gid == 0) {
        continue;
      }

      x++;
    }

    std::printf("number of cells: %u/%u\n", x, k);

  }

  unsigned width;
};



int main() {
  sf::RenderWindow window(sf::VideoMode(INITIAL_WIDTH, INITIAL_HEIGHT), "Perce Ciel");

  tmx::Map *map = tmx::parseMapFile("shared/PerceCiel/maps/MapBasic.tmx");

  MapVisitor visitor;
  visitor.width = 2500;

  map->visitLayers(visitor);

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Red);


    window.display();
  }

  delete map;

}
