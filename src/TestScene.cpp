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

    this->m_world.load("Data/World.wd");
    this->m_world.setActualMap(1);
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
  //x+=16;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x-=vel;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x+=vel;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) y-=vel;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) y+=vel;

  this->m_world.lockSprite(this->m_test);
  this->m_world.setCamera(x,y);
  this->m_world.update(this->m_game->getFrameTime());
  x = this->m_world.getCameraX();
  y = this->m_world.getCameraY();
  this->m_test.update(this->m_game->getFrameTime());

  this->m_sprite.setPosition(x,y);
  this->m_sprite.setIndex(spriteIndex);
  this->m_sprite.update(this->m_game->getFrameTime());
}

void TestScene::Render() {
  this->m_world.render(this->m_game);
  //this->m_sprite.render(this->m_game);
  this->m_test.render(this->m_game);
}

TestScene::~TestScene() {

  std::cout << "Destruida la escena numero: " << this->m_num << std::endl;

}
