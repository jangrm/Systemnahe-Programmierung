#!/bin/sh

set -eu

BIN="${BIN:-./sopfind}"

fail() { echo "ERROR: $*" >&2; exit 1; }

cleanup(){
  rm -f err.txt out.txt
}
trap cleanup EXIT

echo "[ERRORTEST] -p without argument returns exit code 2 and prints error"
set +e
$BIN -p 1>/dev/null 2>err.txt
rc=$?
set -e

if [ "$rc" -eq 2 ]; then 
	echo "passed"
else
	fail "expected exit 2, got $rc"
fi

grep -Fiq "missing argument" err.txt || fail "stderr should mention missing argument"

echo "[ERRORTEST] --stdin with empty input produces no output and exits"
printf "" | $BIN --stdin >out.txt 2>/dev/null
if [ ! -s out.txt ]; then
       echo "passed"
else
       fail "expected empty stdout for empty stdin"	
fi

echo "[ERRORTEST] --stdin ignores empty lines"
printf "\n\n" | $BIN --stdin >out.txt 2>/dev/null
if [ ! -s out.txt ]; then
       echo "passed"
else
       fail "expected empty stdout when stdin hat only empty lines"
fi       

echo "[ERRORTEST] directory without permission does not hang"
rm -rf tests/errdata
mkdir -p tests/errdata/noperm
printf "x\n" > tests/errdata/noperm/x.txt
chmod 000 tests/errdata/noperm 2>/dev/null || true

set +e
timeout 3 $BIN -p tests/errdata 1>/dev/null 2>/dev/null
rc=$?
set -e

if [ "$rc" -ne 124 ]; then
       echo "passed"
else
       fail "program hung on unreadable directory"
fi       

#cleanup permission

chmod 755 tests/errdata/noperm 2>/dev/null || true
rm -rf tests/errdata

echo "All error tests passed."





