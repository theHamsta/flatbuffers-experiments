project(flatbuffers-experiment)

cmake_minimum_required(VERSION 3.20)
include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
option(FLATBUFFERS_BUILD_FLATLIB OFF)
option(FLATBUFFERS_BUILD_FLATC OFF)
FetchContent_Declare(
  flatbuffersbuild
  URL      https://github.com/google/flatbuffers/archive/v2.0.0.tar.gz
  URL_HASH SHA256=9ddb9031798f4f8754d00fca2f1a68ecf9d0f83dfac7239af1311e4fd9a565c4
  SOURCE_DIR include/flatbuffers
)
FetchContent_MakeAvailable(flatbuffersbuild)
add_library(flatbuffers_headers INTERFACE)
target_include_directories(flatbuffers_headers INTERFACE ${flatbuffersbuild_SOURCE_DIR})

FetchContent_Declare(
  fmtbuild
  URL      https://github.com/fmtlib/fmt/archive/8.0.1.tar.gz
  URL_HASH SHA256=b06ca3130158c625848f3fb7418f235155a4d389b2abc3a6245fb01cb0eb1e01
)
FetchContent_MakeAvailable(fmtbuild)

aux_source_directory(src SOURCES)

add_executable(flatbuffers-experiment
    main.cpp
    ${SOURCES}
    )

target_include_directories(
    flatbuffers-experiment
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    )

target_link_libraries(flatbuffers-experiment
	PRIVATE
	flatbuffers_headers
	fmt::fmt
	)

set_target_properties(flatbuffers-experiment PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    )

if(UNIX)
	target_compile_options(flatbuffers-experiment
		PRIVATE
		-Wall
		-Wno-long-long
		-pedantic)
endif()
