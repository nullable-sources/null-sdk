#pragma once
#include <ranges>
#include <algorithm>

#include "../vec4.h"

namespace ntl::sdk {
    template <size_t size, typename data_t> struct vec_type_selector_t { using vec_t = data_t; };
    template <typename data_t> struct vec_type_selector_t<2, data_t> { using vec_t = vec2_t<data_t>; };
    template <typename data_t> struct vec_type_selector_t<3, data_t> { using vec_t = vec3_t<data_t>; };
    template <typename data_t> struct vec_type_selector_t<4, data_t> { using vec_t = vec4_t<data_t>; };

    struct packed_access_t {
    public:
        static inline void set(auto&& matrix, size_t i, const auto& new_data) { matrix.data[i] = new_data; }
        template <typename value_t> static inline auto& get(auto&& matrix, size_t i) { return matrix.data[i]; }
    };

    template <size_t stride_size>
    struct stride_access_t {
    public:
        static inline void set(auto&& matrix, size_t i, const auto& new_value) {
            for(int value_idx = 0; i < matrix.linear_array.size(); i += stride_size)
                matrix.linear_array[i] = new_value[value_idx++];
        }

        template <typename value_t>
        static inline auto get(auto&& matrix, size_t i) {
            typename vec_type_selector_t<stride_size, value_t>::vec_t result{ };

            for(int idx = 0; i < matrix.linear_array.size(); i += stride_size)
                result[idx++] = matrix.linear_array[i];

            return result;
        }
    };

    struct row_major_t;
    struct column_major_t;

    struct row_major_t {
    public:
        using transpose_major_t = column_major_t;

        template <size_t rows_num> using row_access_t = packed_access_t;
        template <size_t columns_num> using column_access_t = stride_access_t<columns_num>;

        template <typename row_header_t, typename column_header_t, size_t rows_num, size_t columns_num>
        using vec_representation_t = typename vec_type_selector_t<rows_num, row_header_t>::vec_t;

        template <typename data_t, size_t rows_num, size_t columns_num>
        using array_representation_t = std::array<std::array<data_t, columns_num>, rows_num>;

    public:
        static auto&& get_by_index(auto&& matrix, size_t row, size_t column) { return matrix.data[row][column]; }
    };

    struct column_major_t {
    public:
        using transpose_major_t = row_major_t;

        template <size_t rows_num> using row_access_t = stride_access_t<rows_num>;
        template <size_t columns_num> using column_access_t = packed_access_t;

        template <typename row_header_t, typename column_header_t, size_t rows_num, size_t columns_num>
        using vec_representation_t = typename vec_type_selector_t<columns_num, column_header_t>::vec_t;

        template <typename data_t, size_t rows_num, size_t columns_num>
        using array_representation_t = std::array<std::array<data_t, rows_num>, columns_num>;

    public:
        static auto&& get_by_index(auto&& matrix, size_t row, size_t column) { return matrix.data[column][row]; }
    };

    template <typename major_type_t, typename data_t, size_t rows_num, size_t columns_num>
    class i_matrix {
    public:
        static inline i_matrix identity() { return i_matrix{ }.set_diagonal({ 1.f }); }

    public:
        static constexpr size_t diagonal_size = std::min(rows_num, columns_num);
        static constexpr size_t linear_size = rows_num * columns_num;

        using column_header_t = typename vec_type_selector_t<rows_num, data_t>::vec_t;
        using columns_t = typename vec_type_selector_t<columns_num, column_header_t>::vec_t;

        using row_header_t = typename vec_type_selector_t<columns_num, data_t>::vec_t;
        using rows_t = typename vec_type_selector_t<rows_num, row_header_t>::vec_t;

        using diagonal_t = typename vec_type_selector_t<diagonal_size, data_t>::vec_t;

        using transpose_t = i_matrix<typename major_type_t::transpose_major_t, data_t, rows_num, columns_num>;
        using row_access_t = typename major_type_t::template row_access_t<rows_num>;
        using column_access_t = typename major_type_t::template column_access_t<columns_num>;
        using vec_representation_t = typename major_type_t::template vec_representation_t<row_header_t, column_header_t, rows_num, columns_num>;
        using array_representation_t = typename major_type_t::template array_representation_t<data_t, rows_num, columns_num>;

        template <typename other_data_t>
        using different_data_type_t = i_matrix<major_type_t, other_data_t, rows_num, columns_num>;

        template <size_t other_rows_num, size_t other_columns_num>
        using different_size_t = i_matrix<major_type_t, data_t, other_rows_num, other_columns_num>;

    public:
        union {
            vec_representation_t data;
            array_representation_t array;
            std::array<data_t, linear_size> linear_array{ };
        };

    public:
        inline constexpr i_matrix() { }

        inline constexpr i_matrix(std::same_as<row_header_t> auto&& ... headers) { set_rows(rows_t(headers...)); }
        inline constexpr i_matrix(const rows_t& rows) { set_rows(rows); }
        inline i_matrix(const array_representation_t& matrix) : array(matrix) { }
        inline i_matrix(const std::array<data_t, linear_size>& matrix) : linear_array(matrix) { }

        template <size_t another_rows_num, size_t another_columns_num>
        i_matrix(const i_matrix<major_type_t, data_t, another_rows_num, another_columns_num>& matrix) {
            if constexpr(diagonal_size > std::min(another_rows_num, another_columns_num))
                set_diagonal(1.f);

            constexpr size_t min_rows_num = std::min(rows_num, another_rows_num);
            for(int row = 0; row < min_rows_num; row++)
                set_row(row, matrix.get_row(row));
        }

        template <typename type_t> requires ntl::compatibility::data_type_convertertable<type_t, i_matrix<major_type_t, data_t, rows_num, columns_num>>
        inline constexpr i_matrix(const type_t& value) : i_matrix(ntl::compatibility::data_type_converter_t<type_t, i_matrix<major_type_t, data_t, rows_num, columns_num>>::convert(value)) { }

    public:
        template <typename self_t> inline auto&& get_by_index(this self_t&& self, size_t row, size_t column) { return major_type_t::get_by_index(self, row, column); }
        template <typename self_t> inline auto&& fill_rows(this self_t&& self, const row_header_t& row) { for(int i = 0; i < rows_num; i++) self.set_row(i, row); return self; }
        template <typename self_t> inline auto&& fill_columns(this self_t&& self, const column_header_t& column) { for(int i = 0; i < columns_num; i++) self.set_column(i, column); return self; }

        template <typename self_t> inline auto&& set_rows(this self_t&& self, const rows_t& rows) { for(int i = 0; i < rows_num; i++) self.set_row(i, rows[i]); return self; }
        template <typename self_t> inline auto&& set_row(this self_t&& self, size_t i, const row_header_t& row) { row_access_t::set(self, i, row); return self; }
        template <typename self_t> inline row_header_t get_row(this self_t&& self, size_t i) { return row_access_t::template get<data_t>(self, i); }

        template <typename self_t> inline auto&& set_columns(this self_t&& self, const columns_t& columns) { for(int i = 0; i < columns_num; i++) self.set_column(i, columns[i]); return self; }
        template <typename self_t> inline auto&& set_column(this self_t&& self, size_t i, const column_header_t& column) { column_access_t::set(self, i, column); return self; }
        template <typename self_t> inline column_header_t get_column(this self_t&& self, size_t i) { return column_access_t::template get<data_t>(self, i); }

    public:
        inline transpose_t transpose() const {
            transpose_t transpose{ };
            for(int i = 0; i < rows_num; i++)
                transpose.set_row(i, get_row(i));
            return transpose;
        }

        template <typename self_t>
        inline auto&& set_diagonal(this self_t&& self, const diagonal_t& value) {
            for(int i = 0; i < diagonal_size; i++) self.data[i][i] = value[i];
            return self;
        }

        inline diagonal_t get_diagonal() const {
            diagonal_t result{ };
            for(int i = 0; i < diagonal_size; i++) { result[i] = data[i][i]; }
            return result;
        }

    public:
        inline operator transpose_t() const { return transpose(); }

        template <typename type_t> requires ntl::compatibility::data_type_convertertable<i_matrix<major_type_t, data_t, rows_num, columns_num>, type_t>
        inline constexpr operator type_t() const { return ntl::compatibility::data_type_converter_t<i_matrix<major_type_t, data_t, rows_num, columns_num>, type_t>::convert(*this); }

        template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.data[i]; }

        NULLSDK_FAST_OPS_STRUCTURE_ALL_PREFIX_OPERATORS(inline constexpr, data);
        NULLSDK_FAST_OPS_STRUCTURE_ALL_POSTFIX_OPERATORS(inline constexpr, data);

        template <typename other_data_t, size_t other_rows_num, size_t other_columns_num>
        auto operator*(const i_matrix<major_type_t, other_data_t, other_rows_num, other_columns_num>& rhs) const {
            constexpr size_t rows = std::min(rows_num, other_rows_num), columns = std::min(columns_num, other_columns_num);
            i_matrix<major_type_t, other_data_t, rows, other_columns_num> result{ };
            for(int row = 0; row < rows; row++) {
                auto vec_row = get_row(row);
                for(int column = 0; column < other_columns_num; column++)
                    result.get_by_index(row, column) = vec_row.dot(rhs.get_column(column));
            }
            return result;
        }

        auto operator*(const column_header_t& rhs) const {
            column_header_t result{ };
            for(int row = 0; row < rows_num; row++)
                result[row] = get_row(row).dot(rhs);
            return result;
        }

        template <typename self_t, typename other_data_t> inline auto&& operator*=(this self_t&& self, const different_data_type_t<other_data_t>& rhs) { self = self * rhs; return self; }
        template <typename self_t> inline auto&& operator*=(this self_t&& self, const column_header_t& rhs) { self = self * rhs; return self; }

        NULLSDK_FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, template <typename other_data_t>, const different_data_type_t<other_data_t>&, RHS_FIELD, data);
        NULLSDK_FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, , data_t, RHS_VALUE, data);
    };
}

#define NULLSDK_MAKE_MATRIX_DEFINITION(rows_num, columns_num)                                                                                                                                           \
    template <typename major_type_t>                                                                                                                                                                    \
    class c_matrix##rows_num##x##columns_num : public ntl::sdk::i_matrix<major_type_t, float, rows_num, columns_num> {                                                                                  \
    public:                                                                                                                                                                                             \
        using ntl::sdk::i_matrix<major_type_t, float, rows_num, columns_num>::i_matrix;                                                                                                                 \
        c_matrix##rows_num##x##columns_num##(const ntl::sdk::i_matrix<major_type_t, float, rows_num, columns_num>& matrix) : ntl::sdk::i_matrix<major_type_t, float, rows_num, columns_num>(matrix) { } \
    };                                                                                                                                                                                                  \
    using matrix##rows_num##x##columns_num##_t = c_matrix##rows_num##x##columns_num##<ntl::sdk::column_major_t>;                                                                                        \

NULLSDK_MAKE_MATRIX_DEFINITION(2, 3);
NULLSDK_MAKE_MATRIX_DEFINITION(2, 4);

NULLSDK_MAKE_MATRIX_DEFINITION(3, 2);
NULLSDK_MAKE_MATRIX_DEFINITION(3, 4);

NULLSDK_MAKE_MATRIX_DEFINITION(4, 2);
NULLSDK_MAKE_MATRIX_DEFINITION(4, 3);