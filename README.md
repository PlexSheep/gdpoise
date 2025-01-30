# gdpoise

## Tired of GDB Debugging Your ELF Binaries? Meet **gdpoise**! 🛡️

Ever wanted to modify an ELF binary’s header to prevent GDB from debugging it, while still keeping the binary functional? No? Well, now you can! Introducing **gdpoise** — a simple tool to help you do exactly that.

### What does **gdpoise** do?

**gdpoise** modifies the ELF binary's header by overwriting key fields:  
- Section number  
- Section offset  
- String entries in the header table  

This effectively prevents GDB from debugging the binary by making it "unrecognizable" to the debugger, while maintaining the functionality of the binary itself. 

### A word of caution

While this tool is effective against GDB, it's worth noting that other debuggers might use automated scripts to restore the binary, so this technique won't guarantee protection in every case.

### Disclaimer

- **I am not liable** for any damage or unintended consequences resulting from the use of this tool.
- **No guarantees** of flawless functionality — use at your own risk!

