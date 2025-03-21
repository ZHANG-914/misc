############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project ov5640_sobel
set_top ov5640_sobel
add_files ov5640_sobel/src/ov5640_sobel.h
add_files ov5640_sobel/src/ov5640_sobel.cpp
add_files -tb ov5640_sobel/src/ov5640_sobel_tb.cpp -cflags "-Wno-unknown-pragmas"
add_files -tb ov5640_sobel/src/lena.jpg -cflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 20 -name default
config_export -format ip_catalog -rtl verilog
#source "./ov5640_sobel/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
