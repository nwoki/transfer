set(transfer_SRCS
    dialogs/settingsdialog.cpp
    connectioncenter.cpp
#     core.cpp
    dbhandler.cpp
    discoverer.cpp
    main.cpp
    parser.cpp
    settings.cpp
    systray.cpp
    user.cpp
    userlist.cpp
)


## final application

# for defines/consts aux stuff
# configure_file(aux_config.h.in ${CMAKE_SOURCE_DIR}/generated/aux_config.h)

qt5_wrap_ui(transfer_UIS
    dialogs/settingsdialog.ui
)

qt5_add_resources(transfer_QRCS
    ../images.qrc
    ../qml.qrc
)

add_executable(transfer ${transfer_SRCS} ${transfer_UIS} ${transfer_QRCS})

qt5_use_modules(transfer Core Gui Widgets Qml Quick Sql)


