library verilog;
use verilog.vl_types.all;
entity Project1 is
    port(
        memwr           : out    vl_logic;
        clock           : in     vl_logic;
        reset           : in     vl_logic;
        memtoreg        : out    vl_logic;
        alusrc          : out    vl_logic;
        regdst          : out    vl_logic;
        regwr           : out    vl_logic;
        \out\           : out    vl_logic;
        a               : out    vl_logic_vector(4 downto 0);
        Addr            : out    vl_logic_vector(7 downto 0);
        aluop           : out    vl_logic_vector(2 downto 0);
        b               : out    vl_logic_vector(4 downto 0);
        btype           : out    vl_logic_vector(1 downto 0);
        c               : out    vl_logic_vector(4 downto 0);
        d               : out    vl_logic_vector(15 downto 0);
        func            : out    vl_logic_vector(5 downto 0);
        op              : out    vl_logic_vector(5 downto 0);
        q               : out    vl_logic_vector(31 downto 0);
        read1           : out    vl_logic_vector(7 downto 0);
        read2           : out    vl_logic_vector(7 downto 0);
        result          : out    vl_logic_vector(7 downto 0);
        rshift          : out    vl_logic_vector(7 downto 0);
        sol             : out    vl_logic_vector(7 downto 0);
        truncate        : out    vl_logic_vector(7 downto 0)
    );
end Project1;
