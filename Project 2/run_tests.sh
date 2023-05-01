NONE='\033[00m'
RED='\033[01;31m'
GREEN='\033[01;32m'
YELLOW='\033[01;33m'
PURPLE='\033[01;35m'
CYAN='\033[01;36m'
WHITE='\033[01;37m'
BOLD='\033[1m'
UNDERLINE='\033[4m'


compare=$1
detail=$2
valgrind=$3

echo -e "\n----------${BOLD}${YELLOW}Compiling Files${NONE}----------"
make
echo -e "\n----------${BOLD}${WHITE}Running Tests${NONE}----------"
for file in test_input/*; do
    if [ -f "$file" ]; then
        filename=$(basename -- "$file")
        filename="${filename%.*}"
        ./a.out < test_input/${filename}.in > test_output/${filename}.out
        if [[ -n "$valgrind" ]]; then
          valgrind ./a.out < test_input/${filename}.in > test_output/val.out 2>&1
          if grep -q "All heap blocks were freed -- no leaks are possible" test_output/val.out; then
            echo -e "${BOLD}${GREEN}Valgrind: ${filename} - No Leaks${NONE}"
          else
            echo -e "${BOLD}${RED}Valgrind: ${filename} - Memory Leaks${NONE}"
          fi
        fi
        echo "Ran test $filename"
    fi
done

if [[ -n "$compare" ]]; then
  echo -e "\n----------${BOLD}${CYAN}Comparing Differences${NONE}----------"
  for file in test_input/*; do
    if [ -f "$file" ]; then
        filename=$(basename -- "$file")
        filename="${filename%.*}"
        DIFF=$(diff correct_output/${filename}.out test_output/${filename}.out)
        if [ "$DIFF" != "" ]
        then
            echo -e "${BOLD}${RED}Test $filename failed${NONE}"
            if [[ -n "$detail" ]]; then
              sdiff -l correct_output/${filename}.out test_output/${filename}.out | cat -n | grep -v -e '($'
            else
              diff correct_output/${filename}.out test_output/${filename}.out
            fi
        else
            echo -e "${BOLD}${GREEN}Test $filename passed${NONE}"
        fi
    fi
  done
fi

echo -e "\n---------${PURPLE}Testing Finished${NONE}----------"
