if (systemlib_LIBEI)
    if (WIN32)
        set(LIBERRORINTERCEPTOR_INCLUDE_DIR "C:\\LibErrorInterceptor\\$ENV{name}\\include")
        set(LIBERRORINTERCEPTOR_LIBRARIES "C:\\LibErrorInterceptor\\$ENV{name}\\lib\\ei_static.lib")
    elseif (UNIX)
        set(LIBERRORINTERCEPTOR_LIBRARIES "-lei")
    endif ()
else (systemlib_LIBEI)
	if (UNIX)
		find_library(LIBERRORINTERCEPTOR_LIBRARIES ei)
		find_path(LIBERRORINTERCEPTOR_INCLUDE_DIR NAMES ei)
	elseif (WIN32)
		if (EXISTS "C:\\LibErrorInterceptor\\$ENV{name}")
			set(LIBERRORINTERCEPTOR_INCLUDE_DIR "C:\\LibErrorInterceptor\\$ENV{name}\\include")
			set(LIBERRORINTERCEPTOR_LIBRARIES "C:\\LibErrorInterceptor\\$ENV{name}\\lib\\ei_static.lib")
		endif ()
	endif ()

    if (NOT ${LIBERRORINTERCEPTOR_LIBRARIES} MATCHES "")
		include (ExternalProject)

		set(LIBEI_URL https://github.com/swasun/LibErrorInterceptor.git)
		set(libei_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/external/libei_archive)
		set(LIBEI_BUILD ${CMAKE_CURRENT_BINARY_DIR}/libei/src/libei)
		set(LIBEI_INSTALL ${CMAKE_CURRENT_BINARY_DIR}/libei/install)

		if (WIN32)
			set(libei_STATIC_LIBRARIES "${CMAKE_CURRENT_BINARY_DIR}\\ei_static.lib")
		else()
			set(libei_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/libei/install/lib/libei.a)
		endif()

		ExternalProject_Add(libei
			PREFIX libei
			GIT_REPOSITORY ${LIBEI_URL}
			BUILD_IN_SOURCE 1
			BUILD_BYPRODUCTS ${libei_STATIC_LIBRARIES}
			DOWNLOAD_DIR "${DOWNLOAD_LOCATION}"
			CMAKE_CACHE_ARGS
				-DCMAKE_BUILD_TYPE:STRING=Release
				-DCMAKE_INSTALL_PREFIX:STRING=${LIBEI_INSTALL}
		)

		if (WIN32)
			set(LIBERRORINTERCEPTOR_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}\\libei\\install\\include")
			set(LIBERRORINTERCEPTOR_LIBRARIES "${CMAKE_CURRENT_BINARY_DIR}\\libei\\install\\lib\\ei_static.lib")
		elseif (UNIX)
			set(LIBERRORINTERCEPTOR_LIBRARIES "-lei")
		endif ()
    endif ()
endif (systemlib_LIBEI)
