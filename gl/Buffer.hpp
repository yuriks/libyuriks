#pragma once

#include <algorithm>
#include "gl/gl_1_5.h"
#include "noncopyable.hpp"

namespace yks {
	namespace gl {

		struct Buffer {
			GLuint name;

			Buffer()
				: name(0)
			{ }

			explicit Buffer(GLuint name)
				: name(name)
			{ }

			Buffer(Buffer&& o)
				: name(o.name)
			{
				o.name = 0;
			}

			Buffer& operator=(Buffer&& o) {
				std::swap(name, o.name);
			}

			~Buffer() {
				if (name != 0)
					glDeleteBuffers(1, &name);
			}

		private:
			NONCOPYABLE(Buffer);
		};

	}
}