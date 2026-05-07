
#################
###  BOOST
#################
set(CONAN_BOOST_ROOT_RELEASE "/home/nafan/.conan/data/boost/1.78.0/_/_/package/a0d4e1436288d5f00e9dfbffea6197064706982f")
set(CONAN_INCLUDE_DIRS_BOOST_RELEASE "/home/nafan/.conan/data/boost/1.78.0/_/_/package/a0d4e1436288d5f00e9dfbffea6197064706982f/include")
set(CONAN_LIB_DIRS_BOOST_RELEASE "/home/nafan/.conan/data/boost/1.78.0/_/_/package/a0d4e1436288d5f00e9dfbffea6197064706982f/lib")
set(CONAN_BIN_DIRS_BOOST_RELEASE )
set(CONAN_RES_DIRS_BOOST_RELEASE )
set(CONAN_SRC_DIRS_BOOST_RELEASE )
set(CONAN_BUILD_DIRS_BOOST_RELEASE )
set(CONAN_FRAMEWORK_DIRS_BOOST_RELEASE )
set(CONAN_LIBS_BOOST_RELEASE boost_contract boost_coroutine boost_fiber_numa boost_fiber boost_context boost_graph boost_iostreams boost_json boost_locale boost_log_setup boost_log boost_math_c99 boost_math_c99f boost_math_c99l boost_math_tr1 boost_math_tr1f boost_math_tr1l boost_nowide boost_program_options boost_random boost_regex boost_stacktrace_addr2line boost_stacktrace_backtrace boost_stacktrace_basic boost_stacktrace_noop boost_timer boost_type_erasure boost_thread boost_chrono boost_container boost_date_time boost_unit_test_framework boost_prg_exec_monitor boost_test_exec_monitor boost_exception boost_wave boost_filesystem boost_atomic boost_wserialization boost_serialization)
set(CONAN_PKG_LIBS_BOOST_RELEASE boost_contract boost_coroutine boost_fiber_numa boost_fiber boost_context boost_graph boost_iostreams boost_json boost_locale boost_log_setup boost_log boost_math_c99 boost_math_c99f boost_math_c99l boost_math_tr1 boost_math_tr1f boost_math_tr1l boost_nowide boost_program_options boost_random boost_regex boost_stacktrace_addr2line boost_stacktrace_backtrace boost_stacktrace_basic boost_stacktrace_noop boost_timer boost_type_erasure boost_thread boost_chrono boost_container boost_date_time boost_unit_test_framework boost_prg_exec_monitor boost_test_exec_monitor boost_exception boost_wave boost_filesystem boost_atomic boost_wserialization boost_serialization)
set(CONAN_SYSTEM_LIBS_BOOST_RELEASE dl rt pthread)
set(CONAN_FRAMEWORKS_BOOST_RELEASE )
set(CONAN_FRAMEWORKS_FOUND_BOOST_RELEASE "")  # Will be filled later
set(CONAN_DEFINES_BOOST_RELEASE "-DBOOST_STACKTRACE_ADDR2LINE_LOCATION=\"/usr/bin/addr2line\""
			"-DBOOST_STACKTRACE_USE_ADDR2LINE"
			"-DBOOST_STACKTRACE_USE_BACKTRACE"
			"-DBOOST_STACKTRACE_USE_NOOP")
set(CONAN_BUILD_MODULES_PATHS_BOOST_RELEASE )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_BOOST_RELEASE "BOOST_STACKTRACE_ADDR2LINE_LOCATION=\"/usr/bin/addr2line\""
			"BOOST_STACKTRACE_USE_ADDR2LINE"
			"BOOST_STACKTRACE_USE_BACKTRACE"
			"BOOST_STACKTRACE_USE_NOOP")

set(CONAN_C_FLAGS_BOOST_RELEASE "")
set(CONAN_CXX_FLAGS_BOOST_RELEASE "")
set(CONAN_SHARED_LINKER_FLAGS_BOOST_RELEASE "")
set(CONAN_EXE_LINKER_FLAGS_BOOST_RELEASE "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_BOOST_RELEASE_LIST "")
set(CONAN_CXX_FLAGS_BOOST_RELEASE_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_BOOST_RELEASE_LIST "")
set(CONAN_EXE_LINKER_FLAGS_BOOST_RELEASE_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_BOOST_RELEASE "${CONAN_FRAMEWORKS_BOOST_RELEASE}" "_BOOST" "_RELEASE")
# Append to aggregated values variable
set(CONAN_LIBS_BOOST_RELEASE ${CONAN_PKG_LIBS_BOOST_RELEASE} ${CONAN_SYSTEM_LIBS_BOOST_RELEASE} ${CONAN_FRAMEWORKS_FOUND_BOOST_RELEASE})


#################
###  CATCH2
#################
set(CONAN_CATCH2_ROOT_RELEASE "/home/nafan/.conan/data/catch2/3.7.1/_/_/package/3a97d359160735989fa7e619b5fa4b8b4d45e216")
set(CONAN_INCLUDE_DIRS_CATCH2_RELEASE "/home/nafan/.conan/data/catch2/3.7.1/_/_/package/3a97d359160735989fa7e619b5fa4b8b4d45e216/include")
set(CONAN_LIB_DIRS_CATCH2_RELEASE "/home/nafan/.conan/data/catch2/3.7.1/_/_/package/3a97d359160735989fa7e619b5fa4b8b4d45e216/lib")
set(CONAN_BIN_DIRS_CATCH2_RELEASE )
set(CONAN_RES_DIRS_CATCH2_RELEASE )
set(CONAN_SRC_DIRS_CATCH2_RELEASE )
set(CONAN_BUILD_DIRS_CATCH2_RELEASE "/home/nafan/.conan/data/catch2/3.7.1/_/_/package/3a97d359160735989fa7e619b5fa4b8b4d45e216/lib/cmake/Catch2")
set(CONAN_FRAMEWORK_DIRS_CATCH2_RELEASE )
set(CONAN_LIBS_CATCH2_RELEASE Catch2Main Catch2)
set(CONAN_PKG_LIBS_CATCH2_RELEASE Catch2Main Catch2)
set(CONAN_SYSTEM_LIBS_CATCH2_RELEASE m)
set(CONAN_FRAMEWORKS_CATCH2_RELEASE )
set(CONAN_FRAMEWORKS_FOUND_CATCH2_RELEASE "")  # Will be filled later
set(CONAN_DEFINES_CATCH2_RELEASE )
set(CONAN_BUILD_MODULES_PATHS_CATCH2_RELEASE )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_CATCH2_RELEASE )

set(CONAN_C_FLAGS_CATCH2_RELEASE "")
set(CONAN_CXX_FLAGS_CATCH2_RELEASE "")
set(CONAN_SHARED_LINKER_FLAGS_CATCH2_RELEASE "")
set(CONAN_EXE_LINKER_FLAGS_CATCH2_RELEASE "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_CATCH2_RELEASE_LIST "")
set(CONAN_CXX_FLAGS_CATCH2_RELEASE_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_CATCH2_RELEASE_LIST "")
set(CONAN_EXE_LINKER_FLAGS_CATCH2_RELEASE_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_CATCH2_RELEASE "${CONAN_FRAMEWORKS_CATCH2_RELEASE}" "_CATCH2" "_RELEASE")
# Append to aggregated values variable
set(CONAN_LIBS_CATCH2_RELEASE ${CONAN_PKG_LIBS_CATCH2_RELEASE} ${CONAN_SYSTEM_LIBS_CATCH2_RELEASE} ${CONAN_FRAMEWORKS_FOUND_CATCH2_RELEASE})


#################
###  LIBPQXX
#################
set(CONAN_LIBPQXX_ROOT_RELEASE "/home/nafan/.conan/data/libpqxx/7.7.5/_/_/package/84b287c7f4808a5e98be8eea8f4deb46aa14e092")
set(CONAN_INCLUDE_DIRS_LIBPQXX_RELEASE "/home/nafan/.conan/data/libpqxx/7.7.5/_/_/package/84b287c7f4808a5e98be8eea8f4deb46aa14e092/include")
set(CONAN_LIB_DIRS_LIBPQXX_RELEASE "/home/nafan/.conan/data/libpqxx/7.7.5/_/_/package/84b287c7f4808a5e98be8eea8f4deb46aa14e092/lib")
set(CONAN_BIN_DIRS_LIBPQXX_RELEASE )
set(CONAN_RES_DIRS_LIBPQXX_RELEASE )
set(CONAN_SRC_DIRS_LIBPQXX_RELEASE )
set(CONAN_BUILD_DIRS_LIBPQXX_RELEASE )
set(CONAN_FRAMEWORK_DIRS_LIBPQXX_RELEASE )
set(CONAN_LIBS_LIBPQXX_RELEASE pqxx)
set(CONAN_PKG_LIBS_LIBPQXX_RELEASE pqxx)
set(CONAN_SYSTEM_LIBS_LIBPQXX_RELEASE )
set(CONAN_FRAMEWORKS_LIBPQXX_RELEASE )
set(CONAN_FRAMEWORKS_FOUND_LIBPQXX_RELEASE "")  # Will be filled later
set(CONAN_DEFINES_LIBPQXX_RELEASE )
set(CONAN_BUILD_MODULES_PATHS_LIBPQXX_RELEASE )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBPQXX_RELEASE )

set(CONAN_C_FLAGS_LIBPQXX_RELEASE "")
set(CONAN_CXX_FLAGS_LIBPQXX_RELEASE "")
set(CONAN_SHARED_LINKER_FLAGS_LIBPQXX_RELEASE "")
set(CONAN_EXE_LINKER_FLAGS_LIBPQXX_RELEASE "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBPQXX_RELEASE_LIST "")
set(CONAN_CXX_FLAGS_LIBPQXX_RELEASE_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBPQXX_RELEASE_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBPQXX_RELEASE_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBPQXX_RELEASE "${CONAN_FRAMEWORKS_LIBPQXX_RELEASE}" "_LIBPQXX" "_RELEASE")
# Append to aggregated values variable
set(CONAN_LIBS_LIBPQXX_RELEASE ${CONAN_PKG_LIBS_LIBPQXX_RELEASE} ${CONAN_SYSTEM_LIBS_LIBPQXX_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBPQXX_RELEASE})


#################
###  ZLIB
#################
set(CONAN_ZLIB_ROOT_RELEASE "/home/nafan/.conan/data/zlib/1.3.1/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9")
set(CONAN_INCLUDE_DIRS_ZLIB_RELEASE "/home/nafan/.conan/data/zlib/1.3.1/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/include")
set(CONAN_LIB_DIRS_ZLIB_RELEASE "/home/nafan/.conan/data/zlib/1.3.1/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/lib")
set(CONAN_BIN_DIRS_ZLIB_RELEASE )
set(CONAN_RES_DIRS_ZLIB_RELEASE )
set(CONAN_SRC_DIRS_ZLIB_RELEASE )
set(CONAN_BUILD_DIRS_ZLIB_RELEASE "/home/nafan/.conan/data/zlib/1.3.1/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/")
set(CONAN_FRAMEWORK_DIRS_ZLIB_RELEASE )
set(CONAN_LIBS_ZLIB_RELEASE z)
set(CONAN_PKG_LIBS_ZLIB_RELEASE z)
set(CONAN_SYSTEM_LIBS_ZLIB_RELEASE )
set(CONAN_FRAMEWORKS_ZLIB_RELEASE )
set(CONAN_FRAMEWORKS_FOUND_ZLIB_RELEASE "")  # Will be filled later
set(CONAN_DEFINES_ZLIB_RELEASE )
set(CONAN_BUILD_MODULES_PATHS_ZLIB_RELEASE )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_ZLIB_RELEASE )

set(CONAN_C_FLAGS_ZLIB_RELEASE "")
set(CONAN_CXX_FLAGS_ZLIB_RELEASE "")
set(CONAN_SHARED_LINKER_FLAGS_ZLIB_RELEASE "")
set(CONAN_EXE_LINKER_FLAGS_ZLIB_RELEASE "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_ZLIB_RELEASE_LIST "")
set(CONAN_CXX_FLAGS_ZLIB_RELEASE_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_ZLIB_RELEASE_LIST "")
set(CONAN_EXE_LINKER_FLAGS_ZLIB_RELEASE_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_ZLIB_RELEASE "${CONAN_FRAMEWORKS_ZLIB_RELEASE}" "_ZLIB" "_RELEASE")
# Append to aggregated values variable
set(CONAN_LIBS_ZLIB_RELEASE ${CONAN_PKG_LIBS_ZLIB_RELEASE} ${CONAN_SYSTEM_LIBS_ZLIB_RELEASE} ${CONAN_FRAMEWORKS_FOUND_ZLIB_RELEASE})


#################
###  BZIP2
#################
set(CONAN_BZIP2_ROOT_RELEASE "/home/nafan/.conan/data/bzip2/1.0.8/_/_/package/d2b26eab5d737825f387165f3d8a52545f27d816")
set(CONAN_INCLUDE_DIRS_BZIP2_RELEASE "/home/nafan/.conan/data/bzip2/1.0.8/_/_/package/d2b26eab5d737825f387165f3d8a52545f27d816/include")
set(CONAN_LIB_DIRS_BZIP2_RELEASE "/home/nafan/.conan/data/bzip2/1.0.8/_/_/package/d2b26eab5d737825f387165f3d8a52545f27d816/lib")
set(CONAN_BIN_DIRS_BZIP2_RELEASE "/home/nafan/.conan/data/bzip2/1.0.8/_/_/package/d2b26eab5d737825f387165f3d8a52545f27d816/bin")
set(CONAN_RES_DIRS_BZIP2_RELEASE )
set(CONAN_SRC_DIRS_BZIP2_RELEASE )
set(CONAN_BUILD_DIRS_BZIP2_RELEASE "/home/nafan/.conan/data/bzip2/1.0.8/_/_/package/d2b26eab5d737825f387165f3d8a52545f27d816/")
set(CONAN_FRAMEWORK_DIRS_BZIP2_RELEASE )
set(CONAN_LIBS_BZIP2_RELEASE bz2)
set(CONAN_PKG_LIBS_BZIP2_RELEASE bz2)
set(CONAN_SYSTEM_LIBS_BZIP2_RELEASE )
set(CONAN_FRAMEWORKS_BZIP2_RELEASE )
set(CONAN_FRAMEWORKS_FOUND_BZIP2_RELEASE "")  # Will be filled later
set(CONAN_DEFINES_BZIP2_RELEASE )
set(CONAN_BUILD_MODULES_PATHS_BZIP2_RELEASE )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_BZIP2_RELEASE )

set(CONAN_C_FLAGS_BZIP2_RELEASE "")
set(CONAN_CXX_FLAGS_BZIP2_RELEASE "")
set(CONAN_SHARED_LINKER_FLAGS_BZIP2_RELEASE "")
set(CONAN_EXE_LINKER_FLAGS_BZIP2_RELEASE "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_BZIP2_RELEASE_LIST "")
set(CONAN_CXX_FLAGS_BZIP2_RELEASE_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_BZIP2_RELEASE_LIST "")
set(CONAN_EXE_LINKER_FLAGS_BZIP2_RELEASE_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_BZIP2_RELEASE "${CONAN_FRAMEWORKS_BZIP2_RELEASE}" "_BZIP2" "_RELEASE")
# Append to aggregated values variable
set(CONAN_LIBS_BZIP2_RELEASE ${CONAN_PKG_LIBS_BZIP2_RELEASE} ${CONAN_SYSTEM_LIBS_BZIP2_RELEASE} ${CONAN_FRAMEWORKS_FOUND_BZIP2_RELEASE})


#################
###  LIBBACKTRACE
#################
set(CONAN_LIBBACKTRACE_ROOT_RELEASE "/home/nafan/.conan/data/libbacktrace/cci.20210118/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9")
set(CONAN_INCLUDE_DIRS_LIBBACKTRACE_RELEASE "/home/nafan/.conan/data/libbacktrace/cci.20210118/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/include")
set(CONAN_LIB_DIRS_LIBBACKTRACE_RELEASE "/home/nafan/.conan/data/libbacktrace/cci.20210118/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/lib")
set(CONAN_BIN_DIRS_LIBBACKTRACE_RELEASE )
set(CONAN_RES_DIRS_LIBBACKTRACE_RELEASE )
set(CONAN_SRC_DIRS_LIBBACKTRACE_RELEASE )
set(CONAN_BUILD_DIRS_LIBBACKTRACE_RELEASE "/home/nafan/.conan/data/libbacktrace/cci.20210118/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/")
set(CONAN_FRAMEWORK_DIRS_LIBBACKTRACE_RELEASE )
set(CONAN_LIBS_LIBBACKTRACE_RELEASE backtrace)
set(CONAN_PKG_LIBS_LIBBACKTRACE_RELEASE backtrace)
set(CONAN_SYSTEM_LIBS_LIBBACKTRACE_RELEASE )
set(CONAN_FRAMEWORKS_LIBBACKTRACE_RELEASE )
set(CONAN_FRAMEWORKS_FOUND_LIBBACKTRACE_RELEASE "")  # Will be filled later
set(CONAN_DEFINES_LIBBACKTRACE_RELEASE )
set(CONAN_BUILD_MODULES_PATHS_LIBBACKTRACE_RELEASE )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBBACKTRACE_RELEASE )

set(CONAN_C_FLAGS_LIBBACKTRACE_RELEASE "")
set(CONAN_CXX_FLAGS_LIBBACKTRACE_RELEASE "")
set(CONAN_SHARED_LINKER_FLAGS_LIBBACKTRACE_RELEASE "")
set(CONAN_EXE_LINKER_FLAGS_LIBBACKTRACE_RELEASE "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBBACKTRACE_RELEASE_LIST "")
set(CONAN_CXX_FLAGS_LIBBACKTRACE_RELEASE_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBBACKTRACE_RELEASE_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBBACKTRACE_RELEASE_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBBACKTRACE_RELEASE "${CONAN_FRAMEWORKS_LIBBACKTRACE_RELEASE}" "_LIBBACKTRACE" "_RELEASE")
# Append to aggregated values variable
set(CONAN_LIBS_LIBBACKTRACE_RELEASE ${CONAN_PKG_LIBS_LIBBACKTRACE_RELEASE} ${CONAN_SYSTEM_LIBS_LIBBACKTRACE_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBBACKTRACE_RELEASE})


#################
###  LIBPQ
#################
set(CONAN_LIBPQ_ROOT_RELEASE "/home/nafan/.conan/data/libpq/15.4/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9")
set(CONAN_INCLUDE_DIRS_LIBPQ_RELEASE "/home/nafan/.conan/data/libpq/15.4/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/include")
set(CONAN_LIB_DIRS_LIBPQ_RELEASE "/home/nafan/.conan/data/libpq/15.4/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/lib")
set(CONAN_BIN_DIRS_LIBPQ_RELEASE "/home/nafan/.conan/data/libpq/15.4/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/bin")
set(CONAN_RES_DIRS_LIBPQ_RELEASE )
set(CONAN_SRC_DIRS_LIBPQ_RELEASE )
set(CONAN_BUILD_DIRS_LIBPQ_RELEASE )
set(CONAN_FRAMEWORK_DIRS_LIBPQ_RELEASE )
set(CONAN_LIBS_LIBPQ_RELEASE pq pgcommon pgcommon_shlib pgport pgport_shlib)
set(CONAN_PKG_LIBS_LIBPQ_RELEASE pq pgcommon pgcommon_shlib pgport pgport_shlib)
set(CONAN_SYSTEM_LIBS_LIBPQ_RELEASE pthread)
set(CONAN_FRAMEWORKS_LIBPQ_RELEASE )
set(CONAN_FRAMEWORKS_FOUND_LIBPQ_RELEASE "")  # Will be filled later
set(CONAN_DEFINES_LIBPQ_RELEASE )
set(CONAN_BUILD_MODULES_PATHS_LIBPQ_RELEASE )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBPQ_RELEASE )

set(CONAN_C_FLAGS_LIBPQ_RELEASE "")
set(CONAN_CXX_FLAGS_LIBPQ_RELEASE "")
set(CONAN_SHARED_LINKER_FLAGS_LIBPQ_RELEASE "")
set(CONAN_EXE_LINKER_FLAGS_LIBPQ_RELEASE "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBPQ_RELEASE_LIST "")
set(CONAN_CXX_FLAGS_LIBPQ_RELEASE_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBPQ_RELEASE_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBPQ_RELEASE_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBPQ_RELEASE "${CONAN_FRAMEWORKS_LIBPQ_RELEASE}" "_LIBPQ" "_RELEASE")
# Append to aggregated values variable
set(CONAN_LIBS_LIBPQ_RELEASE ${CONAN_PKG_LIBS_LIBPQ_RELEASE} ${CONAN_SYSTEM_LIBS_LIBPQ_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBPQ_RELEASE})


### Definition of global aggregated variables ###

set(CONAN_DEPENDENCIES_RELEASE boost catch2 libpqxx zlib bzip2 libbacktrace libpq)

set(CONAN_INCLUDE_DIRS_RELEASE "/home/nafan/.conan/data/boost/1.78.0/_/_/package/a0d4e1436288d5f00e9dfbffea6197064706982f/include"
			"/home/nafan/.conan/data/catch2/3.7.1/_/_/package/3a97d359160735989fa7e619b5fa4b8b4d45e216/include"
			"/home/nafan/.conan/data/libpqxx/7.7.5/_/_/package/84b287c7f4808a5e98be8eea8f4deb46aa14e092/include"
			"/home/nafan/.conan/data/zlib/1.3.1/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/include"
			"/home/nafan/.conan/data/bzip2/1.0.8/_/_/package/d2b26eab5d737825f387165f3d8a52545f27d816/include"
			"/home/nafan/.conan/data/libbacktrace/cci.20210118/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/include"
			"/home/nafan/.conan/data/libpq/15.4/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/include" ${CONAN_INCLUDE_DIRS_RELEASE})
set(CONAN_LIB_DIRS_RELEASE "/home/nafan/.conan/data/boost/1.78.0/_/_/package/a0d4e1436288d5f00e9dfbffea6197064706982f/lib"
			"/home/nafan/.conan/data/catch2/3.7.1/_/_/package/3a97d359160735989fa7e619b5fa4b8b4d45e216/lib"
			"/home/nafan/.conan/data/libpqxx/7.7.5/_/_/package/84b287c7f4808a5e98be8eea8f4deb46aa14e092/lib"
			"/home/nafan/.conan/data/zlib/1.3.1/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/lib"
			"/home/nafan/.conan/data/bzip2/1.0.8/_/_/package/d2b26eab5d737825f387165f3d8a52545f27d816/lib"
			"/home/nafan/.conan/data/libbacktrace/cci.20210118/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/lib"
			"/home/nafan/.conan/data/libpq/15.4/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/lib" ${CONAN_LIB_DIRS_RELEASE})
set(CONAN_BIN_DIRS_RELEASE "/home/nafan/.conan/data/bzip2/1.0.8/_/_/package/d2b26eab5d737825f387165f3d8a52545f27d816/bin"
			"/home/nafan/.conan/data/libpq/15.4/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/bin" ${CONAN_BIN_DIRS_RELEASE})
set(CONAN_RES_DIRS_RELEASE  ${CONAN_RES_DIRS_RELEASE})
set(CONAN_FRAMEWORK_DIRS_RELEASE  ${CONAN_FRAMEWORK_DIRS_RELEASE})
set(CONAN_LIBS_RELEASE boost_contract boost_coroutine boost_fiber_numa boost_fiber boost_context boost_graph boost_iostreams boost_json boost_locale boost_log_setup boost_log boost_math_c99 boost_math_c99f boost_math_c99l boost_math_tr1 boost_math_tr1f boost_math_tr1l boost_nowide boost_program_options boost_random boost_regex boost_stacktrace_addr2line boost_stacktrace_backtrace boost_stacktrace_basic boost_stacktrace_noop boost_timer boost_type_erasure boost_thread boost_chrono boost_container boost_date_time boost_unit_test_framework boost_prg_exec_monitor boost_test_exec_monitor boost_exception boost_wave boost_filesystem boost_atomic boost_wserialization boost_serialization Catch2Main Catch2 pqxx z bz2 backtrace pq pgcommon pgcommon_shlib pgport pgport_shlib ${CONAN_LIBS_RELEASE})
set(CONAN_PKG_LIBS_RELEASE boost_contract boost_coroutine boost_fiber_numa boost_fiber boost_context boost_graph boost_iostreams boost_json boost_locale boost_log_setup boost_log boost_math_c99 boost_math_c99f boost_math_c99l boost_math_tr1 boost_math_tr1f boost_math_tr1l boost_nowide boost_program_options boost_random boost_regex boost_stacktrace_addr2line boost_stacktrace_backtrace boost_stacktrace_basic boost_stacktrace_noop boost_timer boost_type_erasure boost_thread boost_chrono boost_container boost_date_time boost_unit_test_framework boost_prg_exec_monitor boost_test_exec_monitor boost_exception boost_wave boost_filesystem boost_atomic boost_wserialization boost_serialization Catch2Main Catch2 pqxx z bz2 backtrace pq pgcommon pgcommon_shlib pgport pgport_shlib ${CONAN_PKG_LIBS_RELEASE})
set(CONAN_SYSTEM_LIBS_RELEASE dl rt m pthread ${CONAN_SYSTEM_LIBS_RELEASE})
set(CONAN_FRAMEWORKS_RELEASE  ${CONAN_FRAMEWORKS_RELEASE})
set(CONAN_FRAMEWORKS_FOUND_RELEASE "")  # Will be filled later
set(CONAN_DEFINES_RELEASE "-DBOOST_STACKTRACE_ADDR2LINE_LOCATION=\"/usr/bin/addr2line\""
			"-DBOOST_STACKTRACE_USE_ADDR2LINE"
			"-DBOOST_STACKTRACE_USE_BACKTRACE"
			"-DBOOST_STACKTRACE_USE_NOOP" ${CONAN_DEFINES_RELEASE})
set(CONAN_BUILD_MODULES_PATHS_RELEASE  ${CONAN_BUILD_MODULES_PATHS_RELEASE})
set(CONAN_CMAKE_MODULE_PATH_RELEASE "/home/nafan/.conan/data/catch2/3.7.1/_/_/package/3a97d359160735989fa7e619b5fa4b8b4d45e216/lib/cmake/Catch2"
			"/home/nafan/.conan/data/zlib/1.3.1/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/"
			"/home/nafan/.conan/data/bzip2/1.0.8/_/_/package/d2b26eab5d737825f387165f3d8a52545f27d816/"
			"/home/nafan/.conan/data/libbacktrace/cci.20210118/_/_/package/c11224e931af7eb47df7c689b7ad7afc6b151bd9/" ${CONAN_CMAKE_MODULE_PATH_RELEASE})

set(CONAN_CXX_FLAGS_RELEASE " ${CONAN_CXX_FLAGS_RELEASE}")
set(CONAN_SHARED_LINKER_FLAGS_RELEASE " ${CONAN_SHARED_LINKER_FLAGS_RELEASE}")
set(CONAN_EXE_LINKER_FLAGS_RELEASE " ${CONAN_EXE_LINKER_FLAGS_RELEASE}")
set(CONAN_C_FLAGS_RELEASE " ${CONAN_C_FLAGS_RELEASE}")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_RELEASE "${CONAN_FRAMEWORKS_RELEASE}" "" "_RELEASE")
# Append to aggregated values variable: Use CONAN_LIBS instead of CONAN_PKG_LIBS to include user appended vars
set(CONAN_LIBS_RELEASE ${CONAN_LIBS_RELEASE} ${CONAN_SYSTEM_LIBS_RELEASE} ${CONAN_FRAMEWORKS_FOUND_RELEASE})
