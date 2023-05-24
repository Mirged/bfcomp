#include <stdio.h>
#include <stdlib.h>

void generate_c_code(const char* source_code, FILE* file);

void compile_brainfuck_to_c(const char* source_code, const char* output_file) {
	const char* c_file = "output.c";
    FILE* file = fopen(output_file, "w");
    if (!file) {
        printf("Error: Failed to open output file.\n");
        return;
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
    sprintf(compile_command, "cc -o %s %s", output_file, c_file);
    int result = system(compile_command);
    if (result == 0) {
        printf("Executable file '%s' generated.\n", output_file);
    } else {
        printf("Error: Compilation failed.\n");
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
        printf("Error: Mismatched brackets in Brainfuck code.\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) { // TODO: Add argument to compile braifuck code without saving C code
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    const char* input_file = argv[1];
    const char* output_file = argv[2];

    FILE* file = fopen(input_file, "r");
    if (!file) {
        printf("Error: Failed to open input file.\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* source_code = (char*)malloc(file_size + 1);
    if (!source_code) {
        printf("Error: Failed to allocate memory.\n");
        fclose(file);
        return 1;
    }

    size_t bytes_read = fread(source_code, 1, file_size, file);
    if (bytes_read != file_size) {
        printf("Error: Failed to read input file.\n");
        fclose(file);
        free(source_code);
        return 1;
    }

    source_code[file_size] = '\0';
    fclose(file);

    compile_brainfuck_to_c(source_code, output_file);

    free(source_code);

    return 0;
}
