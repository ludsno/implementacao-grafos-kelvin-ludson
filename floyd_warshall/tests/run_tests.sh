set -e

# Identifica a raiz do módulo (um nível acima deste script)
ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"

# Nome do binário
BIN="$ROOT_DIR/floyd_warshall.bin"

echo "Compilando o binário floyd_warshall..."
make -C "$ROOT_DIR"

echo
echo "Executando os testes..."
for inp in "$ROOT_DIR"/tests/in_out/inputs/*.in; do
    base=$(basename "$inp" .in)
    out_exp="$ROOT_DIR"/tests/in_out/outputs/"${base}".out
    out_act="$ROOT_DIR"/tests/in_out/outputs/"${base}".act

    # Executa o binário
    "$BIN" -f "$inp" > "$out_act"

    # Compara com o gabarito
    if diff -u "$out_exp" "$out_act" > /dev/null; then
        echo "$base: OK"
    else
        echo "$base: FALHA"
        echo "Diferenças:"
        diff -u "$out_exp" "$out_act"
        exit 1
    fi
done

echo
echo "Todos os testes passaram!"
