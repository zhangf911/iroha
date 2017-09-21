add_library(boostmultiprecision INTERFACE IMPORTED)

find_path(boostmultiprecision_INCLUDE_DIR boost/multiprecision/cpp_int.hpp)
mark_as_advanced(boostmultiprecision_INCLUDE_DIR)

find_package(PackageHandleStandardArgs REQUIRED)
find_package_handle_standard_args(boostmultiprecision DEFAULT_MSG
    boostmultiprecision_INCLUDE_DIR
    )

if (NOT boostmultiprecision_FOUND)
  externalproject_add(boostorg_multiprecision
      GIT_REPOSITORY https://github.com/boostorg/multiprecision
      GIT_TAG 64387787c27aeea31d293aec99fac356681ad0ee
      BUILD_COMMAND "" # remove build step, header only lib
      CONFIGURE_COMMAND "" # remove configure step
      INSTALL_COMMAND "" # remove install step
      TEST_COMMAND "" # remove test step
      UPDATE_COMMAND "" # remove update step
      )
  externalproject_get_property(boostorg_multiprecision source_dir)
  set(boostmultiprecision_INCLUDE_DIR "${source_dir}/include")

  file(MAKE_DIRECTORY ${boostmultiprecision_INCLUDE_DIR})

  add_dependencies(boostmultiprecision boostorg_multiprecision)
endif ()

set_target_properties(boostmultiprecision PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${boostmultiprecision_INCLUDE_DIR}
    )
