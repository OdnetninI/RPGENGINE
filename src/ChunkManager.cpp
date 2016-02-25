#include "ChunkManager.hpp"
#include "FileUtils.hpp"

ChunkManager::ChunkManager () {
  for (uint8_t i = 0; i < 9; i++)
    m_loaded[i] = nullptr;
}

ChunkManager::~ChunkManager () {
  for (uint8_t i = 0; i < 9; i++)
    delete m_loaded[i];
}

void ChunkManager::loadChunk (const char* filename, uint8_t id) {
  if (id >= 9) return;
  std::ifstream file;
  if (!FileUtils::openBinary(file, filename)) ;

  int16_t cx = FileUtils::readBytesAsINT16(file);
  int16_t cy = FileUtils::readBytesAsINT16(file);

  Chunk* chunk = new Chunk(cx, cy);

  for (uint8_t x = 0; x < CHUNK_SIZE; x++)
    for (uint8_t y = 0; y < CHUNK_SIZE; y++) {
      uint16_t downTile = FileUtils::readBytesAsUINT16(file);
      uint16_t midTile = FileUtils::readBytesAsUINT16(file);
      uint16_t upTile = FileUtils::readBytesAsUINT16(file);
      uint8_t collision = FileUtils::readByteAsUINT8(file);
      uint8_t tileset = FileUtils::readByteAsUINT8(file);
      if(chunk->setTile(x, y, downTile, midTile, upTile, collision, tileset));
    }

  file.close();

  this->m_loaded[id] = chunk;
}

void ChunkManager::loadChunkFromCoords (int16_t x, int16_t y, uint8_t id) {

}

void ChunkManager::loadChunksFromCenteredChunk (int16_t x, int16_t y) {

}

Chunk* ChunkManager::generateEmptyChunk (int16_t x, int16_t y) {
  Chunk* chunk = new Chunk(x, y);
  for (uint8_t x = 0; x < CHUNK_SIZE; x++)
    for (uint8_t y = 0; y < CHUNK_SIZE; y++)
      chunk->setTile(x,y,0,0,0,0,0);

  return chunk;
}
