add_library(util-filesystem
    filesystem.cpp
    )
target_link_libraries(util-filesystem
    ${Boost_LIBRARIES}
    )
