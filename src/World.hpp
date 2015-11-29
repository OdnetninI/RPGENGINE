
#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include "defines.hpp"
#include "Map.hpp"
#include "Tileset.hpp"
#include <unordered_map>

class World {
    private:
      //Map**                   m_maps;
      std::unordered_map<uint16_t, Map*>      m_maps;
      std::unordered_map<uint16_t, Tileset*>  m_tilesets;

      Map*                                    m_actualMap;
      Map*                                    m_actualNorthMap;
      Map*                                    m_actualSouthMap;
      Map*                                    m_actualEastMap;
      Map*                                    m_actualWestMap;
      // Diagonal Maps
      Map*                                    m_actualNorthWestMap;
      Map*                                    m_actualSouthWestMap;
      Map*                                    m_actualNorthEastMap;
      Map*                                    m_actualSouthEastMap;

      int16_t x,y;

      void        Construct     ();

    public:
      World();
      World(std::string filename);

      void        load              (std::string filename);
      void        lockSprite        (AbstractSprite& sprite);
      Map*        getMapByID        (uint16_t id);

      void        setActualMap      (uint16_t map);
      Map*        getMap            ();
      void        mapUpdate         (Map* map, sf::Time deltaTime, int16_t scrollx, int16_t scrolly, uint16_t startx, uint16_t starty, uint16_t width, uint16_t height);

      void        update            (sf::Time deltaTime);
      void        setCamera         (int16_t x, int16_t y);
      int16_t     getCameraX        ();
      int16_t     getCameraY        ();
      void        render            (Game* game);

      ~World();
};

#endif // __WORLD_HPP__
