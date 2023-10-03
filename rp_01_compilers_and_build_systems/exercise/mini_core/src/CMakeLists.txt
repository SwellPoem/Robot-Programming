# TODO add other .cpp files
# I want to include here te all the files that end with .cpp
# I create CMakeLists.txt in utils and message folders folder such that i don't need this anymore
#add_library(core_library SHARED
 
  
#)

# instead I use these
add_subdirectory(utils)
add_subdirectory(messages)