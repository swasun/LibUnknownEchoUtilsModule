if (systemlib_LIBEI)
    if (WIN32)
        set(LIBERRORINTERCEPTOR_INCLUDE_DIR "C:\\LibErrorInterceptor\\$ENV{name}\\include")
        set(LIBERRORINTERCEPTOR_LIBRARIES "C:\\LibErrorInterceptor\\$ENV{name}\\lib\\ei_static.lib")
    elseif (UNIX)
        set(LIBERRORINTERCEPTOR_LIBRARIES "-lei")
	endif ()
	set(LIBEI_SET true)
else (systemlib_LIBEI)
	include (ExternalProject)

	set(LIBEI_URL https://github.com/swasun/LibErrorInterceptor.git)
	set(LIBEI_INSTALL ${ROOT_BUILD_DIR}/libei/install)
	set(LIBERRORINTERCEPTOR_INCLUDE_DIR ${LIBEI_INSTALL}/include)
	set(LIBEI_BUILD ${ROOT_BUILD_DIR}/libei/src/libei)

	if (WIN32)
		set(LIBERRORINTERCEPTOR_LIBRARIES "${ROOT_BUILD_DIR}\\libei\\install\\lib\\ei_static.lib")
	else()
		set(LIBERRORINTERCEPTOR_LIBRARIES ${ROOT_BUILD_DIR}/libei/install/lib/libei_static.a)
	endif()

	ExternalProject_Add(libei
		PREFIX libei
		GIT_REPOSITORY ${LIBEI_URL}
		BUILD_IN_SOURCE 1
		BUILD_BYPRODUCTS ${LIBERRORINTERCEPTOR_LIBRARIES}
		DOWNLOAD_DIR "${DOWNLOAD_LOCATION}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=Release
			-DCMAKE_INSTALL_PREFIX:STRING=${LIBEI_INSTALL}
			-DCMAKE_C_FLAGS:STRING=-fPIC
	)
endif (systemlib_LIBEI)
