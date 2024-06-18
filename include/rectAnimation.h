#pragma once

#include <iostream>
#include <algorithm>

#include "raylib/raylib.h"

class RectAnimation
{
public:
  RectAnimation(Rectangle originalRect, Rectangle targetRect, Color originalColor, Color targetColor, float duration);
  RectAnimation(void);

  void Animate(void);
  void Reverse(void);
  void Restart(void);
  bool IsFinished(void);

private:
  Rectangle m_OriginalRect;
  Rectangle m_CurrentRect;
  Rectangle m_TargetRect;
  Color m_OriginalColor, m_CurrentColor, m_TargetColor;
  float m_Duration;
  bool m_IsFinished;
};
