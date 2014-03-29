#pragma once
#include <cassert>
#include "gl_1_5.h"

inline void check_gl_error() {
	GLenum error = glGetError();
	assert(error == GL_NO_ERROR);
}

#define YKS_CHECK_GL check_gl_error()
#ifdef _DEBUG
#define YKS_CHECK_GL_PARANOID check_gl_error()
#else
#define YKS_CHECK_GL_PARANOID
#endif
