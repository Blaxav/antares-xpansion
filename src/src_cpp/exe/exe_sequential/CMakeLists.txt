# ===========================================================================
# CMake configuration
# ===========================================================================

# ===========================================================================
# Targets
# ===========================================================================

# ---------------------------------------------------------------------------
# Sequential Benders Exe
# ---------------------------------------------------------------------------

add_executable (benderssequential
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries (benderssequential ${PROJECT_NAME}::sequentialcore)

install(TARGETS benderssequential DESTINATION bin)