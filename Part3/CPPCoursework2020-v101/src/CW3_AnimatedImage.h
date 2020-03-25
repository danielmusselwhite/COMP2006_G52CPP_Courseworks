#pragma once
#include "SimpleImage.h"
#include <vector>
#include "BaseEngine.h"

class CW3_AnimatedImage
{
protected:
	std::vector<std::pair<SimpleImage, int>> m_animFrames;
	int m_frameIndex;
	int m_limit;

public:
	// constructor
	CW3_AnimatedImage(std::vector<std::pair<SimpleImage, int>> animFrames) {
		m_animFrames = animFrames;
		m_frameIndex = 0; //start animation with first frame
		m_limit = m_animFrames.at(m_frameIndex).second; //starting time limit for first frame
	}

	// deconstructor
	~CW3_AnimatedImage() {
		m_animFrames.clear();
	}

	void renderCurrentFrame(BaseEngine* pEngine, DrawingSurface* pTarget,
		int iXDrawLocation, int iYDrawLocation, int iTargetWidth, int iTargetHeight,
		int iLeftInImage, int iTopInImage, int iWidthInImage, int iHeightInImage) {

		// get the frame image for this anim frame
		SimpleImage frame = m_animFrames.at(m_frameIndex).first;

		// render this frames image
		frame.setTransparencyColour(0x000000);
		frame.renderImageBlit(pEngine, pTarget, iXDrawLocation, iYDrawLocation, iTargetWidth, iTargetHeight, 0, 0, iWidthInImage, iHeightInImage);

		// if we have superceeded the limit
		if (pEngine->getRawTime() >= m_limit) {
			//move to the next anim frame
			m_frameIndex = (m_frameIndex + 1) % (m_animFrames.size());
			//set the limit for when we move to the next anim frame
			m_limit = m_animFrames.at(m_frameIndex).second + pEngine->getRawTime();
		}
	}

	SimpleImage getCurrentFrame() {
		return m_animFrames.at(m_frameIndex).first;
	}
};