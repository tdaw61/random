library verilog;
use verilog.vl_types.all;
entity fetch is
    port(
        Addr            : out    vl_logic_vector(7 downto 0);
        clock           : in     vl_logic;
        reset           : in     vl_logic;
        PCSrc           : in     vl_logic;
        q               : out    vl_logic_vector(31 downto 0)
    );
end fetch;
