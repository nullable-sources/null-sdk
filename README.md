# Building and linkning

There are two linking options:
* static-linking: .lib.
* dynamic-linking: .dll.

Using both methods is almost the same, the only difference is in the file name.
Compile *.static-linking/.dynamic-linking* *.vcxproj* from the msvc folder, then include *.XXX-linking.props* in our .vcxproj (an example of linking is in the examples), in which we will use the library.