/*
                  Linker File for Renesas FSP
*/

/* Memory allocation example using ddr. */
BOOTPARAM_START         = 0x00022D00;
BOOTPARAM_LENGTH        = 0x00000300;

VECTBL_S_START          = 0x00023000;
VECTBL_S_LENGTH         = 0x00000800;
SRAM_S_START            = 0x00023880;
SRAM_S_LENGTH           = 0x0003C780;

VECTBL_N_START          = 0x10023800;
VECTBL_N_LENGTH         = 0x00000040;
SRAM_N_START            = 0x10023840;
SRAM_N_LENGTH           = 0x00000040;

NS_OFFSET_ADDRESS       = 0x10000000;
VECTBL_N_START_LMA      = VECTBL_N_START - NS_OFFSET_ADDRESS;
SRAM_N_START_LMA        = SRAM_N_START - NS_OFFSET_ADDRESS;


DDR_S_START             = 0x60010000;
DDR_S_LENGTH            = 0x03EF0000;
DDR_N_START             = 0x70010000;
DDR_N_LENGTH            = 0x03EF0000;

OPENAMP_RSCTBL_START    = 0x72F00000;
OPENAMP_RSCTBL_LENGTH   = 0x00001000;
MHU_SHMEM_START         = 0x72F01000;
MHU_SHMEM_LENGTH        = 0x00001000;
OPENAMP_VRING_START     = 0x73000000;
OPENAMP_VRING_LENGTH    = 0x00800000;


/* When using OpenAMP, allocate the length of the OpenAMP relevant region. */
OPENAMP_RSCTBL_START    = DEFINED(OPENAMP_RSCTBL_START) ? OPENAMP_RSCTBL_START  : 0;
OPENAMP_RSCTBL_LENGTH   = DEFINED(OPENAMP_RSCTBL_LENGTH)? OPENAMP_RSCTBL_LENGTH : 0;
MHU_SHMEM_START         = DEFINED(MHU_SHMEM_START)      ?      MHU_SHMEM_START  : 0;
MHU_SHMEM_LENGTH        = DEFINED(MHU_SHMEM_LENGTH)     ?      MHU_SHMEM_LENGTH : 0;
OPENAMP_VRING_START     = DEFINED(OPENAMP_VRING_START)  ?  OPENAMP_VRING_START  : 0;
OPENAMP_VRING_LENGTH    = DEFINED(OPENAMP_VRING_LENGTH) ?  OPENAMP_VRING_LENGTH : 0;
/* Define memory regions. */
MEMORY
{
  DDR_S (rwx)       : ORIGIN = DDR_S_START,         LENGTH = DDR_S_LENGTH
  DDR_N (rwx)       : ORIGIN = DDR_N_START,         LENGTH = DDR_N_LENGTH
  BOOTPARAM (rx)    : ORIGIN = BOOTPARAM_START,     LENGTH = BOOTPARAM_LENGTH
  VECTTBL_S (rx)    : ORIGIN = VECTBL_S_START,      LENGTH = VECTBL_S_LENGTH
  SRAM_S (rwx)      : ORIGIN = SRAM_S_START,        LENGTH = SRAM_S_LENGTH
  VECTTBL_N (rx)    : ORIGIN = VECTBL_N_START,      LENGTH = VECTBL_N_LENGTH
  SRAM_N (rwx)      : ORIGIN = SRAM_N_START,        LENGTH = SRAM_N_LENGTH
  OPENAMP_RSCTBL(rw): ORIGIN = OPENAMP_RSCTBL_START,LENGTH = OPENAMP_RSCTBL_LENGTH
  MHU_SHMEM(rw)     : ORIGIN = MHU_SHMEM_START,     LENGTH = MHU_SHMEM_LENGTH
  OPENAMP_VRING(rw) : ORIGIN = OPENAMP_VRING_START, LENGTH = OPENAMP_VRING_LENGTH
}

/* Library configurations */
GROUP(libgcc.a libc.a libm.a libnosys.a)

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions CODE, RAM and etc.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler_S : Entry of secure reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __Vectors_End
 *   __Vectors_Size
 */
ENTRY(Entry_Function_S)
SECTIONS
{

    .rodata.bootparam :
    {
        _BOOTPARAM_Start = .;
        LONG(__RAM_segment_used_end__ - _XSPI_Boot_Entry); /* Program size (copysize) */
        FILL(0xFFFFFFFF);
        . += 0xC;
        LONG(_XSPI_Boot_Entry - _BOOTPARAM_Start);         /* Program offset from top of BOOTPARAM
                                                            * copyfrom address = "this value" + 0x20000000
                                                            */
        FILL(0xFFFFFFFF);
        . += 0xC;
        LONG(_XSPI_Boot_Entry + 0x20000000);               /* Entry function address (Load address of XSPI)
                                                            * copyto address = "this value" - 0x20000000
                                                            */
        FILL(0xFFFFFFFF);
        . += 0x1DA;
        SHORT(0xAA55);                                     /* Signature of bootparam */

        _XSPI_Boot_Entry = .;
        KEEP(*(.text.XSPI_Boot_Entry))
    } > BOOTPARAM

    __tz_VECTBL_S = ABSOLUTE(VECTBL_S_START);
    . = __tz_VECTBL_S;

    .text.secure_vector :
    {
        /* Even though the vector table is not 16 entries (64B) long, we still allocate that much space. */
        KEEP(*(.fixed_secure_vectors*))
        KEEP(*(.application_vectors*))
        __Vectors_End = .;
    } >VECTTBL_S
    __tz_CODE_S = .;

    .text.secure_code :
    {
        *\bsp_security.o (.text)
        *\bsp_security.o (.text.*)
        *\bsp_security.o (.rodata)
        *\bsp_security.o (.rodata.*)
        *\bsp_irqs.o (.text)
        *\bsp_irqs.o (.text.*)
        *\bsp_irqs.o (.rodata)
        *\bsp_irqs.o (.rodata.*)
        *\startups.o (.text)
        *\startups.o (.text.*)
        *\startups.o (.rodata)
        *\startups.o (.rodata.*)
        *\systems.o (.text)
        *\systems.o (.text.*)
        *\systems.o (.rodata)
        *\systems.o (.rodata.*)

        __CODE_S_End = .;
    } >SRAM_S

    __tz_RAM_S = .;

    /* secure stacks are stored in this section. */
    .stack_dummy (NOLOAD) :
    {
        __S_StackLimit = .;
        /* secure main stack */
        KEEP(*(.s_stack))
        __S_StackTop = .;
    } >SRAM_S
    __tz_VECTBL_N =.;
    /* start at address VECTBL_N_START */
    .text.non_secure_vector : AT (VECTBL_N_START_LMA)
    {
        /* Even though the vector table is not 512 entries (2KB) long, we still allocate that much space. */
        KEEP(*(.fixed_vectors*))
    } >VECTTBL_N

    __Vectors_Size = __Vectors_End - __Secure_Vectors;

    /* start at address CODE_N_START */
    .text.secure_code :
    {
        *(.text*)
        KEEP(*(.version))
        KEEP(*(.init))
        KEEP(*(.fini))
        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(* crtend?.o * crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)
        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(* crtend?.o * crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)
        *(.rodata*)
        KEEP(*(.eh_frame*))
    } >SRAM_S

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > SRAM_S
    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > SRAM_S
    __exidx_end = .;
    /* To copy multiple CODE_N to DDR_N sections,
     * uncomment .copy.table section and,
     * define __STARTUP_COPY_MULTIPLE in startup_ARMCMx.S */
    /*
     * .copy.table :
     * {
     *     . = ALIGN(4);
     *     __copy_table_start__ = .;
     *     LONG (__etext)
     *     LONG (__data_start__)
     *     LONG (__data_end__ - __data_start__)
     *     LONG (__etext2)
     *     LONG (__data2_start__)
     *     LONG (__data2_end__ - __data2_start__)
     *     __copy_table_end__ = .;
     * } > CODE_N
     */
    /* To clear multiple BSS sections,
     * uncomment .zero.table section and,
     * define __STARTUP_CLEAR_BSS_MULTIPLE in startup_ARMCMx.S */
    /*
     * .zero.table :
     * {
     *     . = ALIGN(4);
     *     __zero_table_start__ = .;
     *     LONG (__bss_start__)
     *     LONG (__bss_end__ - __bss_start__)
     *     LONG (__bss2_start__)
     *     LONG (__bss2_end__ - __bss2_start__)
     *     __zero_table_end__ = .;
     * } > CODE_N
     */
    /* Initialized data section. */
    __etext = .;
    __tz_RAM_N = .;
    .data :
    {
        __data_start__ = .;
        . = ALIGN(4);
        __Code_In_RAM_Start = .;
        KEEP(*(.code_in_ram*))
        __Code_In_RAM_End = .;
        *(vtable)
        /* Don't use *(.data*) because it will place data meant for .data_flash in this section. */
        *(.data.*)
        *(.data)
        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN(__preinit_array_end = .);
        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN(__init_array_end = .);
        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN(__fini_array_end = .);
        KEEP(*(.jcr*))
        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;
    } > SRAM_S
    .bss.noinit (NOLOAD) :
    {
        . = ALIGN(4);
        __noinit_start = .;
        KEEP(*(.noinit*))
        . = ALIGN(8);
        /* Place the FreeRTOS heap here so that the __HeapLimit calculation does not include the freertos heap. */
        KEEP(*(.heap.*))
        __noinit_end = .;
    }  > SRAM_S
    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    }  > SRAM_S
    .heap (NOLOAD) :
    {
        . = ALIGN(8);
        __HeapBase = .;
        /* Place the STD heap here. */
        KEEP(*(.heap))
        __HeapLimit = .;
    }  > SRAM_S
    /* Stacks are stored in this section. */
    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        __StackLimit = .;
        /* Main stack */
        KEEP(*(.stack))
        __StackTop = .;
        /* Thread stacks */
        KEEP(*(.stack*))
        __StackTopAll = .;
    }  > SRAM_S
    PROVIDE(__stack = __StackTopAll);
    /* This symbol represents the end of user allocated RAM. The RAM after this symbol can be used
     at run time for things such as ThreadX memory pool allocations. */
    __RAM_segment_used_end__ = ALIGN(__StackTopAll , 4);

    PROVIDE(__tz_RAM_C = __RAM_segment_used_end__);

    __tz_OPENAMP_RSCTBL = ABSOLUTE(OPENAMP_RSCTBL_START);
    . = __tz_OPENAMP_RSCTBL;

    /* OpenAMP resource table */
    .bss.resource_table (NOLOAD) :
    {
        PROVIDE(__rsctbl_start = .);
        *(.resource_table)
        PROVIDE(__rsctbl_end = .);
    } > OPENAMP_RSCTBL

    __tz_MHU_SHMEM = ABSOLUTE(MHU_SHMEM_START);
    . = __tz_MHU_SHMEM;

    /* MHU driver shared memory */
    .bss.mhu_shmem (NOLOAD) :
    {
        PROVIDE(__mhu_shmem_start = .);
        . += MHU_SHMEM_LENGTH;
        PROVIDE(__mhu_shmem_end = .);
    } > MHU_SHMEM

    __tz_OPENAMP_VRING = ABSOLUTE(OPENAMP_VRING_START);
    . = __tz_OPENAMP_VRING;

    /* OpenAMP VRINGresource table */
    .bss.vring (NOLOAD) :
    {
        PROVIDE(__vring_start = .);
        . += OPENAMP_VRING_LENGTH;
        PROVIDE(__vring_end = .);
    } > OPENAMP_VRING

    .text.non_secure_code : AT (SRAM_N_START_LMA)
    {
        *(.non_secure*)
    } >SRAM_N

}
