#include "../include/rectAnimation.h"

RectAnimation::RectAnimation(Rectangle originalRect, Rectangle targetRect, Color originalColor, Color targetColor, float duration)
  : m_OriginalRect(originalRect), m_CurrentRect(originalRect), m_TargetRect(targetRect), m_OriginalColor(originalColor), m_CurrentColor(originalColor), m_TargetColor(targetColor), m_Duration(duration)
{
  m_IsFinished = false;
}

RectAnimation::RectAnimation(void)
{ }

void RectAnimation::Restart(void)
{
  m_CurrentColor = m_OriginalColor;
  m_CurrentRect = m_OriginalRect;
  m_IsFinished = false;
}

// This function is only created to the extent needed for the game and is not fully completed
// -----------------------------------------------------------------------------------------------
void RectAnimation::Animate(void)
{
  if (m_OriginalColor.a > m_TargetColor.a)
  {
    if (m_CurrentColor.a > m_TargetColor.a)
      m_CurrentColor.a -= (m_TargetColor.a-m_OriginalColor.a)/(GetFPS()*m_Duration);

    if (m_CurrentColor.a <= m_TargetColor.a)
    {
      m_CurrentColor.a = m_TargetColor.a;
      m_IsFinished = true;
    }
  }
  else
  {
    if (m_CurrentColor.a < m_TargetColor.a)
    {
      if ((int)m_CurrentColor.a + (m_TargetColor.a-m_OriginalColor.a)/(GetFPS()*m_Duration) >= 255)
        m_CurrentColor.a = 255;
      else
        m_CurrentColor.a += (m_TargetColor.a-m_OriginalColor.a)/(GetFPS()*m_Duration);
    }

    if (m_CurrentColor.a >= m_TargetColor.a)
    {
      m_CurrentColor.a = m_TargetColor.a;
      m_IsFinished = true;
    }
  }

  DrawRectangleRec(m_CurrentRect, m_CurrentColor);
}

void RectAnimation::Reverse(void)
{
  m_IsFinished = false;
  std::swap(m_OriginalColor, m_TargetColor);
  std::swap(m_OriginalRect, m_TargetRect);
}

bool RectAnimation::IsFinished(void)
{
  return m_IsFinished;
}
