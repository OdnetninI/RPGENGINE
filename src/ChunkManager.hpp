#ifndef __CHUNKMANAGER_HPP__
#define __CHUNKMANAGER_HPP__

#include "Chunk.hpp"

class ChunkManager {
  private:
    Chunk* m_loaded[9];

  public:
    ChunkManager();
    void loadChunk (const char* filename, uint8_t id);
    void loadChunkFromCoords (int16_t x, int16_t y, uint8_t id);
    void loadChunksFromCenteredChunk (int16_t x, int16_t y);
    Chunk* generateEmptyChunk(int16_t x, int16_t y);
    ~ChunkManager();
};

#endif // __CHUNKMANAGER_HPP__
