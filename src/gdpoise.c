#include <elf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_elf(char *filename) {
  FILE *fptr = fopen(filename, "rb");
  if (!fptr) {
    printf("Error opening file %s\n", filename);
    return -1;
  }

  // Load ELF header struct
  Elf64_Ehdr hdr;
  size_t header_size = sizeof(Elf64_Ehdr);

  if (fread(&hdr, header_size, 1, fptr) != 1) {
    printf("Error reading ELF Header of file %s\n", filename);
    fclose(fptr);
    return -1;
  }

  // Check if File is type ELF by examining magic values
  if (hdr.e_ident[EI_MAG0] != ELFMAG0 || hdr.e_ident[EI_MAG1] != ELFMAG1 ||
      hdr.e_ident[EI_MAG2] != ELFMAG2 || hdr.e_ident[EI_MAG3] != ELFMAG3) {
    printf("Error, %s is not an ELF file. Closing..\n", filename);
    fclose(fptr);
    return -1;
  }

  printf("\nELF Header Information:\n");
  printf("------------------------\n");
  printf("Number of sections in header:      %d\n", hdr.e_shnum);
  printf("Start of section header:      %ld\n", hdr.e_shoff);
  printf("Location of Strings defined in header table: %ld\n", hdr.e_shstrndx);

  fclose(fptr);
  return 0;
}

int write_elf(char *input_file, char *output_file, uint16_t new_shnum,
              uint16_t new_shoff, uint16_t new_shstrndx) {
  FILE *infile = fopen(input_file, "rb");
  if (!infile) {
    printf("Error while reading file %s\n", input_file);
    return -1;
  }

  // Get the size of the input file
  fseek(infile, 0, SEEK_END);
  long file_size = ftell(infile);
  fseek(infile, 0, SEEK_SET);

  // Allocate memory to read the entire ELF file
  unsigned char *file_data = (unsigned char *)malloc(file_size);
  if (!file_data) {
    printf("Error allocating memory for file data\n");
    fclose(infile);
    return -1;
  }

  // Read the entire file into memory
  if (fread(file_data, 1, file_size, infile) != file_size) {
    printf("Error reading the entire file %s\n", input_file);
    free(file_data);
    fclose(infile);
    return -1;
  }

  fclose(infile);

  // Load ELF header struct from the file data
  Elf64_Ehdr *hdr = (Elf64_Ehdr *)file_data;

  // Check if the file is ELF
  if (hdr->e_ident[EI_MAG0] != ELFMAG0 || hdr->e_ident[EI_MAG1] != ELFMAG1 ||
      hdr->e_ident[EI_MAG2] != ELFMAG2 || hdr->e_ident[EI_MAG3] != ELFMAG3) {
    printf("Error, %s is not an ELF file. Closing..\n", input_file);
    free(file_data);
    return -1;
  }

  // Modify the ELF header
  hdr->e_shnum = new_shnum;
  hdr->e_shoff = new_shoff;
  hdr->e_shstrndx = new_shstrndx;

  // Open the output file for writing
  FILE *outfile = fopen(output_file, "wb");
  if (!outfile) {
    printf("Error while creating outfile %s\n", output_file);
    free(file_data);
    return -1;
  }

  // Write the entire modified file data (header + sections) to the output file
  if (fwrite(file_data, 1, file_size, outfile) != file_size) {
    printf("Error writing the modified data to output file %s\n", output_file);
    free(file_data);
    fclose(outfile);
    return -1;
  }

  fclose(outfile);
  free(file_data);
  return 0;
}
int main(int argc, char *argv[]) {
  char *name = argv[1];
  if (strcmp(name, "-h") == 0) {
    printf("----------------------------------------\n");
    printf("Usage: gdpoise <name or path for binary>\n");
    printf("----------------------------------------\n");

    return 0;
  }
  if (argc > 2) {
    printf("Error, too many arguments provided\n");
  }

  read_elf(argv[1]);

  char output_file[256];
  snprintf(output_file, sizeof(output_file), "%s_modified", argv[1]);

  uint16_t shnum = 0xffff;

  uint16_t shoff = 0xffff;

  uint16_t shstrndx = 0xffff;

  write_elf(argv[1], output_file, shnum, shoff, shstrndx);
}
