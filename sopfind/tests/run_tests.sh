#!/bin/sh

set -eu

BIN="./sopfind"

# test tree setup

rm -rf tests/data
mkdir -p tests/data/sub

printf "hello\n" > tests/data/a.txt
printf "int main{}{}\n" > tests/data/b.c
printf "world\n" > tests/data/sub/c.txt

# make big file

dd if=/dev/zero of=tests/data/sub/big.bin bs=2048 count=1 >/dev/null 2>&1

touch -d "2 days ago" tests/data/a.txt || true

echo "[TEST] --help exists and prints usage"
$BIN --help | grep -Fq "Usage:"

echo "[TEST] -p traversal prints something under tests/data"
OUT="$($BIN -p tests/data)"
echo "$OUT" | grep -Fq "tests/data"

echo "[TEST] -name uses fnmatch on name"
$BIN -p tests/data -name "*.c" | grep -q "b.c"

echo "[TEST] -type d returns subdir but not a.txt"
OUT="$($BIN -p tests/data -type d)"
echo "$OUT" | grep -Fq "sub"
echo "$OUT" | grep -Fq "a.txt" && exit 1 || true

echo "[TEST] -size +1000 finds big.bin"
$BIN -p tests/data -size +1000 | grep -q "big.bin"

echo "[TEST] Combined filters work"
OUT="$($BIN -p tests/data -name "*.c" -type f)"
echo "$OUT" | grep -Fq "b.c"
echo "$OUT" | grep -Fq "a.txt" && exit 1 || true

echo "[TEST] --stdin processes multiple paths"
OUT="$(printf "tests/data\ntests/data/sub\n" | $BIN --stdin)"
echo "$OUT" | grep -Fq "a.txt"
echo "$OUT" | grep -Fq "c.txt"

echo "[TEST] stdin + filters applies filters to each processed path"
OUT="$(printf "tests/data\ntests/data/sub\n" | $BIN --stdin -name "*.txt")"
echo "$OUT" | grep -Fq "a.txt"
echo "$OUT" | grep -Fq "c.txt"
if echo "$OUT" | grep -Fq "b.c"; then
	echo "DEBUG OUT:"
	echo "$OUT"
	echo "ERROR: b.c should not be in output"
	exit 1
fi

echo "All tests passed."





