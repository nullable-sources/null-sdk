#pragma once
#include <data-types/vec4.h>

template <typename data_t, template<typename> class rows_t, template<typename> class columns_t>
struct matrix_t {
public:
	static constexpr size_t rows_size{ rows_t<data_t>::array_size }, columns_size{ columns_t<data_t>::array_size }, linear_size{ rows_size * columns_size };

public:
	union {
		rows_t<columns_t<data_t>> data;
		std::array<data_t, linear_size> linear_array;
		std::array<std::array<data_t, columns_size>, rows_size> array{ };
	};

public:
	matrix_t() { }

	matrix_t(const data_t& value) : data{ value } { }

	matrix_t(const rows_t<columns_t<data_t>>& matrix) : data{ matrix } { }
	matrix_t(const std::array<data_t, columns_size * rows_size>& matrix) : linear_array{ matrix } { }
	matrix_t(const std::array<std::array<data_t, columns_size>, rows_size>& matrix) : array{ matrix } { }
	matrix_t(const std::vector<std::vector<data_t>>& matrix) { for(const auto& row : std::views::iota(matrix.begin(), std::next(matrix.begin(), rows_size))) set_row(row - matrix.begin(), *row); }
	matrix_t(const std::vector<data_t>& matrix) { std::move(matrix.begin(), std::next(matrix.begin(), linear_size), linear_array.begin()); }

public:
	template <typename self_t> auto&& fill(this self_t&& self, const data_t& value) { self.data = value; return self; }
	template <typename self_t> auto&& fill_rows(this self_t&& self, const rows_t<data_t>& row) {
		for(const int& i : std::views::iota(size_t{ }, rows_size)) self.set_row(i, row);
		return self;
	}

	template <typename self_t> auto&& fill_columns(this self_t&& self, const columns_t<data_t>& column) {
		for(const int& i : std::views::iota(size_t{ }, columns_size)) self.set_column(i, column);
		return self;
	}

	template <typename self_t> auto&& set_row(this self_t&& self, const int& row_n, const rows_t<data_t>& row) { self.data[row_n] = row; return self; }
	rows_t<data_t> get_row(const int& row_n) const { return data[row_n]; }

	template <typename self_t> auto&& set_column(this self_t&& self, const int& column_n, const columns_t<data_t>& column) { for(int i{ }; data_t& coordinate : self.linear_array | std::views::drop(column_n) | std::views::stride(rows_size)) coordinate = column[i++]; return self; }
	columns_t<data_t> get_column(const int& column_n) const { return linear_array | std::views::drop(column_n) | std::views::stride(rows_size) | std::ranges::to<std::vector>(); }

public:
	template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.data; return self; }
	template <typename self_t> auto operator ++(this self_t&& self, int) { return matrix_t{ self.data++ }; }
	template <typename self_t> auto&& operator --(this self_t&& self) { --self.data; return self; }
	template <typename self_t> auto operator --(this self_t&& self, int) { return matrix_t{ self.data-- }; }

	template <typename self_t> auto operator -(this self_t&& self) { return matrix_t{ -self.data }; }
	class_create_arithmetic_operators(matrix, matrix_t, -, { return self.data - matrix.data; });
	class_create_arithmetic_operators(matrix, matrix_t, +, { return self.data + matrix.data; });
	class_create_arithmetic_operators(matrix, matrix_t, *, {
		matrix_t result{ };
		for(const int& row : std::views::iota(size_t{ }, rows_size)) {
			for(const int& column : std::views::iota(size_t{ }, columns_size)) {
				result.array[row][column] = self.get_column(column).dot(matrix.get_row(row));
			}
		}
		return result;
		});
	class_create_arithmetic_operators(matrix, matrix_t, /, { return self.data / matrix.data; });
	class_create_arithmetic_operators(matrix, matrix_t, %, { return self.data % matrix.data; });

	template <typename another_data_t> bool operator ==(const matrix_t<another_data_t, rows_t, columns_t>& matrix) const { return data == matrix.data; };
	template <typename another_t> bool operator ==(const another_t& value) const { return data == value; };
	class_create_logic_operators(matrix, matrix_t, <, { return self.data < matrix.data; }, { return self.data <= matrix.data; });
	class_create_logic_operators(matrix, matrix_t, >, { return self.data > matrix.data; }, { return self.data >= matrix.data; });
};

struct matrix4x4_t : public matrix_t<float, vec4_t, vec4_t> {
public: using matrix_t<float, vec4_t, vec4_t>::matrix_t;
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
		return matrix4x4_t{ {
			{ 2.f / (r - l),		0.f,				0.f,				0.f	},
			{ 0.f,					2.f / (t - b),		0.f,				0.f },
			{ 0.f,					0.f,				2 / (f - n),		0.f },
			{ -(r + l) / (r - l),	-(t + b) / (t - b),	-(f + n) / (f - n),	1.f }
			} };
	}

	static matrix4x4_t project_perspective(const float& l, const float& r, const float& b, const float& t, const float& n, const float& f) {
		return matrix4x4_t{ {
			{ 2.f * n / (r - l),	0.f,				0.f,					0.f	},
			{ 0.f,					2.f * n / (t - b),	0.f,					0.f	},
			{ (r + l) / (r - l),	(t + b) / (t - b),	-(f + n) / (f - n),		-1.f },
			{ 0.f,					0.f,				-(2 * f * n) / (f - n),	0.f	}
			} };
	}

public:
	matrix4x4_t() { }

	matrix4x4_t(const matrix_t<float, vec4_t, vec4_t>& matrix) : matrix_t{ matrix.data } { }
};