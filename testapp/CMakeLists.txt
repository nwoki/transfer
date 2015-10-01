set(testapp_SRCS
    commanddispatcher.cpp
    main.cpp
)

add_executable(testApp ${testapp_SRCS})

qt5_use_modules(testApp Core Network)


