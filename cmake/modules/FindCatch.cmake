include(ExternalProject)
externalproject_add(catch
   CONFIGURE_COMMAND ""
   BUILD_COMMAND ""
   INSTALL_COMMAND ""
   GIT_REPOSITORY https://github.com/philsquared/Catch.git)

# Expose required variable (Catch_INCLUDE_DIR) to parent scope
externalproject_get_property(catch SOURCE_DIR)
set(Catch_INCLUDE_DIRS ${SOURCE_DIR}/single_include
   CACHE INTERNAL "Path to include folder for Catch")

# find_package boilerplate
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Catch DEFAULT_MSG Catch_INCLUDE_DIRS)
mark_as_advanced(Catch_INCLUDE_DIRS)
