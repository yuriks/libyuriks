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
				parentFromLocal * yks::translate(v),
				yks::translate(-v) * localFromParent
			};
		}

		TransformPair scale(float s) const {
			return TransformPair{
				parentFromLocal * pad<4>(yks::scale(s)),
				pad<4>(yks::scale(1.0f / s)) * localFromParent
			};
		}

		TransformPair rotate(const mat3& m) const {
			return TransformPair{
				parentFromLocal * pad<4>(m),
				pad<4>(transpose(m)) * localFromParent
			};
		}
	};

}