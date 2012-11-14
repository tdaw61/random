library verilog;
use verilog.vl_types.all;
entity Project1 is
    port(
        a               : out    vl_logic_vector(4 downto 0);
        clock           : in     vl_logic;
        reset           : in     vl_logic;
        btype           : in     vl_logic_vector(1 downto 0);
        b               : out    vl_logic_vector(4 downto 0);
        c               : out    vl_logic_vector(4 downto 0);
        Instr           : out    vl_logic_vector(31 downto 0);
        PC              : out    vl_logic_vector(7 downto 0);
        read2           : out    vl_logic_vector(7 downto 0);
        result          : out    vl_logic_vector(7 downto 0);
        truncate        : out    vl_logic_vector(7 downto 0)
    );
end Project1;
