# c++ompact

## Building the Project

Create a directory named `build` (if it doesn’t already exist) and navigate into it:

```bash
mkdir -p build
cd build
```

Generate the necessary build files using CMake:

```bash
cmake ..
```

Compile the project using `make`:

```bash
make
```

This will produce the executable file (`cppompact` or `cppompact.exe` on Windows) in the `build` directory.

## Running the Project with Command-Line Arguments

Ensure you are in the `build` directory:

```bash
cd build
```

### Encoding a File

To encode a file, use the following command:

```bash
./cppompact --encode ../input/input.txt ../output/encoded.bin
```

This command reads the `input.txt` file from the `input` directory and saves the encoded data as `encoded.bin` in the `output` directory.

### Decoding a File

To decode a previously encoded file, use:

```bash
./cppompact --decode ../output/encoded.bin ../output/decoded.txt
```

This command reads the `encoded.bin` file from the `output` directory and saves the decoded text as `decoded.txt` in the same directory.

### Displaying Help Information

To display usage information and available options, use:

```bash
./cppompact --help
```

## Handling Windows Builds

If you are on Windows, use the `.exe` extension for the executable.

Run the following commands in the `build` directory:

```bash
cmake ..
make
```

Use the `.exe` extension when running the executable:

```bash
cppompact.exe --encode ..\input\input.txt ..\output\encoded.bin
```

## Troubleshooting

### CMake Configuration Issues

If you see an error like `CMakeLists.txt not found`, make sure you are in the `build` directory and run `cmake ..` from there.

### Google Test Submodule Issues

If using Google Test and it’s not initialised, run the following commands:

```bash
git submodule update --init --recursive
```

### File Not Found Errors

If you encounter "file not found" errors, ensure that the input files exist and that the paths are correct relative to your current working directory.

## Running Tests

These commands will run all test cases and provide a detailed report of the results.

```bash
make cppompact_tests
```

```bash
./cppompact_tests
```

### Additional Information

1. **Command-Line Argument Descriptions:**
   - **`--encode` or `-e`:** Specifies the encoding mode. Requires input and output file paths.
   - **`--decode` or `-d`:** Specifies the decoding mode. Requires input and output file paths.
   - **`--help` or `-h`:** Displays the help message.

2. **File Path Adjustments:**
   - Ensure that the input files (`input/input.txt`) and output directories exist and have the correct relative paths based on your current working directory.
