module;
#include <ranges>
#include <cmath>
#include <vector>

#include <utils/fast_operators.h>

export module null.sdk:math.matrix;

import :math.vec2;
import :math.vec3;
import :math.vec4;

export namespace null::sdk {
	struct packed_access_t {
	public:
		static auto get(auto& matrix, const size_t& i) { return matrix.data[i]; }
		static void set(auto& matrix, const size_t& i, const auto& new_data) { matrix.data[i] = new_data; }
	};

	template <size_t stride_size>
	struct stride_access_t {
	public:
		static void set(auto& matrix, const size_t& i, const auto& new_data) {
			for(int data_i{ }; auto & data : matrix.linear_array | std::views::drop(i) | std::views::stride(stride_size))
				data = new_data[data_i++];
		}

		static auto get(auto& matrix, const size_t& i) {
			return matrix.linear_array | std::views::drop(i) | std::views::stride(stride_size) | std::ranges::to<std::vector>();
		}
	};

	template <size_t size, typename data_t> struct vec_type_selector_t { using vec_t = data_t; };
	template <typename data_t> struct vec_type_selector_t<2, data_t> { using vec_t = vec2_t<data_t>; };
	template <typename data_t> struct vec_type_selector_t<3, data_t> { using vec_t = vec3_t<data_t>; };
	template <typename data_t> struct vec_type_selector_t<4, data_t> { using vec_t = vec4_t<data_t>; };

	template <typename data_t, typename row_header_t, typename column_header_t, size_t rows_num, size_t columns_num> struct row_major_t;
	template <typename data_t, typename row_header_t, typename column_header_t, size_t rows_num, size_t columns_num> struct column_major_t;

	template <typename data_t, typename row_header_t, typename column_header_t, size_t rows_num, size_t columns_num>
	struct row_major_t {
	public:
		using transpose_t = column_major_t;

		using row_access_t = packed_access_t;
		using column_access_t = stride_access_t<columns_num>;

		using vec_representation_t = vec_type_selector_t<rows_num, typename row_header_t>::vec_t;
		using array_representation_t = std::array<std::array<data_t, columns_num>, rows_num>;

	public:
		static auto&& get_by_index(auto&& matrix, const size_t& row, const size_t& column) { return matrix.data[row][column]; }
	};

	template <typename data_t, typename row_header_t, typename column_header_t, size_t rows_num, size_t columns_num>
	struct column_major_t {
	public:
		using transpose_t = row_major_t;

		using row_access_t = stride_access_t<rows_num>;
		using column_access_t = packed_access_t;

		using vec_representation_t = vec_type_selector_t<columns_num, typename column_header_t>::vec_t;
		using array_representation_t = std::array<std::array<data_t, rows_num>, columns_num>;

	public:
		static auto&& get_by_index(auto&& matrix, const size_t& row, const size_t& column) { return matrix.data[column][row]; }
	};

	template <template <typename, typename, typename, size_t, size_t> class major_type_t, typename data_t, size_t rows_num, size_t columns_num>
	class i_matrix {
	public:
		static i_matrix identity() { return i_matrix{ }.set_diagonal({ 1.f }); }

	public:
		static constexpr size_t diagonal_size{ std::min(rows_num, columns_num) };
		static constexpr size_t linear_size{ rows_num* columns_num };

		using column_header_t = vec_type_selector_t<rows_num, data_t>::vec_t;
		using columns_t = vec_type_selector_t<columns_num, typename column_header_t>::vec_t;

		using row_header_t = vec_type_selector_t<columns_num, data_t>::vec_t;
		using rows_t = vec_type_selector_t<rows_num, typename row_header_t>::vec_t;

		using diagonal_t = vec_type_selector_t<diagonal_size, data_t>::vec_t;

		using major_t = major_type_t<data_t, typename row_header_t, typename column_header_t, rows_num, columns_num>;
		using transpose_t = i_matrix<major_t::transpose_t, data_t, rows_num, columns_num>;
		using vec_representation_t = major_t::vec_representation_t;
		using array_representation_t = major_t::array_representation_t;

	public:
		union {
			vec_representation_t data;
			array_representation_t array{ };
			std::array<data_t, linear_size> linear_array;
		};

	public:
		i_matrix() { }

		i_matrix(const rows_t& rows) { set_rows(rows); }
		i_matrix(const array_representation_t& matrix) : array{ matrix } { }
		i_matrix(const std::array<data_t, linear_size>& matrix) : linear_array{ matrix } { }

		template <size_t another_rows_num, size_t another_columns_num>
		i_matrix(const i_matrix<major_type_t, data_t, another_rows_num, another_columns_num>& matrix) {
			if(diagonal_size > std::min(another_rows_num, another_columns_num))
				set_diagonal(1.f);

			for(const int& row : std::views::iota(0u, std::min(rows_num, another_rows_num)))
				set_row(row, matrix.get_row(row));
		}

		template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<type_t, i_matrix<major_type_t, data_t, rows_num, columns_num>>
		i_matrix(const type_t& value) { *this = null::compatibility::data_type_converter_t<type_t, i_matrix<major_type_t, data_t, rows_num, columns_num>>::convert(value); }

	public:
		auto& get_by_index(const size_t& row, const size_t& column) const { return major_t::get_by_index(*this, row, column); }
		auto& get_by_index(const size_t& row, const size_t& column) { return major_t::get_by_index(*this, row, column); }
		auto& fill_rows(const row_header_t& row) { for(const int& i : std::views::iota(0u, rows_num)) set_row(i, row); return *this; }
		auto& fill_columns(const column_header_t& column) { for(const int& i : std::views::iota(0u, columns_num)) set_column(i, column); return *this; }

		auto& set_rows(const rows_t& rows) { for(const int& i : std::views::iota(0u, rows_num)) set_row(i, rows[i]); return *this; }
		auto& set_row(const int& i, const row_header_t& row) { major_t::row_access_t::set(*this, i, row); return *this; }
		row_header_t get_row(const int& i) const { return major_t::row_access_t::get(*this, i); }

		auto& set_columns(const columns_t& columns) { for(const int& i : std::views::iota(0u, columns_num)) set_column(i, columns[i]); return *this; }
		auto& set_column(const int& i, const column_header_t& column) { major_t::column_access_t::set(*this, i, column); return *this; }
		column_header_t get_column(const int& i) const { return major_t::column_access_t::get(*this, i); }

	public:
		transpose_t transpose() const {
			transpose_t transpose{ };
			for(const int& i : std::views::iota(0u, rows_num))
				transpose.set_row(i, get_row(i));
			return transpose;
		}

		auto& set_diagonal(const diagonal_t& value) {
			for(const int& i : std::views::iota(0u, diagonal_size)) data[i][i] = value[i];
			return *this;
		}

		diagonal_t get_diagonal() const {
			diagonal_t result{ };
			for(const int& i : std::views::iota(0u, diagonal_size)) { result[i] = data[i][i]; }
			return result;
		}

	public:
		operator transpose_t() const { return transpose(); }

		template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<i_matrix<major_type_t, data_t, rows_num, columns_num>, type_t>
		operator type_t() const { return null::compatibility::data_type_converter_t<i_matrix<major_type_t, data_t, rows_num, columns_num>, type_t>::convert(*this); }

		auto& operator [](const int& i) { return data[i]; }

		auto& operator ++() { ++data; return *this; }
		auto operator ++(int) const { return i_matrix{ data++ }; }
		auto& operator --() { --data; return *this; }
		auto operator --(int) const { return i_matrix{ data-- }; }
		auto operator -() const { return i_matrix{ -data }; }

#define fast_arithmetic_operators(op) class_create_arithmetic_operators(matrix, i_matrix, op, { return data op matrix.data; });
		fast_arithmetic_operators(-); fast_arithmetic_operators(+); fast_arithmetic_operators(/ ); fast_arithmetic_operators(%);

		template <typename another_data_t, size_t another_rows_num, size_t another_columns_num>
		auto operator*(const i_matrix<major_type_t, another_data_t, another_rows_num, another_columns_num>& matrix) const {
			constexpr size_t rows{ std::min(rows_num, another_rows_num) }, columns{ std::min(columns_num, another_columns_num) };
			i_matrix<major_type_t, another_data_t, rows, another_columns_num> result{ };
			for(const int& row : std::views::iota(0u, rows))
				for(const int& column : std::views::iota(0u, another_columns_num))
					result.get_by_index(row, column) = get_row(row).dot(matrix.get_column(column));
			return result;
		}

		auto operator*(const column_header_t& column) const {
			column_header_t result{ };
			for(const int& row : std::views::iota(0u, rows_num))
				result[row] = get_row(row).dot(column);
			return result;
		}

		//@todo: P0847
		template <typename another_data_t> auto operator*=(const i_matrix<major_type_t, another_data_t, rows_num, columns_num>& matrix) { *this = *this * matrix; return *this; }
		auto& operator*=(const column_header_t& column) { *this = *this * column; return *this; }

		template <typename another_data_t> bool operator ==(const i_matrix<major_type_t, another_data_t, rows_num, columns_num>& matrix) const { return data == matrix.data; };
		template <typename another_t> bool operator ==(const another_t& value) const { return data == value; };
#define fast_logic_operators(op) class_create_logic_operators(matrix, i_matrix, op, { return data op matrix.data; }, { return data op##= matrix.data; });
		fast_logic_operators(< ); fast_logic_operators(> );
	};
}

#define make_matrix_definition(rows_num, columns_num)																																							\
	export template <template <typename, typename, typename, size_t, size_t> class major_type_t>																														\
	class c_matrix##rows_num##x##columns_num : public null::sdk::i_matrix<major_type_t, float, rows_num, columns_num> {																							\
	public: using null::sdk::i_matrix<major_type_t, float, rows_num, columns_num>::i_matrix;																													\
		 c_matrix##rows_num##x##columns_num##(const null::sdk::i_matrix<major_type_t, float, rows_num, columns_num>& matrix) : null::sdk::i_matrix<major_type_t, float, rows_num, columns_num>{ matrix } { }	\
	};																																																			\
	export using matrix##rows_num##x##columns_num##_t = c_matrix##rows_num##x##columns_num##<null::sdk::column_major_t>;																								\

make_matrix_definition(2, 3);
make_matrix_definition(2, 4);

make_matrix_definition(3, 2);
make_matrix_definition(3, 4);

make_matrix_definition(4, 2);
make_matrix_definition(4, 3);