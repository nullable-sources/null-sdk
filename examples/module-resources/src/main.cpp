#include <format>

#include <null-sdk/memory/module/module.h>

int main() {
    try {
        ntl::c_module::self().load_resources();

        if(ntl::resource_t* test_document = ntl::c_module::self().find_resource("test-document"))
            std::cout << "first finded test-document from module - '" << ntl::resource_cast_t<std::string>::cast(test_document->load()) << "'" << std::endl;

        std::cout << "test-document from 'second-resource' -'" << ntl::resource_cast_t<std::string>::cast(ntl::resource_t("test-document", "second-resource").load()) << "'" << std::endl;
    } catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}
