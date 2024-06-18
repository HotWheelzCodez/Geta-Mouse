#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <algorithm>

#include "raylib/raylib.h"
#include "gui.h"
#include "textAnimation.h"
#include "rectAnimation.h"

class Game
{
public:
  Game(const char* title);
  ~Game(void);

  void Play(void);

private:
  typedef struct
  {
    float x, y;
    bool selected;
  } Hole;

  typedef struct
  {
    bool          positive; 
    uint16_t      amount;
    TextAnimation name;
    Sound         explanation;
  } Effect;

  typedef struct
  {
    Color color;
    Vector2 position;
  } Sand;

  typedef struct
  {
    bool mouseHover;
    bool mainMenu;
    bool battle;
    bool bossFight;
    bool bunnyEnding;
    bool georgeEnding;
    bool dustStormEnding;
    float startTime;
  } GameState;

  typedef struct
  {
    bool      playSqueak;
    bool      renderMouse;
    bool      cocked;
    bool      renderEffect;
    bool      addTime;
    bool      positive;
    bool      playGunShot;
    char      keyToPress;
    float     yOffset;
    float     waitSeconds;
    float     waitDuration;
    float     effectWaitSeconds;
    float     waitTime;
    float     offsetTime;
    uint8_t   randomRant;
    uint32_t  waitCount;
    uint32_t  effectWaitCount;
    uint32_t  waitForNewEffect;
    uint16_t  timeLeft;
    uint16_t  timeOffset;
    uint16_t  keyPressedCount;
    uint16_t  mouseCollected;
    uint16_t  maxMouseCollectd;
    Vector2   handPosition;
    Vector2   curlyWifePos;
    Texture2D handImage;
    std::vector<TextAnimation> keyPressedText;
    std::vector<Effect> positiveEffects;
    std::vector<Effect> negativeEffects;
    std::vector<Sand> sand;
    TextAnimation toAnimate;
  } PlayState;

  Hole m_Holes[12];

  RectAnimation m_BlackFade;

  float m_Scale; 
  float m_PixelWidth;

  Font m_Font;

  Texture2D m_MainMenuImage;
  Texture2D m_PlayBackgroundImage;
  Texture2D m_HandOpenImage;
  Texture2D m_HandClosedImage;
  Texture2D m_MouseImage;
  Texture2D m_BunnyImage;
  Texture2D m_BunnyCockingImage;
  Texture2D m_BunnyPointingImage;
  Texture2D m_DogImage;
  Texture2D m_CurlyWifeImage;

  Sound m_SqueakSound;
  Sound m_SquishSound;
  Sound m_GunCockingSound;
  Sound m_GunShootingSound;
  Sound m_GeorgeSound;
  Sound m_LugerShootingSound;

  Music m_BattleMusic;
  Music m_BossBattleMusic;
  Music m_MainMenuMusic;

  GameState m_GameState;
  PlayState m_PlayState;

  static constexpr float m_WinWidth = 1920.0f;
  static constexpr float m_WinHeight = 1080.0f;

private:
  void BeginRender(void);
  void RenderGame(void);
  void EndRender(void);
  void RenderBunnyEnding(void);
  void RenderGeorgeEnding(void);
  void RenderDustStormEnding(void);
  void RenderMainMenu(void);
  void RenderBattle(void);
  void RenderBossBattle(void);
  void CloseGame(void);
};
