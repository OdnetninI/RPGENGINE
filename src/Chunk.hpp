
#ifndef __CHUNK_HPP__
#define __CHUNK_HPP__

#include <cstdint>

#define CHUNK_SIZE 32
#define INT_16_TO_64(x)         ((uint64_t)((uint16_t)(x)))
#define INT_8_TO_64(x)          ((uint64_t)((uint8_t)(x)))
#define CHUNK_TILE_DOWN(x)      (uint16_t)((uint64_t)x >> 48)
#define CHUNK_TILE_MIDLE(x)     (uint16_t)(CHUNK_TILE_DOWN((uint64_t)x << 16))
#define CHUNK_TILE_UP(x)        (uint16_t)(CHUNK_TILE_DOWN((uint64_t)x << 32))
#define CHUNK_TILE_COLLISION(x) (uint8_t)(CHUNK_TILE_DOWN((uint64_t)x << 40))
#define CHUNK_TILE_TILESET(x)   (uint8_t)(CHUNK_TILE_DOWN((uint64_t)x << 48))
#define CHUNK_TILE(x,y,z,a,b)   (uint64_t)(INT_16_TO_64(x) << 48 | INT_16_TO_64(y) << 32 | INT_16_TO_64(z) << 16 | INT_8_TO_64(a) << 8 | INT_8_TO_64(b))

class Chunk {
  public:
    int16_t m_x, m_y;
    uint64_t m_tiles[CHUNK_SIZE][CHUNK_SIZE];

  private:
    Chunk (int16_t x, int16_t y);
    bool setTile (uint16_t x, uint16_t y, uint16_t down, uint16_t middle, uint16_t up, uint8_t collision, uint8_t tileset);
    uint16_t getTile (uint16_t x, uint16_t y, uint8_t layer);
    uint8_t getCollision (uint16_t x, uint16_t y);
    uint8_t getTileset (uint16_t x, uint16_t y);
    uint16_t getChunkX ();
    uint16_t getChunkY ();
};

#endif  // __CHUNK_HPP__
