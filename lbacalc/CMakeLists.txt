
set(LBACALC_SOURCES
    src/main.c
    src/fileutil.c
)

add_executable(lbacalc ${LBACALC_SOURCES})
target_include_directories(lbacalc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/common/inc
)

target_link_libraries(lbacalc img4dc-common)
