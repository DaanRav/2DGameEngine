#include "Sprite.h"
#include "Texture.h"
#include "Timer.h"

Comp::Sprite::Sprite(int frames, int pxlWidth, int pxlHeight, const glm::vec2& startFramePos, float frameTime)
	:Component{}
	, m_Frames{frames}
	, m_FramePxlWidth{pxlWidth}
	, m_FramePxlHeight{pxlHeight}
	, m_StartFramePos{startFramePos}
	, m_FrameTime{ frameTime }
{
}

void Comp::Sprite::Initialize()
{
	if (!IsAttachedToGameObject())
		return;

	GetNeededComponents();

	//setting the texture size by default to the size of one frame
	m_pTextureComp->SetDestRect(glm::vec4{ 0,0,m_FramePxlWidth,m_FramePxlHeight });
}

void Comp::Sprite::Update()
{
	int oldFrameNr{ m_CurrentFrame };
	//updating the frame counter
	m_ElapsedFrameTime += float(dae::Timer::GetInstance().GetDeltaTime());
	if (m_ElapsedFrameTime >= m_FrameTime)
	{
		m_ElapsedFrameTime = 0;
		m_CurrentFrame++;

		m_CurrentFrame %= m_Frames;
	}

	//only update if the frame nr has changed
	if (oldFrameNr != m_CurrentFrame)
	{
		//setting the correct srource rectangele for the texture
		glm::vec4 srcRect{};
		srcRect.x = m_StartFramePos.x + m_FramePxlWidth * m_CurrentFrame;
		srcRect.y = m_StartFramePos.y;
		srcRect.z = float(m_FramePxlWidth);
		srcRect.w = float(m_FramePxlHeight);

		m_pTextureComp->SetSrcRect(srcRect);
	}
}

void Comp::Sprite::SetSize(const glm::vec4& size)
{
	m_pTextureComp->SetDestRect(size);
}

void Comp::Sprite::GetNeededComponents()
{
	//for now will only find the firs texture attached to the same game object
	if (m_pGameObject.lock())
		m_pTextureComp = m_pGameObject.lock()->GetComponent<Comp::TextureComp>();
}

bool Comp::Sprite::HasAllComponents() const
{
	if (!m_pTextureComp)
		return false;
	return true;
}
