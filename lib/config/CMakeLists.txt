# Add include path for 'lang.tab.hh'
include_directories(${CONFIG_LANG_OUTPUT_DIR})

set_source_files_properties(${CONFIG_LANG_OUTPUT_DIR}/lang.yy.c GENERATED PROPERTIES LANGUAGE CXX)
set_source_files_properties(${CONFIG_LANG_OUTPUT_DIR}/lang.tab.cc GENERATED)

add_library(config STATIC config_loader.cc
                          config_map.cc
                          config_map_builder.cc
                          constant.cc
                          tuple_parser.cc
                          ${CONFIG_LANG_OUTPUT_DIR}/lang.yy.c
                          ${CONFIG_LANG_OUTPUT_DIR}/lang.tab.cc)

add_dependencies(config FlexLexerSources
                        BisonParserSources)
