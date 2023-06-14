#pragma once
#include "engineMath.h"

namespace Lights
{
	static constexpr int MAX_POINT_LIGHTS = 128;

	struct PointLightData
	{
		Vector3 lightColor;
		uint8_t padding1[4]{};
		Vector3 position;
		float innerRadius{};
		float outerRadius{};
		bool isEnabled{};
		uint8_t padding3[11]{};
	};

	struct LightingConstants
	{
		Vector3 c_ambient;
		uint8_t padding1[4]{};
		PointLightData c_pointLight[MAX_POINT_LIGHTS];
	};
}
