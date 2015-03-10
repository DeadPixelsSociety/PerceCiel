include_directories(${SFML2_INCLUDEDIR})
include_directories(${LIBTMX_INCLUDEDIR})
include_directories(${BOX2D_INCLUDEDIR})

add_executable(PerceCiel
  main.cc
)

link_directories(${SFML2_LIBDIR})

target_link_libraries(PerceCiel
  ${SFML2_LIBRARIES}
  ${Boost_LIBRARIES}
  ${LIBTMX_LIBRARIES}
  ${BOX2D_LIBRARIES}
)
