#pragma once

#include <algorithm>
#include "gl/gl_1_5.h"
#include "noncopyable.hpp"

namespace yks {
	namespace gl {

		struct Texture {
			GLuint name;

			Texture()
				: name(0)
			{ }

			explicit Texture(GLuint name)
				: name(name)
			{ }

			Texture(Texture&& o)
				: name(o.name)
			{
				o.name = 0;
			}

			Texture& operator=(Texture&& o) {
				std::swap(name, o.name);
				return *this;
			}

			~Texture() {
				if (name != 0)
					glDeleteTextures(1, &name);
			}

		private:
			NONCOPYABLE(Texture);
		};

	}
}
