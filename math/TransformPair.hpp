#pragma once
#include "./mat.hpp"
#include "./MatrixTransform.hpp"

namespace yks {

	struct TransformPair {
		mat4 parentFromLocal;
		mat4 localFromParent;

		TransformPair()
			: parentFromLocal(mat4_identity), localFromParent(mat4_identity)
		{}

		TransformPair(const mat4& parentFromLocal, const mat4& localFromParent)
			: parentFromLocal(parentFromLocal), localFromParent(localFromParent)
		{}

		TransformPair translate(const vec3& v) const {
			return TransformPair{
				yks::translate(v) * parentFromLocal,
				localFromParent * yks::translate(-v)
			};
		}

		TransformPair scale(float s) const {
			return TransformPair{
				pad<4>(yks::scale(s)) * parentFromLocal,
				localFromParent * pad<4>(yks::scale(1.0f / s))
			};
		}

		TransformPair rotate(const mat3& m) const {
			return TransformPair{
				pad<4>(m) * parentFromLocal,
				localFromParent * pad<4>(transpose(m))
			};
		}
	};

}