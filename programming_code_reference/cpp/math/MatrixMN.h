
#ifndef DDD_MATRIXMN_H_
#define DDD_MATRIXMN_H_

#include <vector>
#include "Matrix.h"
#include "Vector2.h"
#include "Vector3.h"

namespace ddd {
	class MatrixMN
	{
	public:
		// ---------- float** matrix;
		std::vector<std::vector<float>> matrix;
		size_t numOfRow;
		size_t numOfCol;

		// ---------- ctor
		MatrixMN()														noexcept;
		MatrixMN(size_t row_, size_t col_)								noexcept;
		MatrixMN(const Vector2& vector_, bool row_)						noexcept;
		MatrixMN(const Vector3& vector_, bool row_)						noexcept;
		MatrixMN(const std::vector<float>& arrayOfFloat_, bool row_)	noexcept;
		MatrixMN(const std::vector<std::vector<float>>& arrayOfFloat_)	noexcept;

		// ---------- setters
		void SetIdentity();
		void SetZero	();
		void Transpose	();
	
		// ---------- getters
		bool				IsSquare	() const;
		std::vector<float>	GetCol		(size_t index_) const;
		std::vector<float>	GetRow		(size_t index_) const;
		MatrixMN			Transposed	() const;

		// ---------- friend
		friend MatrixMN 		operator*	(const MatrixMN& matrix_, const MatrixMN& rhs);
		friend std::ostream& 	operator<<	(std::ostream& os, const MatrixMN& m);
		
	}; // MatrixMN

	MatrixMN	GaussJordanInverse	(const MatrixMN& mat);
} // namespace ddd

#endif // DDD_MATRIXMN_H_
