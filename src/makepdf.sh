INPUT_FILE="$1"

if [ ! -f "$INPUT_FILE" ]; then
    echo "Plik '$INPUT_FILE' nie znaleziono."
    exit 1
fi
pdflatex -interaction=nonstopmode -jobname="$INPUT_FILE" "$INPUT_FILE" >/dev/null 2>&1

if [ -f "${INPUT_FILE}.pdf" ]; then
    echo "Plik został utworzony: ${INPUT_FILE}.pdf"
    rm -f "${INPUT_FILE}.aux" "${INPUT_FILE}.log" "${INPUT_FILE}.out" "${INPUT_FILE}.toc" "${INPUT_FILE}.synctex.gz"
else
    echo "Nie udało się wygenerować pdf"
    exit 1
fi