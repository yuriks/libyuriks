#pragma once

#include "mat.hpp"
#include "vec.hpp"

namespace yks {

	inline mat4 translate(const vec3& v)
	{
		const mat4 m = {{
			{1, 0, 0, v[0]},
			{0, 1, 0, v[1]},
			{0, 0, 1, v[2]},
			{0, 0, 0,   1 }
		}};

		return m;
	}

	inline mat3 scale(float scale)
	{
		const mat3 m = {{
			{scale,   0,     0, },
			{  0,   scale,   0, },
			{  0,     0,   scale}
		}};

		return m;
	}

	inline mat3 scale(const vec3& scale)
	{
		const mat3 m = {{
			{scale[0],    0,        0,   },
			{   0,     scale[1],    0,   },
			{   0,        0,     scale[2]}
		}};

		return m;
	}

	mat3 rotate(const vec3& axis, float angle);
	mat3 orient(const vec3& up, const vec3& forward);

	// Projections
	mat4 orthographic_proj(float left, float right, float bottom, float top, float z_near, float z_far);
	mat4 frustrum_proj(float half_width, float half_height, float z_near, float z_far);
	mat4 perspective_proj(float vfov, float aspect, float z_near, float z_far);

	// Cameras
	mat4 look_at(const vec3& up, const vec3& camera, const vec3& target);

}
