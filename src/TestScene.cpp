#include <iostream>
#include "TestScene.hpp"

int numscenes = 0;
int spriteIndex = 0;
int x = ((WIN_X/2)/64)*64, y = ((WIN_Y/2)/64)*64;

TestScene::TestScene(Game* game) {
    this->m_game = game;
    this->m_num = numscenes;
    numscenes++;

    std::cout << "Creada la escena numero: " << this->m_num << std::endl;
    this->m_sprite.load("Data/Pokemon.png");
    this->m_sprite.setTextureDimensions(2240, 1440);
    this->m_sprite.setDimensions(80,80);

    this->m_test.load("Data/Test.png");
    this->m_test.setTextureDimensions(64,64);
    this->m_test.setDimensions(64,64);
    this->m_test.setIndex(0);
    //this->m_tileset.load("Data/Tileset.til");
    this->m_world.load("Data/World.wd");
    this->m_world.setActualMap(1);
    //this->m_mapa->setTileset(&this->m_tileset);

    /*this->m_palletTown.load("Data/palletTown.map");
    this->m_palletTown.setTileset(&this->m_tileset);
    this->m_palletTown2.load("Data/palletTown.map");
    this->m_palletTown2.setTileset(&this->m_tileset);
*/
    /*this->m_map.loadTileset(this->m_tileset);
    this->m_mapBack.loadTileset(this->m_tileset);

    // Pallet town example
    {
      for (int i = 0; i < WIDTH_TILES; i++)
      {
        this->m_mapBack.setTile(i,0,2);
        this->m_mapBack.setTile(i,1,2);
      }

      for (int i = 2; i < HEIGHT_TILES; i++) {
        this->m_mapBack.setTile(0,i,2);
        this->m_mapBack.setTile(1,i,2);
        this->m_mapBack.setTile(18,i,2);
        this->m_mapBack.setTile(19,i,2);
      }

      for (int j = 2; j < HEIGHT_TILES-1; j+=2) {
      for (int i = 2; i < WIDTH_TILES-3; i+=2) {
        this->m_mapBack.setTile(i,j,5);
        this->m_mapBack.setTile(i+1,j,1);
        this->m_mapBack.setTile(i+1,j+1,5);
        this->m_mapBack.setTile(i,j+1,1);
      }
      }

      for (int i = 0; i < WIDTH_TILES; i++) {
        this->m_map.setTile(i,1,23);
      }

      this->m_map.setTile(10,1,3);
      this->m_map.setTile(11,1,3);
      this->m_map.setTile(10,0,3);
      this->m_map.setTile(11,0,3);

      this->m_map.setTile(3,0,23);
      this->m_map.setTile(9,0,23);
      this->m_map.setTile(12,0,23);
      this->m_map.setTile(18,0,23);

      for (int i = 2; i < WIDTH_TILES; i++) {
        this->m_map.setTile(0,i,23);
        this->m_map.setTile(19,i,23);
      }

      this->m_mapBack.setTile(2,4,4);
      this->m_mapBack.setTile(3,4,4);
      this->m_mapBack.setTile(2,5,4);
      this->m_mapBack.setTile(3,5,4);

      this->m_mapBack.setTile(10,4,4);
      this->m_mapBack.setTile(11,4,4);
      this->m_mapBack.setTile(10,5,4);
      this->m_mapBack.setTile(11,5,4);

      this->m_map.setTile(3,5,24);
      this->m_map.setTile(11,5,24);

      this->m_map.setTile(4,9,22);
      this->m_map.setTile(5,9,22);
      this->m_map.setTile(6,9,22);
      this->m_map.setTile(7,9,24);

      this->m_mapBack.setTile(4,8,4);
      this->m_mapBack.setTile(5,8,4);
      this->m_mapBack.setTile(6,8,4);
      this->m_mapBack.setTile(7,8,4);
      this->m_mapBack.setTile(4,9,4);
      this->m_mapBack.setTile(5,9,4);
      this->m_mapBack.setTile(6,9,4);
      this->m_mapBack.setTile(7,9,4);
      this->m_mapBack.setTile(4,10,2);
      this->m_mapBack.setTile(5,10,2);
      this->m_mapBack.setTile(6,10,2);
      this->m_mapBack.setTile(7,10,2);
      this->m_mapBack.setTile(4,11,2);
      this->m_mapBack.setTile(5,11,2);
      this->m_mapBack.setTile(6,11,2);
      this->m_mapBack.setTile(7,11,2);

      this->m_map.setTile(4,3,32);
      this->m_map.setTile(5,3,33);
      this->m_map.setTile(6,3,33);
      this->m_map.setTile(7,3,35);

      this->m_map.setTile(12,3,32);
      this->m_map.setTile(13,3,33);
      this->m_map.setTile(14,3,33);
      this->m_map.setTile(15,3,35);

      this->m_map.setTile(4,4,48);
      this->m_map.setTile(5,4,49);
      this->m_map.setTile(6,4,50);
      this->m_map.setTile(7,4,51);

      this->m_map.setTile(12,4,48);
      this->m_map.setTile(13,4,49);
      this->m_map.setTile(14,4,50);
      this->m_map.setTile(15,4,51);

      this->m_map.setTile(4,5,64);
      this->m_map.setTile(5,5,65);
      this->m_map.setTile(6,5,66);
      this->m_map.setTile(7,5,67);

      this->m_map.setTile(12,5,64);
      this->m_map.setTile(13,5,65);
      this->m_map.setTile(14,5,66);
      this->m_map.setTile(15,5,67);

      this->m_map.setTile(10,8,36);
      this->m_map.setTile(11,8,37);
      this->m_map.setTile(12,8,37);
      this->m_map.setTile(13,8,37);
      this->m_map.setTile(14,8,37);
      this->m_map.setTile(15,8,38);

      this->m_map.setTile(10,9,52);
      this->m_map.setTile(11,9,53);
      this->m_map.setTile(12,9,53);
      this->m_map.setTile(13,9,53);
      this->m_map.setTile(14,9,53);
      this->m_map.setTile(15,9,54);

      this->m_map.setTile(10,10,68);
      this->m_map.setTile(11,10,81);
      this->m_map.setTile(12,10,82);
      this->m_map.setTile(13,10,83);
      this->m_map.setTile(14,10,69);
      this->m_map.setTile(15,10,70);

      this->m_map.setTile(10,11,84);
      this->m_map.setTile(11,11,66);
      this->m_map.setTile(12,11,65);
      this->m_map.setTile(13,11,66);
      this->m_map.setTile(14,11,66);
      this->m_map.setTile(15,11,86);

    }
*/
    /*std::cout << "ID: " << this->m_tileset.getID()
              << " tileWide: " << this->m_tileset.getTileWide()
              << " tilehight: " << this->m_tileset.getTileHight()
              << " wide: " << this->m_tileset.getWide()
              << " hight: " << this->m_tileset.getHight() << std::endl;
*/
}

void TestScene::Update() {
  sf::Event event;
  while (this->m_game->getWindow().pollEvent(event))
  {
    if (event.type == sf::Event::Closed) {
      this->m_game->getWindow().close();
      //this->m_game->getSceneMng().markToRemove(this);
      //this->m_game->getSceneMng().markToAdd(new TestScene(this->m_game));
    }
    /*if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Right) {
        spriteIndex++;
        x+=4;
        //std::cout << "Index: " << spriteIndex << std::endl;
      }
      if (event.key.code == sf::Keyboard::Left) {
        spriteIndex--;
        x-=4;
        //std::cout << "Index: " << spriteIndex << std::endl;
      }
      if (event.key.code == sf::Keyboard::Down) {
        spriteIndex++;
        y+=4;
        //std::cout << "Index: " << spriteIndex << std::endl;
      }
      if (event.key.code == sf::Keyboard::Up) {
        spriteIndex--;
        y-=4;
        //std::cout << "Index: " << spriteIndex << std::endl;
      }
    }*/
  }
  int vel = 4;
  x+=16;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x-=vel;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x+=vel;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) y-=vel;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) y+=vel;

  //this->m_sprite.setIndex(spriteIndex);
  //this->m_world.getMap()->setScroll(x,y);
  //this->m_world.getMap()->update(this->m_game->getFrameTime(), 0, 0, 14, 9);
  this->m_world.lockSprite(this->m_test);
  this->m_world.setCamera(x,y);
  this->m_world.update(this->m_game->getFrameTime());
  x = this->m_world.getCameraX();
  y = this->m_world.getCameraY();
  this->m_test.update(this->m_game->getFrameTime());

  this->m_sprite.setPosition(x,y);
  this->m_sprite.setIndex(spriteIndex);
  this->m_sprite.update(this->m_game->getFrameTime());
  /*x %= 64;
  y %= 64;*/
  /*this->m_mapa->setScroll(x,y);
  this->m_mapa->update(this->m_game->getFrameTime(), 4, 14, 14, 4);
  */
  /*this->m_map.setOffset(x, y);
  this->m_mapBack.setOffset(x,y);*/
  /*this->m_palletTown.setScroll(x,y);
  this->m_palletTown.update(this->m_game->getFrameTime(), 4, 14, 14, 4);

  this->m_palletTown2.setScroll(x,y+4*64);
  this->m_palletTown2.update(this->m_game->getFrameTime(), 4, 0, 14, 5);
  */
}

void TestScene::Render() {
  //this->m_mapBack.render(this->m_game, WIDTH_TILES, HEIGHT_TILES);
  //this->m_map.render(this->m_game, WIDTH_TILES, HEIGHT_TILES);
  /*this->m_palletTown.render(this->m_game);
  this->m_palletTown2.render(this->m_game);*/
  //this->m_mapa->render(this->m_game);
  this->m_world.render(this->m_game);
  //this->m_world.render(this->m_game);
  //this->m_sprite.render(this->m_game);
  this->m_test.render(this->m_game);
}

TestScene::~TestScene() {

  std::cout << "Destruida la escena numero: " << this->m_num << std::endl;

}
