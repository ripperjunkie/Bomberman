#pragma once

#include "Engine/GameFramework/Actor.h"

class Explosion : public Actor
{
public:

	Explosion() : Actor()
	{
		mName = "explosion";

		mAnimationSpeed = 7.f;

		explosionAnim.push_back(RecCropLocation(324.f, 708.f));
		explosionAnim.push_back(RecCropLocation(352.f, 708.f));
		explosionAnim.push_back(RecCropLocation(384.f, 708.f));
		explosionAnim.push_back(RecCropLocation(418.f, 708.f));

		CropSprite(explosionAnim[0].x, explosionAnim[0].y);


		mAnimations.push_back(AnimationData(explosionAnim));

	}

	virtual void Start() override;
	virtual void Update() override;
	virtual void Destroy() override;


private:
	float timer;
	float initialTimer; //using to reset timer back to default value
	bool bStartTimer;

	std::vector<RecCropLocation> explosionAnim;
};

