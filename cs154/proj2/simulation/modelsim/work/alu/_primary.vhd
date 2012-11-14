library verilog;
use verilog.vl_types.all;
entity alu is
    port(
        read1           : in     vl_logic_vector(7 downto 0);
        read2           : in     vl_logic_vector(7 downto 0);
        control         : in     vl_logic_vector(2 downto 0);
        result          : out    vl_logic_vector(7 downto 0);
        zero            : out    vl_logic
    );
end alu;
