set -e

# Identifica a raiz do módulo (um nível acima deste script)
ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"

# Nome do binário
BIN="$ROOT_DIR/floyd_warshall.bin"

echo "Compilando o binário floyd_warshall..."
make -C "$ROOT_DIR"

# Bloco para testes em 'testes floyd'
echo
echo "Executando os testes em 'testes floyd'..."
for inp in "$ROOT_DIR"/tests/"testes floyd"/input/*.txt; do
    base=$(basename "$inp" .txt)
    out_exp="$ROOT_DIR"/tests/"testes floyd"/output/"${base}".txt
    out_act="$ROOT_DIR"/tests/"testes floyd"/output/"${base}".txt

    "$BIN" -f "$inp" > "$out_act"

    if diff -u "$out_exp" "$out_act" > /dev/null; then
        echo "${base}: OK"
    else
        echo "${base}: FALHA"
        echo "Diferenças:"
        diff -u "$out_exp" "$out_act"
        exit 1
    fi
done

echo
echo "Todos os testes passaram!"
