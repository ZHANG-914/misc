# ==============================================================
# File generated on Tue Apr 25 15:26:10 +0800 2023
# Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
# SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
# IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
# Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
# ==============================================================
add_files -tb ../src/ov5640_sobel_tb.cpp -cflags { -Wno-unknown-pragmas}
add_files -tb ../src/lena.jpg -cflags { -Wno-unknown-pragmas}
add_files ov5640_sobel/src/ov5640_sobel.h
add_files ov5640_sobel/src/ov5640_sobel.cpp
set_part xc7z010clg400-1
create_clock -name default -period 20
