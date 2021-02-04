cmake_minimum_required(VERSION 3.17)
project(NotepadAnimator)

set(CMAKE_CXX_STANDARD 20)

add_executable(NotepadAnimator main.cpp NotepadController.cpp NotepadController.hpp MainWindowFinder.hpp StringHelper.hpp DirectoryHelper.cpp DirectoryHelper.hpp FfmpegHelper.cpp FfmpegHelper.hpp FrameConverter.cpp FrameConverter.hpp)