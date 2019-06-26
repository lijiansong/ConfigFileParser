# Add incldue path for 'lang.tab.hh'
include_directories(${CONFIG_LANG_OUTPUT_DIR})

add_executable(config-parser config-parser.cc)
target_link_libraries(config-parser util
                                    config)
