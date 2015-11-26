#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "AbstractVisibleMap.hpp"
class Game;

class Map {
  private:
    AbstractVisibleMap*         m_visibleMap;
    uint16_t                    m_conections[4]; // North, South, East, West

    uint16_t***                 m_map;
    uint16_t                    m_id;
    uint16_t                    m_tilesetID;
    uint16_t                    m_width;
    uint16_t                    m_height;
    int16_t                     m_scrollx;
    int16_t                     m_scrolly;
    uint8_t                     m_layers;
    uint16_t                    m_renderWidth;
    uint16_t                    m_renderHeight;

    bool                        m_render;

    void          Construct           ();

  public:
    Map                               ();
    Map                               (std::string filename);

    // Get Map data, metadata is proporcionated by World
    void            load              (std::string filename);
    void            setTileset        (Tileset* tileset);
    void            setScroll         (int16_t x, int16_t y);
    void            setConnections    (uint16_t north, uint16_t south, uint16_t east, uint16_t west);
    //void            setDimensions     (uint16_t width, uint16_t height);
    void            setID             (uint16_t id);
    void            setTilesetID      (uint16_t tid);

    void            update            (sf::Time deltaTime, int16_t startTileX, int16_t startTileY, uint16_t width, uint16_t hight);
    void            render            (Game* game);
    ~Map                              ();

    uint16_t        getNorthMap       ();
    uint16_t        getSouthMap       ();
    uint16_t        getEastMap        ();
    uint16_t        getWestMap        ();

    uint16_t        getID             ();
    uint16_t        getTilesetID      ();

    uint16_t        getWidth          ();
    uint16_t        getHight          ();
};

#endif // __MAP_HPP__
