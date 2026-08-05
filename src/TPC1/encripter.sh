#!/bin/bash
#author Tomás Alves 68681 e Luis Martins 68473

if [ "$#" -lt 2 ]; then
    echo "Uso: $0 <diretoria> <seed>"
    exit 1
fi

diretoria=$1
seed=$2

run_directory() {
    find "$diretoria" -type f ! -name "*.encrypted" | while read -r arquivo; do
        nome_saida="$arquivo.encrypted"
        ./encript "$arquivo" "$nome_saida" "$seed"
    done
}

run_directory       

