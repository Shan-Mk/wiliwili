# Download precompiled dylib dependencies
# arm64: 11.0
# x86_64: 10.11
# universal: arm64 + x86_64

# header files: `brew tap xfangfang/wiliwili && brew install mpv-wiliwili webp boost`

if (APPLE)

    if (MAC_IntelChip)
        set(MAC_OS_ARCH x86_64)
    elseif (MAC_AppleSilicon)
        set(MAC_OS_ARCH arm64)
    elseif (MAC_Universal)
        set(MAC_OS_ARCH universal)
    endif ()

    if (MAC_DOWNLOAD_DYLIB)
        set(APP_PLATFORM_LIB
                ${CMAKE_BINARY_DIR}/deps/${MAC_OS_ARCH}/libmpv.2.dylib
                ${CMAKE_BINARY_DIR}/deps/${MAC_OS_ARCH}/libwebp.7.1.6.dylib
                ${CMAKE_BINARY_DIR}/deps/${MAC_OS_ARCH}/libboost_filesystem-mt.dylib)

        # download deps
        add_custom_target(
                ${PROJECT_NAME}.macos_${MAC_OS_ARCH}_deps
                COMMAND "bash" "${CMAKE_BINARY_DIR}/../scripts/macos_dylib_downloader.sh" "${MAC_OS_ARCH}"
        )
        add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}.macos_${MAC_OS_ARCH}_deps)
        set(MACOS_DYLIB_DIR "${CMAKE_BINARY_DIR}/deps/${MAC_OS_ARCH}")
    endif ()
endif ()