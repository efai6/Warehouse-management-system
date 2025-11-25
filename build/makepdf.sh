
FILENAME="$1"
pdflatex -interaction=nonstopmode "${FILENAME}" >/dev/null 2>&1
echo "PDF created: ${FILENAME}.pdf"
