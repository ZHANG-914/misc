-- ==============================================================
-- RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
-- Version: 2018.3
-- Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
-- 
-- ===========================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Sobel is
port (
    ap_clk : IN STD_LOGIC;
    ap_rst : IN STD_LOGIC;
    ap_start : IN STD_LOGIC;
    ap_done : OUT STD_LOGIC;
    ap_continue : IN STD_LOGIC;
    ap_idle : OUT STD_LOGIC;
    ap_ready : OUT STD_LOGIC;
    p_src_rows_V_dout : IN STD_LOGIC_VECTOR (31 downto 0);
    p_src_rows_V_empty_n : IN STD_LOGIC;
    p_src_rows_V_read : OUT STD_LOGIC;
    p_src_cols_V_dout : IN STD_LOGIC_VECTOR (31 downto 0);
    p_src_cols_V_empty_n : IN STD_LOGIC;
    p_src_cols_V_read : OUT STD_LOGIC;
    p_src_data_stream_V_dout : IN STD_LOGIC_VECTOR (7 downto 0);
    p_src_data_stream_V_empty_n : IN STD_LOGIC;
    p_src_data_stream_V_read : OUT STD_LOGIC;
    p_dst_data_stream_V_din : OUT STD_LOGIC_VECTOR (7 downto 0);
    p_dst_data_stream_V_full_n : IN STD_LOGIC;
    p_dst_data_stream_V_write : OUT STD_LOGIC );
end;


architecture behav of Sobel is 
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_ST_fsm_state1 : STD_LOGIC_VECTOR (1 downto 0) := "01";
    constant ap_ST_fsm_state2 : STD_LOGIC_VECTOR (1 downto 0) := "10";
    constant ap_const_lv32_0 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    constant ap_const_lv32_1 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000001";
    constant ap_const_boolean_1 : BOOLEAN := true;

    signal ap_done_reg : STD_LOGIC := '0';
    signal ap_CS_fsm : STD_LOGIC_VECTOR (1 downto 0) := "01";
    attribute fsm_encoding : string;
    attribute fsm_encoding of ap_CS_fsm : signal is "none";
    signal ap_CS_fsm_state1 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state1 : signal is "none";
    signal p_src_rows_V_blk_n : STD_LOGIC;
    signal p_src_cols_V_blk_n : STD_LOGIC;
    signal p_src_rows_V_read_reg_92 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_block_state1 : BOOLEAN;
    signal p_src_cols_V_read_reg_97 : STD_LOGIC_VECTOR (31 downto 0);
    signal grp_Filter2D_fu_80_ap_start : STD_LOGIC;
    signal grp_Filter2D_fu_80_ap_done : STD_LOGIC;
    signal grp_Filter2D_fu_80_ap_idle : STD_LOGIC;
    signal grp_Filter2D_fu_80_ap_ready : STD_LOGIC;
    signal grp_Filter2D_fu_80_p_src_data_stream_V_read : STD_LOGIC;
    signal grp_Filter2D_fu_80_p_dst_data_stream_V_din : STD_LOGIC_VECTOR (7 downto 0);
    signal grp_Filter2D_fu_80_p_dst_data_stream_V_write : STD_LOGIC;
    signal grp_Filter2D_fu_80_ap_start_reg : STD_LOGIC := '0';
    signal ap_block_state1_ignore_call6 : BOOLEAN;
    signal ap_CS_fsm_state2 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state2 : signal is "none";
    signal ap_NS_fsm : STD_LOGIC_VECTOR (1 downto 0);

    component Filter2D IS
    port (
        ap_clk : IN STD_LOGIC;
        ap_rst : IN STD_LOGIC;
        ap_start : IN STD_LOGIC;
        ap_done : OUT STD_LOGIC;
        ap_idle : OUT STD_LOGIC;
        ap_ready : OUT STD_LOGIC;
        p_src_rows_V_read : IN STD_LOGIC_VECTOR (31 downto 0);
        p_src_cols_V_read : IN STD_LOGIC_VECTOR (31 downto 0);
        p_src_data_stream_V_dout : IN STD_LOGIC_VECTOR (7 downto 0);
        p_src_data_stream_V_empty_n : IN STD_LOGIC;
        p_src_data_stream_V_read : OUT STD_LOGIC;
        p_dst_data_stream_V_din : OUT STD_LOGIC_VECTOR (7 downto 0);
        p_dst_data_stream_V_full_n : IN STD_LOGIC;
        p_dst_data_stream_V_write : OUT STD_LOGIC );
    end component;



begin
    grp_Filter2D_fu_80 : component Filter2D
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst,
        ap_start => grp_Filter2D_fu_80_ap_start,
        ap_done => grp_Filter2D_fu_80_ap_done,
        ap_idle => grp_Filter2D_fu_80_ap_idle,
        ap_ready => grp_Filter2D_fu_80_ap_ready,
        p_src_rows_V_read => p_src_rows_V_read_reg_92,
        p_src_cols_V_read => p_src_cols_V_read_reg_97,
        p_src_data_stream_V_dout => p_src_data_stream_V_dout,
        p_src_data_stream_V_empty_n => p_src_data_stream_V_empty_n,
        p_src_data_stream_V_read => grp_Filter2D_fu_80_p_src_data_stream_V_read,
        p_dst_data_stream_V_din => grp_Filter2D_fu_80_p_dst_data_stream_V_din,
        p_dst_data_stream_V_full_n => p_dst_data_stream_V_full_n,
        p_dst_data_stream_V_write => grp_Filter2D_fu_80_p_dst_data_stream_V_write);





    ap_CS_fsm_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_CS_fsm <= ap_ST_fsm_state1;
            else
                ap_CS_fsm <= ap_NS_fsm;
            end if;
        end if;
    end process;


    ap_done_reg_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_done_reg <= ap_const_logic_0;
            else
                if ((ap_continue = ap_const_logic_1)) then 
                    ap_done_reg <= ap_const_logic_0;
                elsif (((grp_Filter2D_fu_80_ap_done = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then 
                    ap_done_reg <= ap_const_logic_1;
                end if; 
            end if;
        end if;
    end process;


    grp_Filter2D_fu_80_ap_start_reg_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                grp_Filter2D_fu_80_ap_start_reg <= ap_const_logic_0;
            else
                if ((not(((ap_start = ap_const_logic_0) or (p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
                    grp_Filter2D_fu_80_ap_start_reg <= ap_const_logic_1;
                elsif ((grp_Filter2D_fu_80_ap_ready = ap_const_logic_1)) then 
                    grp_Filter2D_fu_80_ap_start_reg <= ap_const_logic_0;
                end if; 
            end if;
        end if;
    end process;

    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((not(((ap_start = ap_const_logic_0) or (p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then
                p_src_cols_V_read_reg_97 <= p_src_cols_V_dout;
                p_src_rows_V_read_reg_92 <= p_src_rows_V_dout;
            end if;
        end if;
    end process;

    ap_NS_fsm_assign_proc : process (ap_start, ap_done_reg, ap_CS_fsm, ap_CS_fsm_state1, p_src_rows_V_empty_n, p_src_cols_V_empty_n, grp_Filter2D_fu_80_ap_done, ap_CS_fsm_state2)
    begin
        case ap_CS_fsm is
            when ap_ST_fsm_state1 => 
                if ((not(((ap_start = ap_const_logic_0) or (p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then
                    ap_NS_fsm <= ap_ST_fsm_state2;
                else
                    ap_NS_fsm <= ap_ST_fsm_state1;
                end if;
            when ap_ST_fsm_state2 => 
                if (((grp_Filter2D_fu_80_ap_done = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then
                    ap_NS_fsm <= ap_ST_fsm_state1;
                else
                    ap_NS_fsm <= ap_ST_fsm_state2;
                end if;
            when others =>  
                ap_NS_fsm <= "XX";
        end case;
    end process;
    ap_CS_fsm_state1 <= ap_CS_fsm(0);
    ap_CS_fsm_state2 <= ap_CS_fsm(1);

    ap_block_state1_assign_proc : process(ap_start, ap_done_reg, p_src_rows_V_empty_n, p_src_cols_V_empty_n)
    begin
                ap_block_state1 <= ((ap_start = ap_const_logic_0) or (p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1));
    end process;


    ap_block_state1_ignore_call6_assign_proc : process(ap_start, ap_done_reg, p_src_rows_V_empty_n, p_src_cols_V_empty_n)
    begin
                ap_block_state1_ignore_call6 <= ((ap_start = ap_const_logic_0) or (p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1));
    end process;


    ap_done_assign_proc : process(ap_done_reg, grp_Filter2D_fu_80_ap_done, ap_CS_fsm_state2)
    begin
        if (((grp_Filter2D_fu_80_ap_done = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then 
            ap_done <= ap_const_logic_1;
        else 
            ap_done <= ap_done_reg;
        end if; 
    end process;


    ap_idle_assign_proc : process(ap_start, ap_CS_fsm_state1)
    begin
        if (((ap_start = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            ap_idle <= ap_const_logic_1;
        else 
            ap_idle <= ap_const_logic_0;
        end if; 
    end process;


    ap_ready_assign_proc : process(grp_Filter2D_fu_80_ap_done, ap_CS_fsm_state2)
    begin
        if (((grp_Filter2D_fu_80_ap_done = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then 
            ap_ready <= ap_const_logic_1;
        else 
            ap_ready <= ap_const_logic_0;
        end if; 
    end process;

    grp_Filter2D_fu_80_ap_start <= grp_Filter2D_fu_80_ap_start_reg;
    p_dst_data_stream_V_din <= grp_Filter2D_fu_80_p_dst_data_stream_V_din;

    p_dst_data_stream_V_write_assign_proc : process(grp_Filter2D_fu_80_p_dst_data_stream_V_write, ap_CS_fsm_state2)
    begin
        if ((ap_const_logic_1 = ap_CS_fsm_state2)) then 
            p_dst_data_stream_V_write <= grp_Filter2D_fu_80_p_dst_data_stream_V_write;
        else 
            p_dst_data_stream_V_write <= ap_const_logic_0;
        end if; 
    end process;


    p_src_cols_V_blk_n_assign_proc : process(ap_start, ap_done_reg, ap_CS_fsm_state1, p_src_cols_V_empty_n)
    begin
        if ((not(((ap_start = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            p_src_cols_V_blk_n <= p_src_cols_V_empty_n;
        else 
            p_src_cols_V_blk_n <= ap_const_logic_1;
        end if; 
    end process;


    p_src_cols_V_read_assign_proc : process(ap_start, ap_done_reg, ap_CS_fsm_state1, p_src_rows_V_empty_n, p_src_cols_V_empty_n)
    begin
        if ((not(((ap_start = ap_const_logic_0) or (p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            p_src_cols_V_read <= ap_const_logic_1;
        else 
            p_src_cols_V_read <= ap_const_logic_0;
        end if; 
    end process;


    p_src_data_stream_V_read_assign_proc : process(grp_Filter2D_fu_80_p_src_data_stream_V_read, ap_CS_fsm_state2)
    begin
        if ((ap_const_logic_1 = ap_CS_fsm_state2)) then 
            p_src_data_stream_V_read <= grp_Filter2D_fu_80_p_src_data_stream_V_read;
        else 
            p_src_data_stream_V_read <= ap_const_logic_0;
        end if; 
    end process;


    p_src_rows_V_blk_n_assign_proc : process(ap_start, ap_done_reg, ap_CS_fsm_state1, p_src_rows_V_empty_n)
    begin
        if ((not(((ap_start = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            p_src_rows_V_blk_n <= p_src_rows_V_empty_n;
        else 
            p_src_rows_V_blk_n <= ap_const_logic_1;
        end if; 
    end process;


    p_src_rows_V_read_assign_proc : process(ap_start, ap_done_reg, ap_CS_fsm_state1, p_src_rows_V_empty_n, p_src_cols_V_empty_n)
    begin
        if ((not(((ap_start = ap_const_logic_0) or (p_src_cols_V_empty_n = ap_const_logic_0) or (p_src_rows_V_empty_n = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1))) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            p_src_rows_V_read <= ap_const_logic_1;
        else 
            p_src_rows_V_read <= ap_const_logic_0;
        end if; 
    end process;

end behav;
