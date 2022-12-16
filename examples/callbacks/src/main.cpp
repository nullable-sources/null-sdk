#include <iostream>
#include <null-sdk.h>
#include <variant>
#include <tuple>

enum class e_calls {
    first,
    second,
};

int main() {
    try {
        {
            std::cout << "single example" << std::endl;
            utils::callbacks_tuple_t<
                utils::callback_t<e_calls::first, void()>,
                utils::callback_t<e_calls::second, int()>
            > callbacks{ };
            callbacks.at<e_calls::first>().set([] { std::cout << "e_calls::first" << std::endl; });
            callbacks.at<e_calls::first>().call();

            callbacks.at<e_calls::second>().set([] { std::cout << "e_calls::second" << std::endl; return 1; });
            std::cout << callbacks.at<e_calls::second>().call() << std::endl;
        }

        std::cout << std::endl;

        {
            std::cout << "array example" << std::endl;
            utils::callbacks_tuple_t<
                utils::callbacks_t<e_calls::first, void()>,
                utils::callbacks_t<e_calls::second, int()>
            > callbacks{ };
            callbacks.at<e_calls::first>().add([] { std::cout << "e_calls::first" << std::endl; });
            callbacks.at<e_calls::first>().call();

            callbacks.at<e_calls::second>().add([] { std::cout << "e_calls::second" << std::endl; return 1; });
            auto second{ callbacks.at<e_calls::second>().add([] { std::cout << "e_calls::second" << std::endl; return 2; }) };
            for(const int& result : callbacks.at<e_calls::second>().call()) {
                std::cout << result << " ";
            } std::cout << std::endl;

            callbacks.at<e_calls::second>().remove(second);
            for(const int& result : callbacks.at<e_calls::second>().call()) {
                std::cout << result << " ";
            } std::cout << std::endl;
        }
    } catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}