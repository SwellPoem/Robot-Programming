
#TODO: check on exercise of prof on gitlab if all libraries are correct before pushing on git

add_library(utils SHARED
    
    blob.cpp
    deserializer.cpp
    id_context.cpp
    id_placeholder.cpp
    identifiable.cpp
    object_data.cpp
    property_container_manager.cpp
    property_container.cpp
    property_eigen.cpp
    property_identifiable.cpp
    property.cpp
    serializable.cpp
    serialization_context.cpp
    serializer.cpp
)

# NB: if I don't want to check all .cpp files by and i can call a mìcommand on the terminal in the folder
# that shows all the files and I can copy paste
