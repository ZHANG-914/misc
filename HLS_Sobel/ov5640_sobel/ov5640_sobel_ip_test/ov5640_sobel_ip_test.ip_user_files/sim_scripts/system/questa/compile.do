vlib questa_lib/work
vlib questa_lib/msim

vlib questa_lib/msim/xilinx_vip
vlib questa_lib/msim/xil_defaultlib
vlib questa_lib/msim/xpm
vlib questa_lib/msim/axi_infrastructure_v1_1_0
vlib questa_lib/msim/axi_vip_v1_1_4
vlib questa_lib/msim/processing_system7_vip_v1_0_6
vlib questa_lib/msim/lib_cdc_v1_0_2
vlib questa_lib/msim/lib_pkg_v1_0_2
vlib questa_lib/msim/fifo_generator_v13_2_3
vlib questa_lib/msim/lib_fifo_v1_0_12
vlib questa_lib/msim/blk_mem_gen_v8_4_2
vlib questa_lib/msim/lib_bmg_v1_0_11
vlib questa_lib/msim/lib_srl_fifo_v1_0_2
vlib questa_lib/msim/axi_datamover_v5_1_20
vlib questa_lib/msim/axi_vdma_v6_3_6
vlib questa_lib/msim/axi_lite_ipif_v3_0_4
vlib questa_lib/msim/v_tc_v6_1_13
vlib questa_lib/msim/v_vid_in_axi4s_v4_0_9
vlib questa_lib/msim/v_axi4s_vid_out_v4_0_10
vlib questa_lib/msim/interrupt_control_v3_1_4
vlib questa_lib/msim/axi_gpio_v2_0_20
vlib questa_lib/msim/xlconstant_v1_1_5
vlib questa_lib/msim/proc_sys_reset_v5_0_13
vlib questa_lib/msim/smartconnect_v1_0
vlib questa_lib/msim/generic_baseblocks_v2_1_0
vlib questa_lib/msim/axi_register_slice_v2_1_18
vlib questa_lib/msim/axi_data_fifo_v2_1_17
vlib questa_lib/msim/axi_crossbar_v2_1_19
vlib questa_lib/msim/axi_protocol_converter_v2_1_18

vmap xilinx_vip questa_lib/msim/xilinx_vip
vmap xil_defaultlib questa_lib/msim/xil_defaultlib
vmap xpm questa_lib/msim/xpm
vmap axi_infrastructure_v1_1_0 questa_lib/msim/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_4 questa_lib/msim/axi_vip_v1_1_4
vmap processing_system7_vip_v1_0_6 questa_lib/msim/processing_system7_vip_v1_0_6
vmap lib_cdc_v1_0_2 questa_lib/msim/lib_cdc_v1_0_2
vmap lib_pkg_v1_0_2 questa_lib/msim/lib_pkg_v1_0_2
vmap fifo_generator_v13_2_3 questa_lib/msim/fifo_generator_v13_2_3
vmap lib_fifo_v1_0_12 questa_lib/msim/lib_fifo_v1_0_12
vmap blk_mem_gen_v8_4_2 questa_lib/msim/blk_mem_gen_v8_4_2
vmap lib_bmg_v1_0_11 questa_lib/msim/lib_bmg_v1_0_11
vmap lib_srl_fifo_v1_0_2 questa_lib/msim/lib_srl_fifo_v1_0_2
vmap axi_datamover_v5_1_20 questa_lib/msim/axi_datamover_v5_1_20
vmap axi_vdma_v6_3_6 questa_lib/msim/axi_vdma_v6_3_6
vmap axi_lite_ipif_v3_0_4 questa_lib/msim/axi_lite_ipif_v3_0_4
vmap v_tc_v6_1_13 questa_lib/msim/v_tc_v6_1_13
vmap v_vid_in_axi4s_v4_0_9 questa_lib/msim/v_vid_in_axi4s_v4_0_9
vmap v_axi4s_vid_out_v4_0_10 questa_lib/msim/v_axi4s_vid_out_v4_0_10
vmap interrupt_control_v3_1_4 questa_lib/msim/interrupt_control_v3_1_4
vmap axi_gpio_v2_0_20 questa_lib/msim/axi_gpio_v2_0_20
vmap xlconstant_v1_1_5 questa_lib/msim/xlconstant_v1_1_5
vmap proc_sys_reset_v5_0_13 questa_lib/msim/proc_sys_reset_v5_0_13
vmap smartconnect_v1_0 questa_lib/msim/smartconnect_v1_0
vmap generic_baseblocks_v2_1_0 questa_lib/msim/generic_baseblocks_v2_1_0
vmap axi_register_slice_v2_1_18 questa_lib/msim/axi_register_slice_v2_1_18
vmap axi_data_fifo_v2_1_17 questa_lib/msim/axi_data_fifo_v2_1_17
vmap axi_crossbar_v2_1_19 questa_lib/msim/axi_crossbar_v2_1_19
vmap axi_protocol_converter_v2_1_18 questa_lib/msim/axi_protocol_converter_v2_1_18

vlog -work xilinx_vip -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"D:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"D:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"D:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"D:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"D:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"D:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"D:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_if.sv" \
"D:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/clk_vip_if.sv" \
"D:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xil_defaultlib -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"D:/Xilinx/Vivado/2018.3/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"D:/Xilinx/Vivado/2018.3/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"D:/Xilinx/Vivado/2018.3/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -64 -93 \
"D:/Xilinx/Vivado/2018.3/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work axi_infrastructure_v1_1_0 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_4 -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/98af/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_6 -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_processing_system7_0_0/sim/system_processing_system7_0_0.v" \

vcom -work lib_cdc_v1_0_2 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work lib_pkg_v1_0_2 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \

vlog -work fifo_generator_v13_2_3 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/64f4/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_3 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/64f4/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_3 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/64f4/hdl/fifo_generator_v13_2_rfs.v" \

vcom -work lib_fifo_v1_0_12 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/544a/hdl/lib_fifo_v1_0_rfs.vhd" \

vlog -work blk_mem_gen_v8_4_2 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/37c2/simulation/blk_mem_gen_v8_4.v" \

vcom -work lib_bmg_v1_0_11 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/556c/hdl/lib_bmg_v1_0_rfs.vhd" \

vcom -work lib_srl_fifo_v1_0_2 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \

vcom -work axi_datamover_v5_1_20 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/dfb3/hdl/axi_datamover_v5_1_vh_rfs.vhd" \

vlog -work axi_vdma_v6_3_6 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl/axi_vdma_v6_3_rfs.v" \

vcom -work axi_vdma_v6_3_6 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl/axi_vdma_v6_3_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/system/ip/system_axi_vdma_0_0/sim/system_axi_vdma_0_0.vhd" \

vcom -work axi_lite_ipif_v3_0_4 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work v_tc_v6_1_13 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/a92c/hdl/v_tc_v6_1_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/system/ip/system_v_tc_0_0/sim/system_v_tc_0_0.vhd" \

vlog -work v_vid_in_axi4s_v4_0_9 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2aa/hdl/v_vid_in_axi4s_v4_0_vl_rfs.v" \

vlog -work v_axi4s_vid_out_v4_0_10 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/a87e/hdl/v_axi4s_vid_out_v4_0_vl_rfs.v" \

vlog -work xil_defaultlib -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_v_axi4s_vid_out_0_0/sim/system_v_axi4s_vid_out_0_0.v" \
"../../../bd/system/ipshared/0c63/src/rgb2lcd.v" \
"../../../bd/system/ip/system_rgb2lcd_0_0/sim/system_rgb2lcd_0_0.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ab26/src/mmcme2_drp.v" \

vcom -work xil_defaultlib -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ab26/src/axi_dynclk_S00_AXI.vhd" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ab26/src/axi_dynclk.vhd" \
"../../../bd/system/ip/system_axi_dynclk_0_0/sim/system_axi_dynclk_0_0.vhd" \

vcom -work interrupt_control_v3_1_4 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_20 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/a7c9/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/system/ip/system_axi_gpio_0_0/sim/system_axi_gpio_0_0.vhd" \

vlog -work xil_defaultlib -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/sim/bd_44e3.v" \

vlog -work xlconstant_v1_1_5 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/4649/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_0/sim/bd_44e3_one_0.v" \

vcom -work proc_sys_reset_v5_0_13 -64 -93 \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_1/sim/bd_44e3_psr_aclk_0.vhd" \

vlog -work smartconnect_v1_0 -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/sc_util_v1_0_vl_rfs.sv" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/c012/hdl/sc_switchboard_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_2/sim/bd_44e3_arsw_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_3/sim/bd_44e3_rsw_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_4/sim/bd_44e3_awsw_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_5/sim/bd_44e3_wsw_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_6/sim/bd_44e3_bsw_0.sv" \

vlog -work smartconnect_v1_0 -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/f85e/hdl/sc_mmu_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_7/sim/bd_44e3_s00mmu_0.sv" \

vlog -work smartconnect_v1_0 -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ca72/hdl/sc_transaction_regulator_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_8/sim/bd_44e3_s00tr_0.sv" \

vlog -work smartconnect_v1_0 -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/9ade/hdl/sc_si_converter_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_9/sim/bd_44e3_s00sic_0.sv" \

vlog -work smartconnect_v1_0 -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b89e/hdl/sc_axi2sc_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_10/sim/bd_44e3_s00a2s_0.sv" \

vlog -work smartconnect_v1_0 -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/sc_node_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_11/sim/bd_44e3_sarn_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_12/sim/bd_44e3_srn_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_13/sim/bd_44e3_s01mmu_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_14/sim/bd_44e3_s01tr_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_15/sim/bd_44e3_s01sic_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_16/sim/bd_44e3_s01a2s_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_17/sim/bd_44e3_sawn_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_18/sim/bd_44e3_swn_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_19/sim/bd_44e3_sbn_0.sv" \

vlog -work smartconnect_v1_0 -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/7005/hdl/sc_sc2axi_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_20/sim/bd_44e3_m00s2a_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_21/sim/bd_44e3_m00arn_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_22/sim/bd_44e3_m00rn_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_23/sim/bd_44e3_m00awn_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_24/sim/bd_44e3_m00wn_0.sv" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_25/sim/bd_44e3_m00bn_0.sv" \

vlog -work smartconnect_v1_0 -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b387/hdl/sc_exit_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_26/sim/bd_44e3_m00e_0.sv" \

vlog -work xil_defaultlib -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_axi_smc_0/sim/system_axi_smc_0.v" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/system/ip/system_rst_ps7_0_100M_0/sim/system_rst_ps7_0_100M_0.vhd" \

vlog -work generic_baseblocks_v2_1_0 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_18 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/cc23/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work axi_data_fifo_v2_1_17 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/c4fd/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_19 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/6c9d/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_xbar_0/sim/system_xbar_0.v" \
"../../../bd/system/sim/system.v" \
"../../../bd/system/ip/system_v_vid_in_axi4s_0_0/sim/system_v_vid_in_axi4s_0_0.v" \
"../../../bd/system/ipshared/8797/src/ov5640_capture_data.v" \
"../../../bd/system/ip/system_ov5640_capture_data_0_0/sim/system_ov5640_capture_data_0_0.v" \

vlog -work axi_protocol_converter_v2_1_18 -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/7a04/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib -64 "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/70cf/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/58e2/hdl" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/979d/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b2d0/hdl/verilog" "+incdir+../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ip/system_processing_system7_0_0" "+incdir+D:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"../../../bd/system/ip/system_auto_pc_0/sim/system_auto_pc_0.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/AXIvideo2Mat.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/Block_Mat_exit49_pro.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/CvtColor.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/CvtColor_1.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/fifo_w8_d2_A.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/fifo_w32_d2_A.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/fifo_w32_d4_A.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/fifo_w32_d5_A.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/fifo_w32_d6_A.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/Filter2D.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/Filter2D_k_buf_0_eOg.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/Mat2AXIvideo.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/ov5640_sobel_AXILiteS_s_axi.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/ov5640_sobel_mac_cud.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/ov5640_sobel_mac_dEe.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/ov5640_sobel_mul_bkb.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/ov5640_sobel_mux_hbi.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/Sobel.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/start_for_CvtColoibs.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/start_for_CvtColokbM.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/start_for_Mat2AXIjbC.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/start_for_Sobel_U0.v" \
"../../../../ov5640_sobel_ip_test.srcs/sources_1/bd/system/ipshared/b7bc/hdl/verilog/ov5640_sobel.v" \
"../../../bd/system/ip/system_ov5640_sobel_0_0/sim/system_ov5640_sobel_0_0.v" \

vlog -work xil_defaultlib \
"glbl.v"

