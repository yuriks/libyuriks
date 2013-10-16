#pragma once
#include <cassert>
#include "gl_1_5.h"

#define YKS_CHECK_GL assert(glGetError() == GL_NO_ERROR)
#ifdef _DEBUG
#define YKS_CHECK_GL_PARANOID assert(glGetError() == GL_NO_ERROR)
#else
#define YKS_CHECK_GL_PARANOID
#endif
