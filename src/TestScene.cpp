#include <iostream>
#include "TestScene.hpp"

int numscenes = 0;
int spriteIndex = 0;
int x = ((WIN_X/2)/64)*64, y = ((WIN_Y/2)/64)*64;
int dir = 0;
#define DIR_NONE  0
#define DIR_DOWN  1
#define DIR_UP    2
#define DIR_LEFT  3
#define DIR_RIGHT 4
int look = 1;

TestScene::TestScene(Game* game) {
    this->m_game = game;
    this->m_num = numscenes;
    numscenes++;

    std::cout << "Creada la escena numero: " << this->m_num << std::endl;

    this->m_test.load("Data/Test.png");
    this->m_test.setTextureDimensions(64,256);
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
  }
  int vel = 8;

  if (dir == DIR_DOWN) y += vel;
  if (dir == DIR_UP) y -= vel;
  if (dir == DIR_LEFT) x -= vel;
  if (dir == DIR_RIGHT) x += vel;

  if ( (x == ( (x >> 6) << 6 )) && (y == ( (y >> 6) << 6 )))
    dir = DIR_NONE;

  //std::cout << "X: " << x << " Y: " << y << std::endl << "Look: " << look << " Dir: " << dir << std::endl;
  //x+=16;
  if (dir == DIR_NONE && look == DIR_LEFT && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) dir=DIR_LEFT;
  if (dir == DIR_NONE && look == DIR_RIGHT && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) dir=DIR_RIGHT;
  if (dir == DIR_NONE && look == DIR_UP && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) dir=DIR_UP;
  if (dir == DIR_NONE && look == DIR_DOWN && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) dir=DIR_DOWN;
  if (dir == DIR_NONE && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) look=DIR_LEFT;
  if (dir == DIR_NONE && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) look=DIR_RIGHT;
  if (dir == DIR_NONE && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) look=DIR_UP;
  if (dir == DIR_NONE && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) look=DIR_DOWN;

  this->m_test.setIndex(look-1);

  this->m_world.lockSprite(this->m_test);
  this->m_world.setCamera(x,y);
  this->m_world.update(this->m_game->getFrameTime());
  this->m_test.update(this->m_game->getFrameTime());
  x = this->m_world.getCameraX();
  y = this->m_world.getCameraY();
}

void TestScene::Render() {
  this->m_world.render(this->m_game);
  this->m_test.render(this->m_game);
}

TestScene::~TestScene() {

  std::cout << "Destruida la escena numero: " << this->m_num << std::endl;

}
