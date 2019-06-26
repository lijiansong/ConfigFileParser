# bison version 2.7 or higher
find_package(BISON 2.7 REQUIRED)
# flex version 2.5 or higher
find_package(FLEX 2.5 REQUIRED)

add_custom_target(FlexLexerSources echo "Generating lang.yy.c"
                  DEPENDS LangOutputDirectory)

add_custom_command(TARGET FlexLexerSources
                   COMMAND flex
                   ARGS --outfile=${CONFIG_LANG_OUTPUT_DIR}/lang.yy.c
                        ${CMAKE_CURRENT_SOURCE_DIR}/lang.ll
                   DEPENDS lang.ll)

add_custom_target(BisonParserSources echo "Generating lang.tab.cc lang.tab.hh"
                  DEPENDS LangOutputDirectory)

add_custom_command(TARGET BisonParserSources
                   COMMAND bison
                   ARGS --output=${CONFIG_LANG_OUTPUT_DIR}/lang.tab.cc
                   --defines=${CONFIG_LANG_OUTPUT_DIR}/lang.tab.hh
                        ${CMAKE_CURRENT_SOURCE_DIR}/lang.yy
                   DEPENDS lang.yy)
