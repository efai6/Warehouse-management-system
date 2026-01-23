INPUT_FILE="$1"

if [ ! -f "$INPUT_FILE" ]; then
    echo "Plik '$INPUT_FILE' nie znaleziono."
    exit 1
fi
if [ -f "${INPUT_FILE}.pdf" ]; then
    rm -f "${INPUT_FILE}.pdf"
    if [ -f "$FILE_PDF" ]; then
        echo "Warning: Unable to delete an old report file"
        echo "Maybe the file is open in viewing program. Close it and retry again"
        exit 1
    fi
fi
pdflatex -interaction=nonstopmode -jobname="$INPUT_FILE" "$INPUT_FILE" >/dev/null 2>&1
pdflatex -interaction=nonstopmode -jobname="$INPUT_FILE" "$INPUT_FILE" >/dev/null 2>&1
if [ -f "${INPUT_FILE}.pdf" ]; then
    echo "File was created: ${INPUT_FILE}.pdf"
    rm -f "${INPUT_FILE}.aux" "${INPUT_FILE}.out" "${INPUT_FILE}.toc" "${INPUT_FILE}.synctex.gz"
else
    echo "Error: the report file was not created"
    exit 1  
fi