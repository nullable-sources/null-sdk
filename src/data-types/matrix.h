#pragma once
#include <data-types/vec4.h>

template <typename data_t, template <typename> class rows_t, template <typename> class columns_t>
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

	template <typename another_data_t, template <typename> class another_rows_t, template <typename> class another_columns_t>
	matrix_t(const matrix_t<another_data_t, another_rows_t, another_columns_t>& matrix) {
		for(const int& i : std::views::iota(0u, std::min(another_rows_t<another_data_t>::array_size, rows_size)))
			set_row(i, matrix.get_row(i));
	}

	matrix_t(const rows_t<columns_t<data_t>>& matrix) : data{ matrix } { }
	matrix_t(const std::array<data_t, columns_size * rows_size>& matrix) : linear_array{ matrix } { }
	matrix_t(const std::array<std::array<data_t, columns_size>, rows_size>& matrix) : array{ matrix } { }
	matrix_t(const std::vector<std::vector<data_t>>& matrix) { for(const auto& row : std::views::iota(matrix.begin(), std::next(matrix.begin(), rows_size))) set_row(row - matrix.begin(), *row); }
	matrix_t(const std::vector<data_t>& matrix) { std::move(matrix.begin(), std::next(matrix.begin(), linear_size), linear_array.begin()); }

	template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<type_t, matrix_t<data_t, rows_t, columns_t>>
	matrix_t(const type_t& value) { *this = null::compatibility::data_type_converter_t<type_t, matrix_t<data_t, rows_t, columns_t>>::convert(value); }

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
	template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<matrix_t<data_t, rows_t, columns_t>, type_t>
	operator type_t() const { return null::compatibility::data_type_converter_t<matrix_t<data_t, rows_t, columns_t>, type_t>::convert(*this); }

	template <typename self_t> auto&& operator [](this self_t&& self, const int& i) { return self.data[i]; }

	template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.data; return self; }
	template <typename self_t> auto operator ++(this self_t&& self, int) { return matrix_t{ self.data++ }; }
	template <typename self_t> auto&& operator --(this self_t&& self) { --self.data; return self; }
	template <typename self_t> auto operator --(this self_t&& self, int) { return matrix_t{ self.data-- }; }                                                                                 

	template <typename self_t> auto operator -(this self_t&& self) { return matrix_t{ -self.data }; }
#define fast_arithmetic_operators(op) class_create_arithmetic_operators(matrix, matrix_t, op, { return self.data op matrix.data; });
	fast_arithmetic_operators(-); fast_arithmetic_operators(+); fast_arithmetic_operators(/); fast_arithmetic_operators(%);

	template <typename self_t, typename another_data_t, template <typename> class another_rows_t, template <typename> class another_columns_t>
	auto operator*(this self_t&& self, const matrix_t<another_data_t, another_rows_t, another_columns_t>& matrix) {
		matrix_t<another_data_t, another_rows_t, another_columns_t> result{ };

		constexpr size_t rows{ std::min(rows_size, another_rows_t<another_data_t>::array_size) }, columns{ std::min(columns_size, another_columns_t<another_data_t>::array_size) };
		for(const int& row : std::views::iota(0u, rows))
			for(const int& column : std::views::iota(0u, columns))
				result[row][column] = self.get_column(column).dot(matrix.get_row(row));
		return result;
	}

	template <typename self_t>
	auto operator*(this self_t&& self, const columns_t<data_t>& column) {
		columns_t<data_t> result{ };
		for(const int& row : std::views::iota(0u, rows_size))
			for(const int& column : std::views::iota(0u, columns_size))
				result[column] = self.get_column(column).dot(column);
		return result;
	}

	template <typename self_t, typename another_data_t, template <typename> class another_rows_t, template <typename> class another_columns_t> auto operator*=(this self_t&& self, const matrix_t<another_data_t, another_rows_t, another_columns_t>& matrix) { self = self * matrix; return self; }
	template <typename self_t> auto operator*=(this self_t&& self, const columns_t<data_t>& column) { self = self * column; return self; }

	template <typename another_data_t> bool operator ==(const matrix_t<another_data_t, rows_t, columns_t>& matrix) const { return data == matrix.data; };
	template <typename another_t> bool operator ==(const another_t& value) const { return data == value; };
#define fast_logic_operators(op) class_create_logic_operators(matrix, matrix_t, op, { return self.data op matrix.data; }, { return self.data op##= matrix.data; });
	fast_logic_operators(<); fast_logic_operators(>);
};

struct matrix4x4_t : public matrix_t<float, vec4_t, vec4_t> {
public: using matrix_t<float, vec4_t, vec4_t>::matrix_t;
	static matrix4x4_t identity() {
		static const matrix4x4_t matrix{
			{ 1.f, 0.f, 0.f, 0.f },
			{ 0.f, 1.f, 0.f, 0.f },
			{ 0.f, 0.f, 1.f, 0.f },
			{ 0.f, 0.f, 0.f, 1.f }
			};
		return matrix;
	}

	static matrix4x4_t project_ortho(const float& left, const float& right, const float& bottom, const float& top, const float& near_plane, const float& far_plane) {
		return {
			{ 2.f / (right - left),				0.f,								0.f,													0.f	},
			{ 0.f,								2.f / (top - bottom),				0.f,													0.f },
			{ 0.f,								0.f,								2 / (far_plane - near_plane),							0.f },
			{ -(right + left) / (right - left),	-(top + bottom) / (top - bottom),	-(far_plane + near_plane) / (far_plane - near_plane),	1.f }
			};
	}

	static matrix4x4_t project_perspective(const float& left, const float& right, const float& bottom, const float& top, const float& near_plane, const float& far_plane) {
		return {
			{ 2.f * near_plane / (right - left),	0.f,								0.f,														0.f	},
			{ 0.f,									2.f * near_plane / (top - bottom),	0.f,														0.f	},
			{ (right + left) / (right - left),		(top + bottom) / (top - bottom),	-(far_plane + near_plane) / (far_plane - near_plane),		-1.f },
			{ 0.f,									0.f,								-(2 * far_plane * near_plane) / (far_plane - near_plane),	0.f	}
			};
	}

public:
	matrix4x4_t() { }

	matrix4x4_t(const matrix_t<float, vec4_t, vec4_t>& matrix) : matrix_t{ matrix.data } { }
	matrix4x4_t(const vec4_t<float>& row1, const vec4_t<float>& row2, const vec4_t<float>& row3, const vec4_t<float>& row4) : matrix_t{ { row1, row2, row3, row4 } } { }
};