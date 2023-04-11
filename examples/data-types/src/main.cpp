#include <iostream>
#include <null-sdk.h>

math_make_templates(vec2_t, coordinates_t)
void print_type(const std::string_view& str, const vec2_t<coordinates_t>& vec) { std::cout << str << "{ " << std::format("[{}; {}]", vec.x, vec.y) << " }" << std::endl; }

math_make_templates(vec3_t, coordinates_t)
void print_type(const std::string_view& str, const vec3_t<coordinates_t>& vec) { std::cout << str << "{ " << std::format("[{}; {}; {}]", vec.x, vec.y, vec.z) << " }" << std::endl; }

math_make_templates(rect_t, coordinates_t)
void print_type(const std::string_view& str, const rect_t<coordinates_t>& rect) { std::cout << str << "{ " << std::format("min: [{}; {}]; max: [{}; {}]", rect.min.x, rect.min.y, rect.max.x, rect.max.y) << " }" << std::endl; }

void callbacks() {
    enum class e_calls {
        first,
        second,
    };

    std::cout << "callbacks example {" << std::endl;

    {
        std::cout << "\tsingle example {" << std::endl;

        utils::callbacks_tuple_t<
            utils::callback_t<e_calls::first, void()>,
            utils::callback_t<e_calls::second, int()>
        > callbacks{ };
        callbacks.at<e_calls::first>().set([] { std::cout << "\t\te_calls::first called" << std::endl; });
        callbacks.at<e_calls::first>().call();

        callbacks.at<e_calls::second>().set([] { std::cout << "\t\te_calls::second called" << std::endl; return 1; });
        int result{ callbacks.at<e_calls::second>().call() };
        std::cout << "\t\te_calls::second result ->{ " << result << " }" << std::endl;

        std::cout << "\t}" << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "\tarray example {" << std::endl;
        utils::callbacks_tuple_t<
            utils::callbacks_t<e_calls::first, void()>,
            utils::callbacks_t<e_calls::second, int()>
        > callbacks{ };

        callbacks.at<e_calls::second>().add([] { return 1; });
        auto second{ callbacks.at<e_calls::second>().add([] { return 2; }) };
        std::cout << "\t\tresults ->{ ";
        for(const int& result : callbacks.at<e_calls::second>().call()) {
            std::cout << result << " ";
        } std::cout << "}" << std::endl;

        callbacks.at<e_calls::second>().remove(second);
        std::cout << "\t\tresults after remove ->{ ";
        for(const int& result : callbacks.at<e_calls::second>().call()) {
            std::cout << result << " ";
        } std::cout << "}" << std::endl;

        std::cout << "\t}" << std::endl;
    }

    std::cout << "}" << std::endl << std::endl;
}

void vec2() {
    vec2_t<int> a{ 11, 23 };
    vec2_t<float> b{ 4.f, 14.f };

    std::cout << "vec2 examples {" << std::endl;
    
    print_type("\ta<int> ->", a);
    print_type("\tb<float> ->", b);
    
    std::cout << std::endl;

    {
        std::cout << "\toperators {" << std::endl;

        print_type("\t\ta + b ->", a + b);
        print_type("\t\ta - b ->", a - b);
        print_type("\t\ta * b ->", a * b);
        print_type("\t\ta / b ->", a / b);
        std::cout << "\t\ta == b ->" << std::format("{{ {} }}", a == b) << std::endl;
        std::cout << "\t\ta < b  ->" << std::format("{{ {} }}", a < b) << std::endl;
        std::cout << "\t\ta <= b ->" << std::format("{{ {} }}", a <= b) << std::endl;
        std::cout << "\t\ta > b  ->" << std::format("{{ {} }}", a > b) << std::endl;
        std::cout << "\t\ta >= b ->" << std::format("{{ {} }}", a >= b) << std::endl;

        std::cout << "\t}" << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "\tmethods {" << std::endl;

        std::cout << "\t\ta.length() ->{ " << a.length() << " }" << std::endl;
        std::cout << "\t\tb.length() ->{ " << b.length() << " }" << std::endl;
        std::cout << "\t\ta.cross(b) ->{ " << a.cross(b) << " }" << std::endl;
        std::cout << "\t\ta.dot(b)   ->{ " << a.dot(b) << " }" << std::endl;

        std::cout << "\t}" << std::endl;
    }

    std::cout << "}" << std::endl << std::endl;
}

void vec3() {
    vec3_t<int> a{ 11, 23, 3 };
    vec3_t<float> b{ 4, 14, 12 };

    std::cout << "vec3 examples {" << std::endl;
    
    print_type("\ta<int> ->", a);
    print_type("\tb<float> ->", b);
    
    std::cout << std::endl;

    {
        std::cout << "\toperators {" << std::endl;

        print_type("\t\ta + b ->", a + b);
        print_type("\t\ta - b ->", a - b);
        print_type("\t\ta * b ->", a * b);
        print_type("\t\ta / b ->", a / b);
        std::cout << "\t\ta == b ->" << std::format("{{ {} }}", a == b) << std::endl;
        std::cout << "\t\ta < b  ->" << std::format("{{ {} }}", a < b) << std::endl;
        std::cout << "\t\ta <= b ->" << std::format("{{ {} }}", a <= b) << std::endl;
        std::cout << "\t\ta > b  ->" << std::format("{{ {} }}", a > b) << std::endl;
        std::cout << "\t\ta >= b ->" << std::format("{{ {} }}", a >= b) << std::endl;

        std::cout << "\t}" << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "\tmethods {" << std::endl;

        std::cout << "\t\ta.length()     ->{ " << a.length() << " }" << std::endl;
        std::cout << "\t\tb.length()     ->{ " << b.length() << " }" << std::endl;
        std::cout << "\t\ta.dot(b)       ->{ " << a.dot(b) << " }" << std::endl;
        std::cout << "\t\ta.dist_to(b)   ->{ " << a.dist_to(b) << " }" << std::endl;
        print_type("\t\ta.cross(b)     ->", a.cross(b));
        print_type("\t\ta.normalized() ->", a.normalized());

        std::cout << "\t}" << std::endl;
    }

    std::cout << "}" << std::endl << std::endl;
}

void rect() {    
    std::cout << "rect examples {" << std::endl;

    {
        static const auto print{ [](const std::string_view& str, const auto& origin) { print_type(std::string{ "\t\t" }.append(str), rect_t{ 0.f, 100.f }.origin(origin)); } };
        
        std::cout << "\torigin from rect {" << std::endl;
        print_type("\t\trect ->", rect_t{ 0.f, 100.f });
        std::cout << std::endl;
        print("rect_t::top    | rect_t::left  ->", null::e_rect_origin::top    | null::e_rect_origin::left);
        print("rect_t::top    | rect_t::right ->", null::e_rect_origin::top    | null::e_rect_origin::right);
        print("rect_t::bottom | rect_t::left  ->", null::e_rect_origin::bottom | null::e_rect_origin::left);
        print("rect_t::bottom | rect_t::right ->", null::e_rect_origin::bottom | null::e_rect_origin::right);
        print("rect_t::center                 ->", null::e_rect_origin::center);
        print("rect_t::center | rect_t::top   ->", null::e_rect_origin::center | null::e_rect_origin::top);
        print("rect_t::center | rect_t::bottom->", null::e_rect_origin::center | null::e_rect_origin::bottom);
        print("rect_t::center | rect_t::left  ->", null::e_rect_origin::center | null::e_rect_origin::left);
        print("rect_t::center | rect_t::right ->", null::e_rect_origin::center | null::e_rect_origin::right);
        std::cout << "\t}" << std::endl;
    }

    std::cout << std::endl;
    {
        static const auto print{ [](const std::string_view& str, const auto& origin, const vec2_t<float>& vec) {
            print_type("\t\torigin ->", vec);
            print_type(std::string{ "\t\t" }.append(str), rect_t{ vec, vec2_t{ 100.f }, origin });
            std::cout << std::endl;
        } };

        std::cout << "\trect from origin {" << std::endl;
        print_type("\t\tsize ->", vec2_t{ 100.f });
        std::cout << std::endl;
        print("rect_t::top | rect_t::left     ->", null::e_rect_origin::top    | null::e_rect_origin::left,   0.f);
        print("rect_t::top | rect_t::right    ->", null::e_rect_origin::top    | null::e_rect_origin::right,  { 100.f, 0.f });
        print("rect_t::bottom | rect_t::left  ->", null::e_rect_origin::bottom | null::e_rect_origin::left,   { 0.f, 100.f });
        print("rect_t::bottom | rect_t::right ->", null::e_rect_origin::bottom | null::e_rect_origin::right,  100.f);
        print("rect_t::center                 ->", null::e_rect_origin::center,                  50.f);
        print("rect_t::center | rect_t::top   ->", null::e_rect_origin::center | null::e_rect_origin::top,    { 50.f, 0.f });
        print("rect_t::center | rect_t::bottom->", null::e_rect_origin::center | null::e_rect_origin::bottom, { 50.f, 100.f });
        print("rect_t::center | rect_t::left  ->", null::e_rect_origin::center | null::e_rect_origin::left,   { 0.f, 50.f });
        print("rect_t::center | rect_t::right ->", null::e_rect_origin::center | null::e_rect_origin::right,  { 100.f, 50.f });
        std::cout << "\t}" << std::endl;
    }

    std::cout << std::endl;

    {
        static const auto print{ [](const std::string_view& str, const auto& origin) {
            print_type(std::string{ "\t\t" }.append(str), rect_t{ 0.f, 100.f }.scale(origin, 0.5f));
        } };

        std::cout << "\tscaling rect {" << std::endl;
        print_type("\t\trect ->", rect_t{ 0.f, 100.f });
        print_type("\t\tscale ->", vec2_t{ 0.5f });
        std::cout << std::endl;
        print("rect_t::top | rect_t::left     ->", null::e_rect_origin::top | null::e_rect_origin::left);
        print("rect_t::top | rect_t::right    ->", null::e_rect_origin::top | null::e_rect_origin::right);
        print("rect_t::bottom | rect_t::left  ->", null::e_rect_origin::bottom | null::e_rect_origin::left);
        print("rect_t::bottom | rect_t::right ->", null::e_rect_origin::bottom | null::e_rect_origin::right);
        print("rect_t::center                 ->", null::e_rect_origin::center);
        print("rect_t::center | rect_t::top   ->", null::e_rect_origin::center | null::e_rect_origin::top);
        print("rect_t::center | rect_t::bottom->", null::e_rect_origin::center | null::e_rect_origin::bottom);
        print("rect_t::center | rect_t::left  ->", null::e_rect_origin::center | null::e_rect_origin::left);
        print("rect_t::center | rect_t::right ->", null::e_rect_origin::center | null::e_rect_origin::right);
        std::cout << "\t}" << std::endl;
    }
    std::cout << "}" << std::endl << std::endl;
}

struct user_vec2_t { float x{ }, y{ }; };

template <typename coordinates_t>
struct null::compatibility::data_type_converter_t<vec2_t<coordinates_t>, user_vec2_t> {
    static user_vec2_t convert(const vec2_t<coordinates_t>& vec) {  return { vec.x, vec.y }; }
};

template <typename coordinates_t>
struct null::compatibility::data_type_converter_t<user_vec2_t, vec2_t<coordinates_t>> {
    static vec2_t<coordinates_t> convert(const user_vec2_t& vec) { return { vec.x, vec.y }; }
};

void conv() {
    std::cout << "vec2_t convert" << std::endl; {
        print_type("\tvec2_t<float> from user_vec2_t ->", vec2_t<float>{ user_vec2_t{ 1.f, 2.f } });
        print_type("\tuser_vec2_t from vec2_t<float> ->", vec2_t<float>{ user_vec2_t{ (user_vec2_t)vec2_t{ 1.f, 2.f } } });
    }
}

int main() {
    try {
        callbacks();
        vec2();
        vec3();
        rect();

        conv();
    } catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}