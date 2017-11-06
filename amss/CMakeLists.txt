cmake_minimum_required(VERSION 3.8)
project(amss)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        camera/CameraReader.cpp
        camera/CameraReader.h
        camera/DotRecognizer.cpp
        camera/DotRecognizer.h
        camera/ImageSender.cpp
        camera/ImageSender.h
        camera/LineRecognizer.cpp
        camera/LineRecognizer.h
        camera/SignRecognizer.cpp
        camera/SignRecognizer.h
        common/CameraImageRepo.cpp
        common/CameraImageRepo.h
        common/MapRepo.cpp
        common/MapRepo.h
        common/SensorDataRepo.cpp
        common/SensorDataRepo.h
        main/AutonomousMode.cpp
        main/AutonomousMode.h
        main/CCommandHandler.cpp
        main/CCommandHandler.h
        main/Initializer.cpp
        main/Initializer.h
        main/MainController.cpp
        main/MainController.h
        main/ManualMode.cpp
        main/ManualMode.h
        main/ModeBase.cpp
        main/ModeBase.h
        main/ModeManager.cpp
        main/ModeManager.h
        main/SuspendMode.cpp
        main/SuspendMode.h
        network/NetworkManager.cpp
        network/NetworkManager.h
        network/TCPSocket.cpp
        network/TCPSocket.h
        network/UDPSocket.cpp
        network/UDPSocket.h
        sam/MazeMapper.cpp
        sam/MazeMapper.h
        sam/PathPlanner.cpp
        sam/PathPlanner.h
        sam/WallRecognizer.cpp
        sam/WallRecognizer.h
        sensorreadloop/README.md
        servoencoder/CBehaviorExecutor.cpp
        servoencoder/CBehaviorExecutor.h
        servoencoder/CServoEncoder.cpp
        servoencoder/CServoEncoder.h)

# add extra include directories
include_directories(/amss)

add_executable(amss ${SOURCE_FILES})
