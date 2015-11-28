
#include "Map.hpp"
#include "FileUtils.hpp"
#include <fstream>
#include <iostream>

void Map::Construct() {
  this->m_visibleMap = nullptr;
  this->m_map = nullptr;
  for (int i = 0; i < 4; i++)
    this->m_conections[i] = 0;

  this->m_width = 0;
  this->m_height = 0;
  this->m_scrollx = 0;
  this->m_scrolly = 0;
  this->m_layers = 0;
  this->m_renderWidth = 0;
  this->m_renderHeight = 0;
}

Map::Map() {
  this->Construct();
}

Map::Map(std::string filename) {
  this->Construct();
  this->load(filename);
}

void Map::setTileset (Tileset* tileset) {
  if (this->m_visibleMap != nullptr) {
    for (uint8_t i = 0; i < this->m_layers; i++) {
      this->m_visibleMap[i].loadTileset(*tileset);
    }
  }
}

void Map::load (std::string filename) {
  if (this->m_map != nullptr) {
    for (uint8_t i = 0; i < this->m_layers; i++) {
      for (uint16_t x = 0; x < this->m_width; x++) {
        delete[] this->m_map[i][x];
      }
      delete[] this->m_map[i];
    }
    delete[] this->m_map;
  }
  if (this->m_visibleMap != nullptr)
    delete[] this->m_visibleMap;

  std::ifstream file;
  if (!FileUtils::openBinary(file, filename)) std::cout << "Error Opening file" << std::endl;
  this->m_width = FileUtils::readBytesAsUINT16 (file);
  this->m_height = FileUtils::readBytesAsUINT16 (file);
  this->m_layers = FileUtils::readByteAsUINT8 (file);

  // Reserve enough memory
  // FIXME: Reverse map
  this->m_map = new uint16_t**[this->m_layers];
  this->m_visibleMap = new AbstractVisibleMap[this->m_layers];
  for (uint8_t i = 0; i < this->m_layers; i++) {
    this->m_map[i] = new uint16_t*[this->m_height];
    for (uint16_t y = 0; y < this->m_height; y++) {
      this->m_map[i][y] = new uint16_t [this->m_width];
      for (uint16_t x = 0; x < this->m_width; x++) {
        this->m_map[i][y][x] = FileUtils::readBytesAsUINT16 (file);
      }
    }
  }

}

void Map::setScroll (int16_t x, int16_t y) {
  this->m_scrollx = x;
  this->m_scrolly = y;
}

void Map::setConnections (uint16_t north, uint16_t south, uint16_t east, uint16_t west) {
  this->m_conections[0] = north;
  this->m_conections[1] = south;
  this->m_conections[2] = east;
  this->m_conections[3] = west;
}

void Map::update (sf::Time deltaTime, int16_t startTileX, int16_t startTileY, uint16_t width, uint16_t hight) {
  if (this->m_visibleMap != nullptr) {
    this->m_render = true;
    this->m_renderWidth = width;
    this->m_renderHeight = hight;
    for (uint8_t i = 0; i < this->m_layers; i++) {
      this->m_visibleMap[i].setOffset(this->m_scrollx, this->m_scrolly);

      // FIXME: Reverse map
      for (int16_t x = startTileX; x < width + startTileX; x++) {
        for (int16_t y = startTileY; y < hight + startTileY; y++) {
          if (y < this->m_height && x < this->m_width && y >= 0 && x >= 0)
            this->m_visibleMap[i].setTile(x - startTileX, y - startTileY, this->m_map[i][y][x]);
          else
            this->m_visibleMap[i].setTile(x - startTileX, y - startTileY, 0);
        }
      }
    }
  }
}

void Map::render (Game* game) {
  if (this->m_render && this->m_visibleMap != nullptr) {
    this->m_render = false;
    for (uint8_t i = 0; i < this->m_layers; i++) {
        this->m_visibleMap[i].render(game, this->m_renderWidth, this->m_renderHeight);
    }
  }
}

Map::~Map () {
  if (this->m_map != nullptr) {
    for (uint8_t i = 0; i < this->m_layers; i++) {
      for (uint16_t y = 0; y < this->m_height; y++) {
        delete[] this->m_map[i][y];
      }
      delete[] this->m_map[i];
    }
    delete[] this->m_map;
  }
  if (this->m_visibleMap != nullptr)
    delete[] this->m_visibleMap;
}

uint16_t Map::getNorthMap () {
  return this->m_conections[0];
}

uint16_t Map::getSouthMap () {
  return this->m_conections[1];
}

uint16_t Map::getEastMap (){
  return this->m_conections[2];
}

uint16_t Map::getWestMap (){
  return this->m_conections[3];
}

void Map::setID (uint16_t id) {
  this->m_id = id;
}

void Map::setTilesetID (uint16_t tid) {
  this->m_tilesetID = tid;
}

uint16_t Map::getTilesetID () {
  return this->m_tilesetID;
}

uint16_t Map::getID() {
  return this->m_id;
}

uint16_t Map::getWidth() {
  return this->m_width;
}

uint16_t Map::getHight() {
  return this->m_height;
}
