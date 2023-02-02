#pragma once

template <typename data_t, size_t columns, size_t rows>
struct matrix_t {
public:
	data_t matrix[rows][columns]{ };

public:
	matrix_t() { }

	matrix_t(const data_t& value) { fill(value); }

	matrix_t(const std::array<std::array<data_t, columns>, rows>& arr) {
		for(const int& row : std::views::iota(size_t{ }, rows)) {
			std::move(arr[row].begin(), arr[row].end(), &matrix[row][0]);
		}
	}

	template <typename another_data_t>
	matrix_t(const another_data_t(&array)[rows][columns]) {
		std::copy(&array[0][0], &array[rows - 1][columns - 1] + 1, &matrix[0][0]);
	}

public:
	template <typename self_t> auto data(this self_t&& self) { return &self.matrix[0][0]; }

	template <typename self_t> auto&& fill(this self_t&& self, const data_t& value) {
		for(const int& column : std::views::iota(size_t{ }, columns)) self.set_column(column, value);
		return self;
	}

	template <typename self_t> auto&& fill_columns(this self_t&& self, const std::array<data_t, rows>& values) {
		for(const int& column : std::views::iota(size_t{ }, columns)) self.set_column(column, values);
		return self;
	}

	template <typename self_t> auto&& fill_rows(this self_t&& self, const std::array<data_t, columns>& values) {
		for(const int& row : std::views::iota(size_t{ }, rows)) self.set_row(row, values);
		return self;
	}

	template <typename self_t> auto&& set_column(this self_t&& self, const int& column, const data_t& value) {
		for(const int& row : std::views::iota(size_t{ }, rows)) self.matrix[row][column] = value;
		return self;
	}

	template <typename self_t> auto&& set_column(this self_t&& self, const int& column, const std::array<data_t, rows>& values) {
		for(const int& row : std::views::iota(size_t{ }, rows)) self.matrix[row][column] = values[row];
		return self;
	}

	template <typename self_t> auto&& set_row(this self_t&& self, const int& row, const data_t& value) {
		for(const int& column : std::views::iota(size_t{ }, columns)) self.matrix[row][column] = value;
		return self;
	}

	template <typename self_t> auto&& set_row(this self_t&& self, const int& row, const std::array<data_t, columns>& values) {
		for(const int& column : std::views::iota(size_t{ }, columns)) self.matrix[row][column] = values[column];
		return self;
	}

	std::array<data_t, rows> get_column(const int& column) const {
		std::array<data_t, rows> result{ };
		std::ranges::move(std::vector<data_t>{ &matrix[0][column], & matrix[rows - 1][column] + 1 } | std::views::stride(rows), result.begin());
		return result;
	}

	std::array<data_t, columns> get_row(const int& row) const {
		return std::to_array(matrix[row]);
	}

	template <typename another_data_t>
	matrix_t<another_data_t, columns, rows> cast() const { return matrix_t<another_data_t, columns, rows>{ matrix }; }

public:
	template <typename another_data_t>
	operator matrix_t<another_data_t, columns, rows>() const { return cast<another_data_t>(); }

#define matrix_create_arithmetic_operators(op)									\
	class_create_arithmetic_operators(mat, matrix_t, op, {						\
		matrix_t new_matrix{ self };											\
		for(const int& row : std::views::iota(size_t{ }, rows))				\
			for(const int& column : std::views::iota(size_t{ }, columns))	\
				new_matrix.matrix[row][column] op##= mat.matrix[row][column];	\
		return new_matrix;														\
	})																			\

	matrix_create_arithmetic_operators(-);
	matrix_create_arithmetic_operators(+);
	matrix_create_arithmetic_operators(*);
	matrix_create_arithmetic_operators(/);
	matrix_create_arithmetic_operators(%);

#undef matrix_create_arithmetic_operators

	template <typename another_data_t> bool operator ==(const matrix_t<another_data_t, columns, rows>& mat) const {
		for(const int& row : std::views::iota(size_t(), rows))
			for(const int& column : std::views::iota(size_t(), columns))
				if(matrix[row][column] != mat.matrix[row][column]) return false;
		return true;
	};
};

struct matrix4x4_t : public matrix_t<float, 4, 4> {
public: using matrix_t<float, 4, 4>::matrix_t;
	static matrix4x4_t identity() {
		static const matrix4x4_t matrix{ {
			{ 1.f, 0.f, 0.f, 0.f },
			{ 0.f, 1.f, 0.f, 0.f },
			{ 0.f, 0.f, 1.f, 0.f },
			{ 0.f, 0.f, 0.f, 1.f }
			} };
		return matrix;
	}

	static matrix4x4_t project_ortho(const float& l, const float& r, const float& b, const float& t, const float& n, const float& f) {
		return {{
			{ 2.f / (r - l),	0.f,			0.f,			-(r + l) / (r - l) },
			{ 0.f,				2.f / (t - b),	0.f,			-(t + b) / (t - b) },
			{ 0.f,				0.f,			2 / (f - n),	-(f + n) / (f - n) },
			{ 0.f,				0.f,			0.f,			1.f }
			}};
	}

	static matrix4x4_t project_perspective(const float& l, const float& r, const float& b, const float& t, const float& n, const float& f) {
		return {{
			{ 2.f * n / (r - l),	0.f,				(r + l) / (r - l),	0.f						},
			{ 0.f,					2.f * n / (t - b),	(t + b) / (t - b),	0.f						},
			{ 0.f,					0.f,				-(f + n) / (f - n), -(2 * f * n) / (f - n)	},
			{ 0.f,					0.f,				-1.f,				0.f						}
			}};
	}

public:
	matrix4x4_t() { }

	matrix4x4_t(const matrix_t<float, 4, 4>& mat) : matrix_t{ mat.matrix } { }

public:
	template <typename self_t> auto&& fill_columns(this self_t&& self, const vec4_t<float>& vec) {
		for(const int& column : std::views::iota(0, 4)) self.set_column(column, vec);
		return self;
	}

	template <typename self_t> auto&& fill_rows(this self_t&& self, const vec4_t<float>& vec) {
		for(const int& row : std::views::iota(0, 4)) self.set_row(row, vec);
		return self;
	}

	template <typename self_t> auto&& set_column(this self_t&& self, const int& column, const vec4_t<float>& vec) {
		self.matrix[0][column] = vec.x;
		self.matrix[1][column] = vec.y;
		self.matrix[2][column] = vec.z;
		self.matrix[3][column] = vec.w;
		return self;
	}

	template <typename self_t> auto&& set_row(this self_t&& self, const int& row, const vec4_t<float>& vec) {
		self.matrix[row][0] = vec.x;
		self.matrix[row][1] = vec.y;
		self.matrix[row][2] = vec.z;
		self.matrix[row][3] = vec.w;
		return self;
	}

	vec4_t<float> get_column(const int& column) const { return { matrix[0][column], matrix[1][column], matrix[2][column], matrix[3][column] }; }
	vec4_t<float> get_row(const int& row) const { return { matrix[row][0], matrix[row][1], matrix[row][2], matrix[row][3] }; }
};