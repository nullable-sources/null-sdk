#include <null-sdk.h>
#include <format>

int main() {
	try {
		memory::c_module::self().load_resources();
		
		if(memory::resource_t* test_document{ memory::c_module::self().find_resource("test-document") })
			std::cout << "first finded test-document from module - '" << memory::resource_cast_t<std::string>::cast(test_document->load()) << "'" << std::endl;
		
		std::cout << "test-document from 'second-resource' -'" << memory::resource_cast_t<std::string>::cast(memory::resource_t{ "test-document", "second-resource" }.load()) << "'" << std::endl;
	} catch(const std::exception& exception) {
		std::cout << exception.what() << std::endl;
	}
}
