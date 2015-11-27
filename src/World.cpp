
#include "World.hpp"
#include <fstream>
#include "FileUtils.hpp"
#include "MapMetadataParser.hpp"

void World::Construct() {
  this->m_actualMap = nullptr;
  this->m_actualNorthMap = nullptr;
  this->m_actualSouthMap = nullptr;
  this->m_actualEastMap = nullptr;
  this->m_actualWestMap = nullptr;

  this->m_actualNorthWestMap = nullptr;
  this->m_actualSouthWestMap = nullptr;
  this->m_actualNorthEastMap = nullptr;
  this->m_actualSouthEastMap = nullptr;
}

World::World() {
  this->Construct();
}
#include <iostream>
World::World(std::string filename) {
  this->Construct();
  this->load(filename);
}

void World::load (std::string filename) {
  std::ifstream file;
  if (!FileUtils::openBinary(file, filename));

  uint16_t ntilesets = FileUtils::readBytesAsUINT16(file);

  // Load tilesets in memory
  for (uint16_t i = 0; i < ntilesets; i++) {
    std::string tilesetFilename = "";
    char x = FileUtils::readByte(file);
    while ((uint8_t)x != 255 && !file.eof()) {
      tilesetFilename += x;
      x = FileUtils::readByte(file);
    }

    Tileset* tileset = new Tileset(tilesetFilename);
    this->m_tilesets[tileset->getID()] = tileset;
  }

  uint16_t nmaps = FileUtils::readBytesAsUINT16(file);

  // Load maps in memory
  for (uint16_t i = 0; i < nmaps; i++) {
    std::string mapFilename = "";
    char x = FileUtils::readByte(file);
    while ((uint8_t)x != 255 && !file.eof()) {
      mapFilename += x;
      x = FileUtils::readByte(file);
    }

    Map* map = MapMetadataParser::parse(mapFilename);
    this->m_maps[map->getID()] = map;
    this->m_maps[map->getID()]->setTileset(this->m_tilesets[map->getTilesetID()]);
  }

  file.close();
}

void World::lockSprite (AbstractSprite& sprite) {
  int16_t tilex = (WIN_X/2)/this->m_tilesets[this->m_actualMap->getTilesetID()]->getTileWide();
  int16_t tiley = (WIN_Y/2)/this->m_tilesets[this->m_actualMap->getTilesetID()]->getTileHight();
  sprite.setPosition(tilex*64, tiley*64);
}

void World::setCamera(int16_t x, int16_t y) {
  this->x = x;
  this->y = y;
}

int16_t World::getCameraX () {
  return this->x;
}

int16_t World::getCameraY () {
  return this->y;
}

void World::setActualMap (uint16_t map) {
  this->m_actualMap = this->m_maps[map];
  this->m_actualNorthMap = this->m_maps[this->m_actualMap->getNorthMap()];
  this->m_actualSouthMap = this->m_maps[this->m_actualMap->getSouthMap()];
  this->m_actualEastMap = this->m_maps[this->m_actualMap->getEastMap()];
  this->m_actualWestMap = this->m_maps[this->m_actualMap->getWestMap()];
  this->m_actualNorthWestMap = nullptr;
  this->m_actualSouthWestMap = nullptr;
  this->m_actualNorthEastMap = nullptr;
  this->m_actualSouthEastMap = nullptr;

  if (this->m_actualNorthMap != nullptr) {
    this->m_actualNorthWestMap = this->m_maps[this->m_actualNorthMap->getWestMap()];
    this->m_actualNorthEastMap = this->m_maps[this->m_actualNorthMap->getEastMap()];
  }
  if (this->m_actualSouthMap != nullptr) {
    this->m_actualSouthWestMap = this->m_maps[this->m_actualSouthMap->getWestMap()];
    this->m_actualSouthEastMap = this->m_maps[this->m_actualSouthMap->getEastMap()];
  }
  if (this->m_actualEastMap != nullptr && ((uint64_t)this->m_actualNorthEastMap & (uint64_t)this->m_actualSouthEastMap ) == 0) {
    this->m_actualNorthEastMap = this->m_maps[this->m_actualEastMap->getNorthMap()];
    this->m_actualSouthEastMap = this->m_maps[this->m_actualEastMap->getSouthMap()];
  }
  if (this->m_actualWestMap != nullptr && ((uint64_t)this->m_actualNorthWestMap & (uint64_t)this->m_actualSouthWestMap ) == 0) {
    this->m_actualNorthWestMap = this->m_maps[this->m_actualWestMap->getNorthMap()];
    this->m_actualSouthWestMap = this->m_maps[this->m_actualWestMap->getSouthMap()];
  }
/*
  if (this->m_actualNorthMap != nullptr) {
    this->m_actualNorthWestMap = this->m_maps[this->m_actualNorthMap->getWestMap()];
    this->m_actualNorthEastMap = this->m_maps[this->m_actualNorthMap->getEastMap()];
  }
  else {
    if (this->m_actualEastMap != nullptr) {
      this->m_actualNorthEastMap = this->m_maps[this->m_actualEastMap->getNorthMap()];
    }
    if (this->m_actualWestMap != nullptr) {
      this->m_actualNorthWestMap = this->m_maps[this->m_actualWestMap->getNorthMap()];
    }
  }

  if (this->m_actualSouthMap != nullptr) {
    this->m_actualSouthWestMap = this->m_maps[this->m_actualSouthMap->getWestMap()];
    this->m_actualSouthEastMap = this->m_maps[this->m_actualSouthMap->getEastMap()];
  }
  else {
    if (this->m_actualEastMap != nullptr) {
      this->m_actualSouthEastMap = this->m_maps[this->m_actualEastMap->getSouthMap()];
    }
    if (this->m_actualWestMap != nullptr) {
      this->m_actualSouthWestMap = this->m_maps[this->m_actualWestMap->getSouthMap()];
    }
  }*/

}

Map* World::getMap() {
  return this->m_actualMap;
}

void World::mapUpdate (Map* map, sf::Time deltaTime, int16_t scrollx,
  int16_t scrolly, uint16_t startx, uint16_t starty, uint16_t width, uint16_t height) {
  if (map == nullptr) return;
  map->setScroll(scrollx, scrolly);
  map->update(deltaTime, startx, starty, width, height);
}

// FIXME: Imposible Loop map
void World::update (sf::Time deltaTime) {
  if (this->m_actualMap == nullptr) return;

  uint16_t tileW = this->m_tilesets[this->m_actualMap->getTilesetID()]->getTileWide();
  uint16_t tileH = this->m_tilesets[this->m_actualMap->getTilesetID()]->getTileHight();
  uint16_t scrTx = WIN_X / tileW;
  uint16_t scrTy = WIN_Y / tileH;
  int16_t startTileX = (this->x / tileW) - scrTx / 2;
  int16_t startTileY = (this->y / tileH) - scrTy / 2;
  uint16_t with = ((this->m_actualMap->getWidth() - startTileX) >= scrTx) ? scrTx : (this->m_actualMap->getWidth() - startTileX);
  uint16_t higth = ((this->m_actualMap->getHight() - startTileY) >= scrTy) ? scrTy : (this->m_actualMap->getHight() - startTileY);
  uint16_t leftaling = (scrTx / 2) - (this->x / tileW);
  uint16_t upaling = (scrTy / 2) - (this->y / tileH);
  int16_t x = -(this->x % tileW);
  int16_t y = -(this->y % tileH);

  this->mapUpdate(this->m_actualMap, deltaTime, x, y, startTileX, startTileY, (with)+1, (higth)+1);

  if (this->m_actualEastMap != nullptr && with <= scrTx)
    this->mapUpdate(this->m_actualEastMap, deltaTime, x + with*tileW, y, 0, startTileY, scrTx - with + 1, higth+1);

  if (this->m_actualWestMap != nullptr && (this->x / tileW) < scrTx / 2)
    this->mapUpdate(this->m_actualEastMap, deltaTime, x - tileW, y,this->m_actualWestMap->getWidth() - leftaling - 1, startTileY, leftaling + 1, higth+1);

  if (this->m_actualNorthMap != nullptr && (this->y / tileH) < scrTy / 2)
    this->mapUpdate(this->m_actualNorthMap, deltaTime, x, y - tileH, startTileX, this->m_actualNorthMap->getHight() - upaling - 1, with + 1, upaling + 1);

  if (this->m_actualSouthMap != nullptr && (this->y / tileH) > scrTy / 2)
    this->mapUpdate(this->m_actualSouthMap, deltaTime, x, y + higth * tileH, startTileX, 0, with + 1, scrTy - higth + 1);

  // this->m_actualMap->setScroll(-this->x % tileW, -this->y % tileH);
  // this->m_actualMap->update(deltaTime, startTileX, startTileY, (with)+1, (higth)+1);

  /*if (this->m_actualEastMap != nullptr) {
    if (with <= (WIN_X / tileW)) {
      this->m_actualEastMap->setScroll((-(this->x % tileW)) + with*tileW, -(this->y % tileH));
      this->m_actualEastMap->update(deltaTime, 0, startTileY, (WIN_X / tileW) - with + 1, higth+1);
    }
  }*/

  /* if (this->m_actualWestMap != nullptr) {
    if ( && (this->x / tileW) < ((WIN_X / 2) / tileW)) {
      this->m_actualWestMap->setScroll((-(this->x % tileW + tileW)), -(this->y % tileH));
      this->m_actualWestMap->update(deltaTime, this->m_actualWestMap->getWidth() - leftaling - 1, startTileY, leftaling + 1, higth+1);
    }
  }*/
/*
  if (this->m_actualNorthMap != nullptr) {
    if ((this->y / tileH) < ((WIN_Y / 2) / tileH)) {
      this->m_actualEastMap->setScroll(-this->x % tileW, -(this->y % tileH + tileH));
      this->m_actualEastMap->update(deltaTime, startTileX, this->m_actualNorthMap->getHight() - upaling - 1, with + 1, upaling + 1);
    }
  }
*/
  // if (this->m_actualSouthMap != nullptr) {
  //   if ((this->y / tileH) > ((WIN_Y / 2) / tileH)) {
  //     this->m_actualSouthMap->setScroll(-this->x % tileW, -(this->y % tileH) + higth * tileH);
  //     this->m_actualSouthMap->update(deltaTime, startTileX, 0, with + 1, (WIN_Y / tileH) - higth + 1);
  //   }
  // }
  //
  // if (this->m_actualNorthWestMap != nullptr) {
  //   if (((this->x / tileW) < ((WIN_X / 2) / tileW)) && ((this->y / tileH) < ((WIN_Y / 2) / tileH))) {
  //     uint16_t leftaling = ((WIN_X / 2) / tileW) - (this->x / tileW);
  //     uint16_t upaling = ((WIN_Y / 2) / tileH) - (this->y / tileH);
  //     //std::cout << "Updating " << this->m_actualNorthWestMap->getID() << std::endl;
  //     this->m_actualEastMap->setScroll((-(this->x % tileW + tileW)), -(this->y % tileH + tileH));
  //     this->m_actualEastMap->update(deltaTime, this->m_actualWestMap->getWidth() - leftaling - 1, this->m_actualNorthMap->getHight() - upaling - 1, leftaling + 1, upaling + 1);
  //   }
  // }

  std::cout << "ID: " << this->m_actualMap->getID()-1 << std::endl;

  if (this->m_actualEastMap != nullptr && (this->x / tileW) > this->m_actualMap->getWidth() - 1) {
    this->x = 0;
    this->setActualMap(this->m_actualEastMap->getID());
  }
  if (this->m_actualWestMap != nullptr && (this->x / tileW) < 0) {
    this->x = (this->m_actualWestMap->getWidth() - 1)*tileW;
    this->setActualMap(this->m_actualWestMap->getID());
  }
  if (this->m_actualNorthMap != nullptr && (this->y / tileH) < 0) {
    this->y = (this->m_actualNorthMap->getHight() - 1)*tileH;
    this->setActualMap(this->m_actualNorthMap->getID());
  }
  if (this->m_actualSouthMap != nullptr && (this->y / tileH) > this->m_actualMap->getHight() - 1) {
    this->y = 0;
    this->setActualMap(this->m_actualSouthMap->getID());
  }
}

void World::render (Game* game) {
  //if (this->m_actualNorthWestMap != nullptr) this->m_actualNorthWestMap->render(game);
  //if (this->m_actualNorthEastMap != nullptr) this->m_actualNorthEastMap->render(game);
  //if (this->m_actualSouthWestMap != nullptr) this->m_actualSouthWestMap->render(game);
  //if (this->m_actualSouthEastMap != nullptr) this->m_actualSouthEastMap->render(game);
  if (this->m_actualNorthMap != nullptr) this->m_actualNorthMap->render(game);
  if (this->m_actualSouthMap != nullptr) this->m_actualSouthMap->render(game);
  if (this->m_actualEastMap != nullptr) this->m_actualEastMap->render(game);
  if (this->m_actualWestMap != nullptr) this->m_actualWestMap->render(game);
  if (this->m_actualMap != nullptr) this->m_actualMap->render(game);
}

World::~World() {
  for (auto tileset = this->m_tilesets.begin(); tileset != this->m_tilesets.end(); tileset++)
    delete tileset->second;
  this->m_tilesets.clear();

  for (auto map = this->m_maps.begin(); map != this->m_maps.end(); map++)
    delete map->second;
  this->m_maps.clear();
}
