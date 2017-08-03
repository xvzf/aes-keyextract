cmake_minimum_required(VERSION 2.8)

set(keyextract_src src)
include_directories(inc)

set(KEYEXTRACT_SRCS ${keyextract_src}/iops.c
                    ${keyextract_src}/keyerror.c
                    ${keyextract_src}/keyextract.c
                    ${keyextract_src}/keysearch.c
                    ${keyextract_src}/main_keyextract.c)


set(HDD_DECRYPT_SRCS ${keyextract_src}/main_hdddecrypt.c
                ${keyextract_src}/iops.c)


set(CORRECT_MEMORY_SRCS ${keyextract_src}/main_correct_memory.c
                     ${keyextract_src}/iops.c)


add_executable(keyextract ${KEYEXTRACT_SRCS})
target_link_libraries(keyextract)

add_executable(hdddecrypt ${HDD_DECRYPT_SRCS})
target_link_libraries(hdddecrypt)

add_executable(correctmemory ${CORRECT_MEMORY_SRCS})
target_link_libraries(correctmemory)
