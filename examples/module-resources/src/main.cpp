#include <null-sdk.h>
#include <format>

int main() {
    try {
        ntl::mem::c_module::self().load_resources();

        if(ntl::mem::resource_t* test_document = ntl::mem::c_module::self().find_resource("test-document"))
            std::cout << "first finded test-document from module - '" << ntl::mem::resource_cast_t<std::string>::cast(test_document->load()) << "'" << std::endl;

        std::cout << "test-document from 'second-resource' -'" << ntl::mem::resource_cast_t<std::string>::cast(ntl::mem::resource_t("test-document", "second-resource").load()) << "'" << std::endl;
    } catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}
