# TODO compile executable that will be run  
add_executable(
    many_object_in_stack_example
    many_object_in_stack_example.cpp
    )
#most of the errors we had were caused by not include something, this is why we use target_link_libraries
#i want to compile all files that ends with .cpp because presumebly all of them include the symbols that we need
#so i copy paste all of them in the cmakelists od src
target_link_libraries(
    many_object_in_stack_example
    messages
    utils
    )