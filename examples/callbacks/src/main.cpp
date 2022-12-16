#include <iostream>
#include <null-sdk.h>

enum class e_calls {
    first,
    second
};

int main() {
    try {
        {
            std::cout << "single example" << std::endl;
            single_callbacks_t<e_calls> callbacks{ };
            callbacks.set(e_calls::first, [] { std::cout << "e_calls::first" << std::endl; });
            callbacks.call(e_calls::first);

            callbacks.set(e_calls::second, [] { std::cout << "e_calls::second" << std::endl; return 1; });
            std::cout << callbacks.call<int>(e_calls::second) << std::endl;
        }

        std::cout << std::endl;

        {
            std::cout << "array example" << std::endl;
            array_callbacks_t<e_calls> callbacks{ };
            callbacks.add(e_calls::first, []() { std::cout << "e_calls::first" << std::endl; });
            callbacks.call(e_calls::first);

            callbacks.add(e_calls::second, []() { std::cout << "e_calls::second" << std::endl; return 1; });
            auto second{ callbacks.add(e_calls::second, []() { std::cout << "e_calls::second" << std::endl; return 2; }) };
            for(const int& result : callbacks.call<int>(e_calls::second)) {
                std::cout << result << " ";
            } std::cout << std::endl;

            callbacks.remove(e_calls::second, second);
            for(const int& result : callbacks.call<int>(e_calls::second)) {
                std::cout << result << " ";
            } std::cout << std::endl;
        }
    } catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}