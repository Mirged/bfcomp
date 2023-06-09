#include <stdio.h>
#include <stdlib.h>

void generate_c_code(const char* source_code, FILE* file);

void compile_brainfuck_to_c(const char* source_code, const char* executable_file, const char* output_file) {
    FILE* file = fopen(output_file, "w");
    if (!file) {
        fprintf(stderr, "Error: Failed to open output file.\n");
        exit(1);
    }

    fprintf(file, "#include <stdio.h>\n\n");
    fprintf(file, "int main() {\n");
    fprintf(file, "    unsigned char array[30000] = {0};\n");
    fprintf(file, "    unsigned char* ptr = array;\n\n");

    generate_c_code(source_code, file);

    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");

    fclose(file);

    // Compile the C code using the system's C compiler (GCC or Clang)
    char compile_command[256];
    sprintf(compile_command, "cc -o %s %s", executable_file, output_file);
    int result = system(compile_command);
    if (result == 0) {
        printf("Executable file '%s' generated.\n", executable_file);
    } else {
        fprintf(stderr, "Error: Compilation failed.\n");
        exit(1);
    }
}

void generate_c_code(const char* source_code, FILE* file) {
    int indent = 1;

    for (const char* c = source_code; *c; ++c) {
        switch (*c) {
            case '>':
                fprintf(file, "%*s++ptr;\n", indent * 4, "");
                break;
            case '<':
                fprintf(file, "%*s--ptr;\n", indent * 4, "");
                break;
            case '+':
                fprintf(file, "%*s++(*ptr);\n", indent * 4, "");
                break;
            case '-':
                fprintf(file, "%*s--(*ptr);\n", indent * 4, "");
                break;
            case '.':
                fprintf(file, "%*sputchar(*ptr);\n", indent * 4, "");
                break;
            case ',':
                fprintf(file, "%*s*ptr = getchar();\n", indent * 4, "");
                break;
            case '[':
                fprintf(file, "%*swhile (*ptr) {\n", indent * 4, "");
                ++indent;
                break;
            case ']':
                fprintf(file, "%*s}\n", (indent - 1) * 4, "");
                --indent;
                break;
        }
    }

    if (indent != 1) {
        fprintf(stderr, "Error: Mismatched brackets in Brainfuck code.\n");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(1);
    }

    const char* input_file = argv[1];
    const char* output_file = argv[2];

    FILE* file = fopen(input_file, "r");
    if (!file) {
        fprintf(stderr, "Error: Failed to open input file.\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* source_code = (char*)malloc(file_size + 1);
    if (!source_code) {
        fprintf(stderr, "Error: Failed to allocate memory.\n");
        fclose(file);
        exit(1);
    }

    size_t bytes_read = fread(source_code, 1, file_size, file);
    if (bytes_read != file_size) {
        fprintf(stderr, "Error: Failed to read input file.\n");
        fclose(file);
        free(source_code);
        exit(1);
    }

    source_code[file_size] = '\0';
    fclose(file);

    const char* executable_file = output_file;

    char c_file[256];
    sprintf(c_file, "%s.c", output_file);

    compile_brainfuck_to_c(source_code, executable_file, c_file);

    free(source_code);

    return 0;
}
