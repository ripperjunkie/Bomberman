#include "Bomb.h"

void Bomb::Start()
{
	Entity::Start();

	bStartTimer = true;
	timer = 5.f;
	printf("Start\n");

}

void Bomb::Update()
{
	Entity::Update();

	

	if (bStartTimer)
	{
		timer -= GetFrameTime();
		printf("Timer: %f\n", timer);

		if (timer <= 0.f)
		{
			Destroy();
			bStartTimer = false;
		}
	}


}