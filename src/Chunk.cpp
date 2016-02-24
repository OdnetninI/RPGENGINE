
#include "Chunk.hpp"

Chunk::Chunk (int16_t x, int16_t y) {
  this->m_x = x;
  this->m_y = y;
}

bool Chunk::setTile (uint16_t x, uint16_t y, uint16_t down, uint16_t middle, uint16_t up, uint8_t collision, uint8_t tileset) {
  if (x >= CHUNK_SIZE || y >= CHUNK_SIZE) return false;
  this->m_tiles[x][y] = CHUNK_TILE(down, middle, up, collision, tileset);
  return true;
}

uint16_t Chunk::getTile (uint16_t x, uint16_t y, uint8_t layer) {
  if (x >= CHUNK_SIZE || y >= CHUNK_SIZE) return 0;
  return (layer == 0) ? CHUNK_TILE_DOWN(this->m_tiles[x][y]) : (layer == 1) ? CHUNK_TILE_MIDLE(this->m_tiles[x][y]) : (layer == 2) ? CHUNK_TILE_UP(this->m_tiles[x][y]) : 0;
}

uint8_t Chunk::getCollision (uint16_t x, uint16_t y) {
  if (x >= CHUNK_SIZE || y >= CHUNK_SIZE) return 0;
  return CHUNK_TILE_COLLISION(this->m_tiles[x][y]);
}

uint8_t Chunk::getTileset (uint16_t x, uint16_t y) {
  if (x >= CHUNK_SIZE || y >= CHUNK_SIZE) return 0;
  return CHUNK_TILE_TILESET(this->m_tiles[x][y]);
}

uint16_t Chunk::getChunkX () {
  return this->m_x;
}

uint16_t Chunk::getChunkY () {
  return this->m_y;
}
