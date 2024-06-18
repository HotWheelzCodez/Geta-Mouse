#include "../include/game.h"

Game::Game(const char* title)
{
  InitWindow(m_WinWidth, m_WinHeight, title);
  ToggleFullscreen();
  SetTargetFPS(60);
  InitAudioDevice();

  // Calculate scale
  // --------------------------------------------------------------------------
  int monitor = GetCurrentMonitor();
  int monitorWidth = GetMonitorWidth(monitor);
  int monitorHeight = GetMonitorHeight(monitor);

  float scaleX = monitorWidth/m_WinWidth;
  float scaleY = monitorHeight/m_WinHeight;
  m_Scale = (scaleX > scaleY) ? scaleX : scaleY;
  m_PixelWidth = m_WinWidth/64.0f;

  // Load font(s)
  // --------------------------------------------------------------
  m_Font = LoadFontEx("assets/fonts/opensans.ttf", 100, 0, 0); 

  // Load textures
  // -----------------------------------------------------------------------------
  m_MainMenuImage = LoadTexture("assets/textures/mainMenu.png");
  m_MainMenuImage.width = 1920;
  m_MainMenuImage.height = 1080*m_Scale;

  m_PlayBackgroundImage = LoadTexture("assets/textures/backgroundImage.png");
  m_PlayBackgroundImage.width = 1920;
  m_PlayBackgroundImage.height = 1080*m_Scale;

  m_HandOpenImage = LoadTexture("assets/textures/handNoBlood.png");
  m_HandOpenImage.width = 5*m_PixelWidth;
  m_HandOpenImage.height = 10*m_PixelWidth;

  m_HandClosedImage = LoadTexture("assets/textures/closedHand.png");
  m_HandClosedImage.width = 5*m_PixelWidth;
  m_HandClosedImage.height = 10*m_PixelWidth;

  m_MouseImage = LoadTexture("assets/textures/mouse.png");
  m_MouseImage.width = 5*m_PixelWidth;
  m_MouseImage.height = 5*m_PixelWidth;

  m_BunnyImage = LoadTexture("assets/textures/bunny.png");
  m_BunnyImage.width *= 20;
  m_BunnyImage.height *= 20;

  m_BunnyCockingImage = LoadTexture("assets/textures/bunnyCocking.png");
  m_BunnyCockingImage.width *= 20;
  m_BunnyCockingImage.height *= 20;

  m_BunnyPointingImage = LoadTexture("assets/textures/bunnyPointing.png");
  m_BunnyPointingImage.width *= 20;
  m_BunnyPointingImage.height *= 20;

  m_DogImage = LoadTexture("assets/textures/dog.png");
  m_DogImage.width = 5*m_PixelWidth;
  m_DogImage.height = 5*m_PixelWidth;

  m_CurlyWifeImage = LoadTexture("assets/textures/curlyWife.png");
  m_CurlyWifeImage.width *= 20;
  m_CurlyWifeImage.height *= 20;

  // Load sounds
  // --------------------------------------------------------------
  m_SqueakSound = LoadSound("assets/sounds/squeak.wav");
  SetSoundVolume(m_SqueakSound, 20.0f);

  m_SquishSound = LoadSound("assets/sounds/killSound.wav");
  SetSoundVolume(m_SquishSound, 20.0f);

  m_GunCockingSound = LoadSound("assets/sounds/gunCocking.wav");
  SetSoundVolume(m_GunCockingSound, 20.0f);

  m_GunShootingSound = LoadSound("assets/sounds/gunShooting.mp3");
  SetSoundVolume(m_GunShootingSound, 20.0f);

  m_GeorgeSound = LoadSound("assets/sounds/georgeVoice.wav");
  SetSoundVolume(m_GeorgeSound, 20.0f);

  m_LugerShootingSound = LoadSound("assets/sounds/lugerShooting.wav");
  SetSoundVolume(m_LugerShootingSound, 20.0f);

  // Load music
  // ---------------------------------------------------------------------
  m_BattleMusic = LoadMusicStream("assets/sounds/battleMusic.wav");
  SetMusicVolume(m_BattleMusic, 3.0f);
  PlayMusicStream(m_BattleMusic);

  m_BossBattleMusic = LoadMusicStream("assets/sounds/bossBattleMusic.wav");
  SetMusicVolume(m_BossBattleMusic, 5.0f);
  PlayMusicStream(m_BossBattleMusic);

  m_MainMenuMusic = LoadMusicStream("assets/sounds/mainMenuMusic.wav");
  SetMusicVolume(m_MainMenuMusic, 20.0f);
  PlayMusicStream(m_MainMenuMusic);

  // Initalize game state
  // ------------------------------------------
  m_GameState.mainMenu = true;
  m_GameState.mouseHover = false;
  m_GameState.battle = false;
  m_GameState.bossFight = false;
  m_GameState.bunnyEnding = false;
  m_GameState.georgeEnding = false;
  m_GameState.dustStormEnding = false;
  m_GameState.startTime = 0.0f;

  // Initalize play state
  // ----------------------------------------------------------------
  m_PlayState.playSqueak = false;
  m_PlayState.renderMouse = false;
  m_PlayState.cocked = false;
  m_PlayState.playGunShot = true;
  m_PlayState.positive = GetRandomValue(0, 1000) % 2 == 0;
  m_PlayState.yOffset = m_MouseImage.width;
  m_PlayState.handImage = m_HandOpenImage;
  m_PlayState.waitSeconds = 0.0f;
  m_PlayState.waitDuration = 1.0f;
  m_PlayState.waitCount = 0;
  m_PlayState.timeLeft = 60;
  m_PlayState.waitTime = 60;
  m_PlayState.keyToPress = 'a' + GetRandomValue(0, 25);
  m_PlayState.keyPressedCount = 0;
  m_PlayState.mouseCollected = 0;
  m_PlayState.effectWaitCount = 0;
  m_PlayState.effectWaitSeconds = 0;
  m_PlayState.randomRant = 0;
  m_PlayState.timeOffset = 0.0f;
  m_PlayState.positiveEffects.push_back({
    true,
    25,
    TextAnimation(m_Font, "Emergency Releif Act +25", 60, 50, (m_WinHeight/2)-25, 50, (m_WinHeight/2)-25, { 0, 255, 0, 255 }, { 0, 255, 0, 0 }, 5.0f), 
    LoadSound("assets/sounds/rantPositive1.wav")
  });
  SetSoundVolume(m_PlayState.positiveEffects[0].explanation, 50.0f);
  m_PlayState.positiveEffects.push_back({
    true,
    10,
    TextAnimation(m_Font, "End Of Prohibition +10", 60, 50, (m_WinHeight/2)-25, 50, (m_WinHeight/2)-25, { 0, 255, 0, 255 }, { 0, 255, 0, 0 }, 5.0f), 
    LoadSound("assets/sounds/rantPositive2.wav")
  });
  SetSoundVolume(m_PlayState.positiveEffects[1].explanation, 50.0f);
  m_PlayState.positiveEffects.push_back({
    true,
    15,
    TextAnimation(m_Font, "FIDC Created +15", 60, 50, (m_WinHeight/2)-25, 50, (m_WinHeight/2)-25, { 0, 255, 0, 255 }, { 0, 255, 0, 0 }, 5.0f), 
    LoadSound("assets/sounds/rantPositive3.wav")
  });
  SetSoundVolume(m_PlayState.positiveEffects[2].explanation, 50.0f);
  m_PlayState.positiveEffects.push_back({
    true,
    5,
    TextAnimation(m_Font, "FM Radio Is Invented +5", 60, 50, (m_WinHeight/2)-25, 50, (m_WinHeight/2)-25, { 0, 255, 0, 255 }, { 0, 255, 0, 0 }, 5.0f), 
    LoadSound("assets/sounds/rantPositive4.wav")
  });
  SetSoundVolume(m_PlayState.positiveEffects[3].explanation, 50.0f);
  m_PlayState.positiveEffects.push_back({
    true,
    20,
    TextAnimation(m_Font, "Social Security Is Invented +20", 60, 50, (m_WinHeight/2)-25, 50, (m_WinHeight/2)-25, { 0, 255, 0, 255 }, { 0, 255, 0, 0 }, 5.0f), 
    LoadSound("assets/sounds/rantPositive5.wav")
  });
  SetSoundVolume(m_PlayState.positiveEffects[4].explanation, 50.0f);
  m_PlayState.negativeEffects.push_back({
    false,
    25,
    TextAnimation(m_Font, "Great Depression -25", 60, 50, (m_WinHeight/2)-25, 50, (m_WinHeight/2)-25, { 255, 0, 0, 255 }, { 255, 0, 0, 0 }, 5.0f), 
    LoadSound("assets/sounds/rantNegative1.wav")
  });
  SetSoundVolume(m_PlayState.negativeEffects[0].explanation, 50.0f);
  m_PlayState.negativeEffects.push_back({
    false,
    10,
    TextAnimation(m_Font, "Hindenburg Disaster -10", 60, 50, (m_WinHeight/2)-25, 50, (m_WinHeight/2)-25, { 255, 0, 0, 255 }, { 255, 0, 0, 0 }, 5.0f), 
    LoadSound("assets/sounds/rantNegative2.wav")
  });
  SetSoundVolume(m_PlayState.negativeEffects[1].explanation, 50.0f);
  m_PlayState.negativeEffects.push_back({
    false,
    20,
    TextAnimation(m_Font, "Rize of Nazi Germany -20", 60, 50, (m_WinHeight/2)-25, 50, (m_WinHeight/2)-25, { 255, 0, 0, 255 }, { 255, 0, 0, 0 }, 5.0f), 
    LoadSound("assets/sounds/rantNegative3.wav")
  });
  SetSoundVolume(m_PlayState.negativeEffects[2].explanation, 50.0f);
  m_PlayState.negativeEffects.push_back({
    false,
    5,
    TextAnimation(m_Font, "Federal Bureau of Narcotics Is Founded -5", 60, 50, (m_WinHeight/2)-25, 50, (m_WinHeight/2)-25, { 255, 0, 0, 255 }, { 255, 0, 0, 0 }, 5.0f), 
    LoadSound("assets/sounds/rantNegative4.wav")
  });
  SetSoundVolume(m_PlayState.negativeEffects[3].explanation, 50.0f);
  m_PlayState.negativeEffects.push_back({
    false,
    15,
    TextAnimation(m_Font, "The FBI Is Formed From The BOI -15", 60, 50, (m_WinHeight/2)-25, 50, (m_WinHeight/2)-25, { 255, 0, 0, 255 }, { 255, 0, 0, 0 }, 5.0f), 
    LoadSound("assets/sounds/rantNegative5.wav")
  });
  SetSoundVolume(m_PlayState.negativeEffects[4].explanation, 50.0f);

  // Generate hole positions and state
  // ------------------------------------------------------------
  m_Holes[0]  = { 16*m_PixelWidth, 24*m_PixelWidth, false };
  m_Holes[1]  = { 25*m_PixelWidth, 24*m_PixelWidth, false };
  m_Holes[2]  = { 34*m_PixelWidth, 24*m_PixelWidth, false };
  m_Holes[3]  = { 43*m_PixelWidth, 24*m_PixelWidth, false };
  m_Holes[4]  = { 16*m_PixelWidth, 30*m_PixelWidth, false };
  m_Holes[5]  = { 25*m_PixelWidth, 30*m_PixelWidth, false };
  m_Holes[6]  = { 34*m_PixelWidth, 30*m_PixelWidth, false };
  m_Holes[7]  = { 43*m_PixelWidth, 30*m_PixelWidth, false };
  m_Holes[8]  = { 16*m_PixelWidth, 35*m_PixelWidth, false };
  m_Holes[9]  = { 25*m_PixelWidth, 35*m_PixelWidth, false };
  m_Holes[10] = { 34*m_PixelWidth, 35*m_PixelWidth, false };
  m_Holes[11] = { 43*m_PixelWidth, 35*m_PixelWidth, false };

  // Initalize animation(s)
  m_BlackFade = RectAnimation({ 0, 0, 1920, 1080*m_Scale }, { 0, 0, 1920, 1080*m_Scale }, { 0, 0, 0, 0 }, { 0, 0, 0, 255 }, 2.0f);
}

Game::~Game(void)
{
  CloseGame();
}

void Game::BeginRender(void)
{
  BeginDrawing();
  ClearBackground(RAYWHITE);
  m_GameState.mouseHover = false;
}

void Game::RenderMainMenu(void)
{
  m_PlayState.mouseCollected = 0;
  m_PlayState.maxMouseCollectd = 0;
  m_PlayState.playGunShot = true;
  m_PlayState.waitDuration = 1.0f;
  UpdateMusicStream(m_MainMenuMusic);
  DrawTexture(m_MainMenuImage, 0, 0, WHITE);
  ShowCursor();
 
  GUI::ButtonStyle bs_Menu = { BROWN, WHITE, { 218, 160, 109, 225 }, WHITE, m_Font, 100, GUI::TEXT_ALIGNMENT_CENTER, 0.0f };
  if (GUI::ButtonText({ (m_WinWidth/2)-250, (m_WinHeight/2)-50, 500, 75 }, bs_Menu, "PLAY", GetMousePosition(), m_GameState.mouseHover))
  {
    m_GameState.startTime = GetTime();
    m_GameState.mainMenu = false;
    m_GameState.battle = true;
  }

  bs_Menu.fontSize >>= 1;
  if (GUI::ButtonText({ m_WinWidth-200, 0, 200, 50 }, bs_Menu, "EXIT", GetMousePosition(), m_GameState.mouseHover))
    CloseGame();
}

void Game::RenderBunnyEnding(void)
{
  DrawTexture(m_PlayBackgroundImage, 0, 0, WHITE);
  Texture2D imageToDraw = m_BunnyImage;

  if (m_GameState.startTime+3 < GetTime() && !m_PlayState.cocked)
  {
    PlaySound(m_GunCockingSound);
    m_PlayState.cocked = true;
  }

  if (m_GameState.startTime+5 < GetTime())
    imageToDraw = m_BunnyPointingImage;
  else if (m_GameState.startTime+4 < GetTime())
    imageToDraw = m_BunnyImage;
  else if (m_GameState.startTime+3.75 < GetTime())
    imageToDraw = m_BunnyCockingImage;

  m_BlackFade.Animate();

  if (m_BlackFade.IsFinished())
    DrawTexture(imageToDraw, (m_WinWidth/2)-(imageToDraw.width/2.0f), (m_WinHeight/2)-(imageToDraw.height/2.0f), WHITE);

  if (m_GameState.startTime+6 < GetTime())
  {
    DrawRectangle(0, 0, 1920, 1080*m_Scale, BLACK);
    if (!IsSoundPlaying(m_GunShootingSound))
      PlaySound(m_GunShootingSound);
  }

  if (m_GameState.startTime+7 < GetTime())
  {
    m_GameState.mainMenu = true;
    m_GameState.bunnyEnding = false;
    m_PlayState.mouseCollected = 0;
    m_PlayState.waitTime = 60;
    m_BlackFade.Restart();
  }
}

void Game::RenderGeorgeEnding(void)
{
  DrawTexture(m_PlayBackgroundImage, 0, 0, WHITE);
  m_BlackFade.Animate();

  if (!IsSoundPlaying(m_GeorgeSound))
    PlaySound(m_GeorgeSound);

  if (GetTime()-m_GameState.startTime >= 3 && m_PlayState.playGunShot)
  {
    PlaySound(m_LugerShootingSound);
    m_PlayState.playGunShot = false;
  }
   
  if (GetTime()-m_GameState.startTime >= 6)
  {
    m_GameState.georgeEnding = false;
    m_GameState.mainMenu = true;
  }
}

void Game::RenderDustStormEnding(void)
{
  ShowCursor();
  DrawTexture(m_PlayBackgroundImage, 0, 0, WHITE);
  GUI::ButtonStyle bs_Menu = { BROWN, WHITE, { 218, 160, 109, 225 }, WHITE, m_Font, 100, GUI::TEXT_ALIGNMENT_CENTER, 0.0f };

  if (m_PlayState.maxMouseCollectd >= 70)
  {
    const char* message = "Congratulations! You collected enough";
    const char* message2 = "mice to escape the dust storm!";
    DrawTextEx(m_Font, message, { (m_WinWidth/2)-(MeasureTextEx(m_Font, message, 80, 5).x/2), 100 }, 80, 5, GREEN);
    DrawTextEx(m_Font, message2, { (m_WinWidth/2)-(MeasureTextEx(m_Font, message, 80, 5).x/2), 200 }, 80, 5, GREEN);

    if (GUI::ButtonText({ (m_WinWidth/2)-500, (m_WinHeight/2)-50, 1000, 100 }, bs_Menu, "Main Menu", GetMousePosition(), m_GameState.mouseHover))
    {
      m_GameState.dustStormEnding = false;
      m_GameState.mainMenu = true;
    }
    return;
  }

  Color colors[5] = {
    { 246,215,176,255 },
    { 242,210,169,255 },
    { 236,204,162,255 },
    { 231,196,150,255 },
    { 225,191,146,255 }
  };

  int randomX = GetRandomValue(0, 1920);
  int randomY = GetRandomValue(0, 1080);

  m_PlayState.sand.push_back({ colors[GetRandomValue(0, 4)], { (float)randomX, (float)randomY*m_Scale } });

  for (Sand sand : m_PlayState.sand)
    DrawRectangle(sand.position.x, sand.position.y, 10, 10, sand.color);

  const char* message = "You did not collect enough mice to escape the dust storm!";
  DrawTextEx(m_Font, message, { (m_WinWidth/2)-(MeasureTextEx(m_Font, message, 80, 5).x/2), 100 }, 80, 5, RED);

  if (GUI::ButtonText({ (m_WinWidth/2)-500, (m_WinHeight/2)-50, 1000, 100 }, bs_Menu, "Main Menu", GetMousePosition(), m_GameState.mouseHover))
  {
    m_GameState.dustStormEnding = false;
    m_GameState.mainMenu = true;
  }
}

void Game::RenderBattle(void)
{
  UpdateMusicStream(m_BattleMusic);

  DrawTexture(m_PlayBackgroundImage, 0, 0, WHITE);
  HideCursor();

  if (!m_PlayState.renderMouse)
  {
    m_PlayState.renderMouse = true;
    m_Holes[GetRandomValue(0, 11)].selected = true;
    m_PlayState.yOffset = m_MouseImage.height;
  }

  m_PlayState.handPosition = { GetMousePosition().x-50, GetMousePosition().y };

  for (size_t i = 0; i < 12; i++)
  {
    if (!m_Holes[i].selected)
      continue;

    if (m_PlayState.yOffset <= -50)
    {
      m_PlayState.playSqueak = true;
      m_PlayState.handImage = m_HandOpenImage;
      m_PlayState.yOffset = -50;
      m_PlayState.waitCount++;
      m_PlayState.waitSeconds = (float)m_PlayState.waitCount/GetFPS();

      if (m_PlayState.playSqueak)
      {
        PlaySound(m_SqueakSound);
        m_PlayState.playSqueak = false;
      }

      if (m_PlayState.waitSeconds >= m_PlayState.waitDuration)
      {
        m_PlayState.renderMouse = false;
        m_PlayState.yOffset = m_MouseImage.width;
        m_Holes[i].selected = false;
        m_PlayState.waitCount = 0;
        m_PlayState.waitSeconds = 0;
      }

      if (CheckCollisionPointRec(GetMousePosition(), { m_Holes[i].x-m_PixelWidth, (m_Holes[i].y-m_MouseImage.height)+(m_PixelWidth*2)+m_PlayState.yOffset, (float)m_MouseImage.width, (float)m_MouseImage.height }))
      {
        m_GameState.mouseHover = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
          m_PlayState.renderMouse = false;
          m_PlayState.yOffset = m_MouseImage.width;
          m_PlayState.mouseCollected++;
          m_Holes[i].selected = false;
          m_PlayState.waitCount = 0;
          m_PlayState.waitSeconds = 0;
          m_PlayState.handImage = m_HandClosedImage;
          PlaySound(m_SquishSound);
        }
      }
    }
    else
    {
      m_PlayState.yOffset -= (m_MouseImage.width)/((float)GetFPS()*0.25f);
    }

    BeginScissorMode(m_Holes[i].x-m_PixelWidth, m_Holes[i].y-m_MouseImage.height-150, m_MouseImage.width, 200);
    DrawTexture(m_MouseImage, m_Holes[i].x-m_PixelWidth, (m_Holes[i].y-m_MouseImage.height)+(m_PixelWidth*2)+m_PlayState.yOffset, WHITE);
    EndScissorMode();
  }

  m_PlayState.timeLeft = m_PlayState.waitTime-((int)GetTime()-m_GameState.startTime)+m_PlayState.offsetTime;
  if (m_PlayState.timeLeft <= 0)
  {
    for (size_t i = 0; i < 12; i++)
      m_Holes[i].selected = false;

    for (size_t i = 0; i < m_PlayState.positiveEffects.size(); i++)
      StopSound(m_PlayState.positiveEffects[i].explanation);
    for (size_t i = 0; i < m_PlayState.negativeEffects.size(); i++)
      StopSound(m_PlayState.negativeEffects[i].explanation);

    m_PlayState.yOffset = m_MouseImage.width;
    m_PlayState.renderMouse = false;
    m_PlayState.waitDuration = 1.0f;
    m_PlayState.waitCount = 0;
    m_PlayState.waitSeconds = 0;
    m_PlayState.timeLeft = 60;
    m_PlayState.effectWaitCount = 0;
    m_PlayState.effectWaitSeconds = 0;
    m_PlayState.maxMouseCollectd = m_PlayState.mouseCollected;
    m_PlayState.offsetTime = 0;
    m_PlayState.effectWaitSeconds = 0;
    m_PlayState.effectWaitCount = 0;
    m_GameState.startTime = GetTime();

    if (m_PlayState.mouseCollected >= 50)
    {
      m_GameState.bossFight = true;
      m_GameState.battle = false;
    }
    else
    {
      m_PlayState.waitTime = 60;
      m_GameState.startTime = GetTime();
      m_GameState.battle = false;
      m_GameState.bunnyEnding = true;
      m_BlackFade.Restart();
    }
  }

  Color textColor = GREEN;
  if (m_PlayState.timeLeft <= 10)
  {
    textColor = RED;
    m_PlayState.waitDuration = 0.1f;
  }
  else if (m_PlayState.timeLeft <= 30)
  {
    textColor = YELLOW;
    m_PlayState.waitDuration = 0.25f;
  }
  else if (m_PlayState.timeLeft <= 45)
  {
    m_PlayState.waitDuration = 0.5f;
  }
  else if (m_PlayState.timeLeft <= 50)
  {
    m_PlayState.waitDuration = 0.75f;
  }

  if (m_PlayState.timeLeft <= 3)
    SetMusicVolume(m_BattleMusic, m_PlayState.timeLeft);

  std::string displayTime = "Time Left: " + std::to_string(m_PlayState.timeLeft);
  DrawTextEx(m_Font, displayTime.c_str(), { 5, 0 }, 50, 5, textColor);

  std::string displayCollected = "Collected: " + std::to_string(m_PlayState.mouseCollected) + "/50";
  DrawTextEx(m_Font, displayCollected.c_str(), { 5, 60 }, 50, 5, GOLD);

  DrawTextureV(m_PlayState.handImage, m_PlayState.handPosition, WHITE);

  {
    const char* displayTitle = "Collect 50 Mice To Get To The Boss";
    DrawTextEx(m_Font, displayTitle, { (m_WinWidth/2)-MeasureTextEx(m_Font, displayTitle, 50, 5).x/2, 50 }, 50, 5, WHITE);
  }

  m_PlayState.effectWaitCount++;
  m_PlayState.effectWaitSeconds = (float)m_PlayState.effectWaitCount/GetFPS();
  if (m_PlayState.effectWaitSeconds >= 10)
  {
    m_PlayState.effectWaitSeconds = 0.0f;
    m_PlayState.effectWaitCount = 0;
    m_PlayState.randomRant = GetRandomValue(0, m_PlayState.positiveEffects.size()-1);
    m_PlayState.renderEffect = true;
    m_PlayState.addTime = true;
    m_PlayState.positive = !m_PlayState.positive;
  }

  if (m_PlayState.renderEffect)
  {
    if (m_PlayState.positive)
    {
      if (m_PlayState.addTime)
      {
        m_PlayState.offsetTime += m_PlayState.positiveEffects[m_PlayState.randomRant].amount;
        PlaySound(m_PlayState.positiveEffects[m_PlayState.randomRant].explanation);
        m_PlayState.addTime = false;
      }
      m_PlayState.positiveEffects[m_PlayState.randomRant].name.Animate();
      if (m_PlayState.positiveEffects[m_PlayState.randomRant].name.IsFinished())
      {
        m_PlayState.renderEffect = false;
        m_PlayState.positiveEffects[m_PlayState.randomRant].name.Restart();
      }
    }
    else
    {
      if (m_PlayState.addTime)
      {
        m_PlayState.offsetTime -= m_PlayState.negativeEffects[m_PlayState.randomRant].amount;
        PlaySound(m_PlayState.negativeEffects[m_PlayState.randomRant].explanation);
        m_PlayState.addTime = false;
      }
      m_PlayState.negativeEffects[m_PlayState.randomRant].name.Animate();
      if (m_PlayState.negativeEffects[m_PlayState.randomRant].name.IsFinished())
      {
        m_PlayState.renderEffect = false;
        m_PlayState.negativeEffects[m_PlayState.randomRant].name.Restart();
      }
    }
  }
}

void Game::RenderBossBattle(void)
{
  UpdateMusicStream(m_BossBattleMusic);

  DrawTexture(m_PlayBackgroundImage, 0, 0, WHITE);
  const char* bossDisplay = "BOSS FIGHT";
  DrawTextEx(m_Font, bossDisplay, { (1920/2.0f)-MeasureTextEx(m_Font, bossDisplay, 100, 5).x/2, 30 }, 100, 5, RED);
  DrawTexture(m_CurlyWifeImage, (m_WinWidth/2)-(m_CurlyWifeImage.width/2.0f)+m_PlayState.curlyWifePos.x, (m_WinHeight/2)-(m_CurlyWifeImage.height/2.0f)+m_PlayState.curlyWifePos.y, WHITE);
  DrawRectangleLines((1920/2)-25, (1080/2)-25, 50, 50, WHITE);

  std::string displayChar;
  displayChar += m_PlayState.keyToPress;
  DrawTextEx(m_Font, displayChar.c_str(), { (1920/2.0f)-7, (1080/2.0f)-12.5 }, 30, 5, WHITE);
  m_PlayState.curlyWifePos = { 0 };

  char keyPressed = GetKeyPressed();

  if (keyPressed)
  {
    if (keyPressed+32 == m_PlayState.keyToPress)
    {
      m_PlayState.keyPressedCount++;
      m_PlayState.keyPressedText.push_back(TextAnimation(m_Font, "+1 Correct Key", 40, (m_WinWidth/2.0f)+50, (m_WinHeight/2), (m_WinWidth/2.0f)+50, (m_WinHeight/2)-100, { 0, 255, 0, 255 }, { 0, 255, 0, 0 }, 1.0f));
      bool left = (GetRandomValue(0, 1)) ? true : false;
      bool down = (GetRandomValue(0, 1)) ? true : false;

      if (left)
        m_PlayState.curlyWifePos.x -= GetRandomValue(1, 50);
      else
        m_PlayState.curlyWifePos.x += GetRandomValue(1, 50);
      if (down)
        m_PlayState.curlyWifePos.y -= GetRandomValue(1, 50);
      else
        m_PlayState.curlyWifePos.y += GetRandomValue(1, 50);

      m_PlayState.keyToPress = 'a' + GetRandomValue(0, 25);
    }
    else
    {
      if (m_PlayState.keyPressedCount)
      {
        m_PlayState.keyPressedCount--;
        m_PlayState.keyPressedText.push_back(TextAnimation(m_Font, "-1 Incorrect Key", 40, (m_WinWidth/2.0f)+50, (m_WinHeight/2.0f), (m_WinWidth/2.0f)+50, (m_WinHeight/2)-100, { 255, 0, 0, 255 }, { 255, 0, 0, 0 }, 1.0f));
      }
    }
  }

  for (size_t i = 0; i < m_PlayState.keyPressedText.size(); i++)
    if (!m_PlayState.keyPressedText[i].IsFinished())
      m_PlayState.keyPressedText[i].Animate();
    else
      m_PlayState.keyPressedText.pop_back();

  m_PlayState.timeLeft = m_PlayState.waitTime-((int)GetTime()-m_GameState.startTime);
  if (m_PlayState.timeLeft <= 0)
  {
    m_GameState.startTime = GetTime();
    m_GameState.bossFight = false;
    m_BlackFade.Restart();
    if (m_PlayState.keyPressedCount >= 75)
      m_GameState.dustStormEnding = true;
    else
      m_GameState.georgeEnding = true;
  }

  std::string displayTime = "Time Left: " + std::to_string(m_PlayState.timeLeft);
  Color textColor = GREEN;
  if (m_PlayState.timeLeft <= 10)
  {
    textColor = RED;
    m_PlayState.waitDuration = 0.1f;
  }
  else if (m_PlayState.timeLeft <= 30)
  {
    textColor = YELLOW;
    m_PlayState.waitDuration = 0.25f;
  }
  else if (m_PlayState.timeLeft <= 45)
  {
    m_PlayState.waitDuration = 0.5f;
  }
  else if (m_PlayState.timeLeft <= 50)
  {
    m_PlayState.waitDuration = 0.75f;
  }
  DrawTextEx(m_Font, displayTime.c_str(), { 5, 0 }, 50, 5, textColor);

  std::string scoreDisplay = "Score: " + std::to_string(m_PlayState.keyPressedCount) + "/75";
  DrawTextEx(m_Font, scoreDisplay.c_str(), { 5, 60 }, 50, 5, GOLD);
}

void Game::RenderGame(void)
{
  if (m_GameState.mainMenu)
    RenderMainMenu();
  else if (m_GameState.battle)
    RenderBattle();
  else if (m_GameState.bossFight)
    RenderBossBattle();
  else if (m_GameState.bunnyEnding)
    RenderBunnyEnding();
  else if (m_GameState.georgeEnding)
    RenderGeorgeEnding();
  else if (m_GameState.dustStormEnding)
    RenderDustStormEnding();
}

void Game::EndRender(void)
{
  if (m_GameState.mouseHover)
    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
  else
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

  EndDrawing();
}

void Game::CloseGame(void)
{
  UnloadTexture(m_MainMenuImage);
  UnloadTexture(m_PlayBackgroundImage);
  UnloadTexture(m_HandClosedImage);
  UnloadTexture(m_HandOpenImage);
  UnloadTexture(m_MouseImage);
  UnloadSound(m_SqueakSound);
  UnloadSound(m_SquishSound);
  UnloadSound(m_GeorgeSound);
  UnloadSound(m_GunCockingSound);
  UnloadSound(m_LugerShootingSound);
  UnloadMusicStream(m_MainMenuMusic);
  UnloadMusicStream(m_BattleMusic);
  UnloadMusicStream(m_BossBattleMusic);
  CloseAudioDevice();
  CloseWindow();
}

void Game::Play(void)
{
  while (!WindowShouldClose())
  {
    BeginRender();
    RenderGame();
    EndRender();
  }

  CloseGame();
}
