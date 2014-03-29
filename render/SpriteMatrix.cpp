#include "./SpriteMatrix.hpp"

namespace yks {

	SpriteMatrix::SpriteMatrix() {
		identity();
	}

	SpriteMatrix& SpriteMatrix::identity() {
		m(0, 0) = 1.0f;
		m(0, 1) = 0.0f;
		m(0, 2) = 0.0f;
		m(1, 0) = 0.0f;
		m(1, 1) = 1.0f;
		m(1, 2) = 0.0f;

		return *this;
	}

	SpriteMatrix& SpriteMatrix::multiply(const SpriteMatrix& l) {
		// a b c   A B C   a*A+b*D a*B+b*E a*C+b*F+c
		// d e f * D E F = d*A+e*D d*B+e*E d*C+e*F+f
		// 0 0 1   0 0 1      0       0        1

		auto a = m(0, 0), b = m(0, 1), c = m(0, 2);
		auto d = m(1, 0), e = m(1, 1), f = m(1, 2);
		auto A = l.m(0, 0), B = l.m(0, 1), C = l.m(0, 2);
		auto D = l.m(1, 0), E = l.m(1, 1), F = l.m(1, 2);

		m(0, 0) = a*A + b*D;
		m(0, 1) = a*B + b*E;
		m(0, 2) = a*C + b*F + c;
		m(1, 0) = d*A + e*D;
		m(1, 1) = d*B + e*E;
		m(1, 2) = d*C + e*F + f;

		return *this;
	}

	SpriteMatrix& SpriteMatrix::rotate(Complex z) {
		// r -i 0   a b c   a*r-d*i b*r-e*i c*r-f*i
		// i  r 0 = d e f = a*i+d*r b*i+e*r c*i+f*r
		// 0  0 1   0 0 1      0       0       1

		auto a = m(0, 0), b = m(0, 1), c = m(0, 2);
		auto d = m(1, 0), e = m(1, 1), f = m(1, 2);

		m(0, 0) = a*z.r - d*z.i;
		m(0, 1) = b*z.r - e*z.i;
		m(0, 2) = c*z.r - f*z.i;
		m(1, 0) = a*z.i + d*z.r;
		m(1, 1) = b*z.i + e*z.r;
		m(1, 2) = c*z.i + f*z.r;

		return *this;
	}

	SpriteMatrix& SpriteMatrix::scale(vec2 s) {
		// x 0 0   a b c   x*a x*b x*c
		// 0 y 0 * d e f = y*d y*e y*f
		// 0 0 1   0 0 1    0   0   1

		m(0, 0) *= s[0];
		m(0, 1) *= s[0];
		m(0, 2) *= s[0];
		m(1, 0) *= s[1];
		m(1, 1) *= s[1];
		m(1, 2) *= s[1];

		return *this;
	}


	SpriteMatrix& SpriteMatrix::shear(vec2 s) {
		// 1 x 0   a b c   a+x*d b+x*e c+x*f
		// y 1 0 * d e f = d+y*a e+y*b f+y*c
		// 0 0 1   0 0 1     0     0     1

		auto a = m(0, 0), b = m(0, 1), c = m(0, 2);
		auto d = m(1, 0), e = m(1, 1), f = m(1, 2);

		m(0, 0) += s[0] * d;
		m(0, 1) += s[0] * e;
		m(0, 2) += s[0] * f;
		m(1, 0) += s[1] * a;
		m(1, 1) += s[1] * b;
		m(1, 2) += s[1] * c;

		return *this;
	}

	SpriteMatrix& SpriteMatrix::translate(vec2 v) {
		// 1 0 x   a b c   a b c+x
		// 0 1 y * d e f = d e f+y
		// 0 0 1   0 0 1   0 0  1

		m(0, 2) += v[0];
		m(1, 2) += v[1];

		return *this;
	}

	vec2 SpriteMatrix::transform(vec2 p) const {
		// a b c   x   a*x+b*y+c
		// d e f * y = d*x+e*y+f
		// 0 0 1   1       1

		return mvec2(
			m(0, 0)*p[0] + m(0, 1)*p[1] + m(0, 2),
			m(1, 0)*p[0] + m(1, 1)*p[1] + m(1, 2));
	}

}
