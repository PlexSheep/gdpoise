# gdpoise

Have you ever wanted to modify the header of an ELF binary to make prohibit gdb from debugging it while still keeping the binary functional? No??
Well now you can.. introducing: **gdpoise**

This small tool modifies the Header of a given file by overwriting the section number, section offset and strings defined in the header table.
This results in gdb not being able to debug the modified binary. 

There are other debuggers out there that have automated scripts to restore the binary, so this may not work in every case.

I am not liable for what you do with this tool and I don't guarantee that it works flawlessly without bugs.
