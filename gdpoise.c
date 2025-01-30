#include <elf.h>
#include <stdio.h>

int read_elf(char *filename) {
  FILE *fptr;
  fptr = fopen(filename, "rb");

  if (!fptr) {
    printf("Error opening file %s\n", filename);
  }

  // Load ELF header struct
  Elf64_Ehdr hdr;
  size_t header_size = sizeof(Elf64_Ehdr);

  if (fread(&hdr, header_size, 1, fptr) != 1) {
    printf("Error reading ELF Header of file %s\n", filename);
  }
  // Check if File is type ELF by examining magic values
  if (hdr.e_ident[EI_MAG0] != ELFMAG0 || hdr.e_ident[EI_MAG1] != ELFMAG1 ||
      hdr.e_ident[EI_MAG2] != ELFMAG2 || hdr.e_ident[EI_MAG3] != ELFMAG3) {
    printf("Error, %s is not format ELF. Closing..\n", filename);
    fclose(fptr);
    return -1;
  }
  fclose(fptr);
  return -1;
}
int main(int argc, char *argv[]) { read_elf(argv[1]); }
