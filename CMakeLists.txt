# CMakeLists.txt

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(pwm_stm32f103)

zephyr_include_directories(include)
target_sources(app PRIVATE src/main.c src/heartbeat.c)

## Create and install git pre-commit script that gets the current hash of the zephyr repo at the time
## when this project was last built so that future-me can reference when this code fails to build in
## in the future, given the current somewhat rapid change to Zephyr API's.

function(install_git_hook HOOK_NAME HOOK_CONTENT)
    set(HOOK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.git/hooks")
    set(HOOK_PATH "${HOOK_DIR}/${HOOK_NAME}")
    
    file(WRITE "${HOOK_PATH}" "${HOOK_CONTENT}")
    execute_process(COMMAND chmod +x "${HOOK_PATH}")
endfunction()

set(PRE_COMMIT_SCRIPT 
"#!/bin/bash
export ZEPHYR_BASE=${ZEPHYR_BASE}

if [ -z \"\$ZEPHYR_BASE\" ]; then
    echo \"Warning: ZEPHYR_BASE not set - skipping Zephyr commit hash\"
    exit 0
fi

cd \"\$ZEPHYR_BASE\"
ZEPHYR_HASH=\$(git rev-parse HEAD)

cd - > /dev/null

# Save hash to file
echo \"\$ZEPHYR_HASH\" > ZEPHYR_COMMIT_HASH.txt
git add ZEPHYR_COMMIT_HASH.txt
")

install_git_hook("pre-commit" "${PRE_COMMIT_SCRIPT}")