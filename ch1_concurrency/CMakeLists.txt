project(ch1_concurrency)

include_directories(src)
aux_source_directory(. SRC_LIST)

add_executable(ch1_concurrency ${SRC_LIST})